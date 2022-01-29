#include "Runner.hpp"

#include <iostream>

namespace file_hasher {

Runner::Runner() : stop_flag_(false) {
    unsigned int threads_num = std::thread::hardware_concurrency();
    workers_.reserve(threads_num);
    for (unsigned int i = 0; i < threads_num; ++i) {
        addWorker();
    }
}

void Runner::work() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(tasks_mtx_);
            cv_.wait(lock, [this] { return stop_flag_ || !tasks_.empty(); });
            if (stop_flag_ && tasks_.empty()) {
                break;
            }
            task = std::move(tasks_.front());
            tasks_.pop();
        }
        task();
    }
}

template <>
void Runner::pushTask<std::function, void>(std::function<void()>&& func) {
    {
        std::lock_guard<std::mutex> lock(this->tasks_mtx_);
        tasks_.emplace(std::forward<std::function<void()>>(func));
    }
    cv_.notify_one();
}

void Runner::addWorker() {
    workers_.emplace_back([this] { this->work(); });
}

Runner::~Runner() {
    {
        std::lock_guard<std::mutex> lock(tasks_mtx_);
        stop_flag_ = true;
    }
    cv_.notify_all();
    for (auto& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

} // namespace file_hasher
