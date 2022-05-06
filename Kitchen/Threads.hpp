/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Threads
*/

#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace threads
{

struct Task {
    using Function = void (*)();
    Function f;
};

class ThreadPool
{
  public:
    explicit ThreadPool(unsigned int) noexcept;
    ThreadPool(const ThreadPool& other) noexcept = delete;
    ThreadPool(ThreadPool&& other) noexcept = default;
    ~ThreadPool() noexcept;

    ThreadPool& operator=(const ThreadPool& rhs) noexcept = delete;
    ThreadPool& operator=(ThreadPool&& rhs) noexcept = default;

    void addTask(const Task& task) noexcept;

  protected:
  private:
    // attributes
    bool finished_{false};
    std::queue<Task> queue_;
    std::vector<std::thread> workers_;
    std::unique_ptr<std::mutex> mutex_;
    std::unique_ptr<std::condition_variable> condition_;
    // methods
    void workerThread() noexcept;
    void executeTask() noexcept;
};
}
