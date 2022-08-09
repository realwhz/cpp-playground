#include <iostream>
#include <chrono>

#include "thread_pool.hpp"

int main()
{
    thread_pool tp{3};

    tp.start();

    std::this_thread::sleep_for(std::chrono::seconds{3});

    tp.queue_job([]{
        auto id = std::this_thread::get_id();
        for (auto i = 0; i < 30; i++) {
            std::cout << "thread " << id << ": " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds{3});

    tp.queue_job([]{
        auto id = std::this_thread::get_id();
        for (auto i = 0; i < 30; i++) {
            std::cout << "thread " << id << ": " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds{3});

    tp.queue_job([]{
        auto id = std::this_thread::get_id();
        for (auto i = 0; i < 30; i++) {
            std::cout << "thread " << id << ": " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds{3});

    tp.queue_job([]{
        auto id = std::this_thread::get_id();
        for (auto i = 0; i < 30; i++) {
            std::cout << "thread " << id << ": " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds{3});

    tp.queue_job([]{
        auto id = std::this_thread::get_id();
        for (auto i = 0; i < 30; i++) {
            std::cout << "thread " << id << ": " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    });

    while (tp.pending()) {
        std::cout << "Waiting for all jobs to be picked up" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds{5});
    }

    tp.stop();

    return 0;
}