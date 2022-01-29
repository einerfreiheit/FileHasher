#pragma once

#include <condition_variable>
#include <functional>
#include <memory>
#include <queue>
#include <thread>
#include <vector>

namespace file_hasher {

// A task runner class with thread-pool of workers.
class Runner {
public:
    Runner();
    //  ~Runner() waits all task to be completed.
    ~Runner();

    Runner& operator=(const Runner& other) const = delete;
    Runner(const Runner& other) = delete;

    // Enqueue a new task.
    template <template <class> class F, class R>
    void pushTask(F<R()>&& func);

private:
    void addWorker();
    void work();

private:
    std::condition_variable cv_;
    bool stop_flag_;

    std::queue<std::function<void()>> tasks_;
    std::mutex tasks_mtx_;

    std::vector<std::thread> workers_;
};

} // namespace file_hasher
