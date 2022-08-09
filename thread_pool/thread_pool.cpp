#include "thread_pool.hpp"

thread_pool::thread_pool(size_t num_threads): num_threads_(num_threads), stop_requested_(false)
{
    pool_.reserve(num_threads);
}

void thread_pool::start()
{
    for (size_t i = 0; i < num_threads_; i++)
        pool_.emplace_back(std::thread(&thread_pool::busy_loop, this));
}

void thread_pool::busy_loop()
{
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_);
            cv_.wait(lock, [this] {
                return !jobs_.empty() || stop_requested_;
            });
            if (stop_requested_) {
                return;
            }
            job = jobs_.front();
            jobs_.pop();
        }
        job();
    }
}

void thread_pool::stop()
{
    {
        std::unique_lock<std::mutex> lock(m_);
        stop_requested_ = true;
    }
    cv_.notify_all();
    for (auto&& t: pool_) {
        t.join();
    }
    pool_.clear();
}

void thread_pool::queue_job(const std::function<void()>& job)
{
    {
        std::unique_lock<std::mutex> lock(m_);
        jobs_.push(job);
    }
    cv_.notify_one();
}

bool thread_pool::pending()
{
    bool has_pending = false;
    {
        std::unique_lock<std::mutex> lock(m_);
        has_pending = !jobs_.empty();
    }
    return has_pending;
}