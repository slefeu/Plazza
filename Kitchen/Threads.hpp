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
#include <optional>
#include <queue>
#include <thread>
#include <vector>

namespace threads
{

using Task = std::function<void(void)>;

class ThreadPool
{
  public:
    explicit ThreadPool(unsigned int) noexcept;
    ThreadPool(const ThreadPool& other) noexcept = delete;
    ThreadPool(ThreadPool&& other) noexcept = delete;
    ~ThreadPool() noexcept;

    ThreadPool& operator=(const ThreadPool& rhs) noexcept = delete;
    ThreadPool& operator=(ThreadPool&& rhs) noexcept = delete;

    void addTask(const Task& task) noexcept;
    void waitForExecution() noexcept;
    unsigned int getBusyThreads() const noexcept;

  protected:
  private:
    // attributes
    bool finished_{false};
    std::queue<Task> queue_;
    std::vector<std::thread> workers_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::mutex wait_mutex_;
    std::condition_variable wait_condition_;
    unsigned int busyThreads_ = 0;

    // methods
    void workerThread() noexcept;
    void executeTask(const Task& task) noexcept;
    std::optional<Task> getTask() noexcept;
};
}
