#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>

class thread_pool {
public:
    thread_pool(size_t num_threads);
    void start();
    void stop();
    void queue_job(const std::function<void()>&);
    bool pending();

private:
    size_t num_threads_;
    std::vector<std::thread> pool_;
    std::mutex m_;
    std::condition_variable cv_;
    std::queue<std::function<void()>> jobs_;
    bool stop_requested_;

    void busy_loop();
};