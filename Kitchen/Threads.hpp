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

class Task
{
  public:
    using Function = void (*)();
    Task() noexcept = default;
    Task(const Task& other) noexcept = default;
    Task(Task&& other) noexcept = default;
    ~Task() noexcept = default;

    Task& operator=(const Task& rhs) noexcept = default;
    Task& operator=(Task&& rhs) noexcept = default;

    Function f;

  protected:
  private:
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

  protected:
  private:
    // attributes
    bool finished_ = false;
    std::queue<Task> queue_;
    std::vector<std::thread> workers_;
    std::unique_ptr<std::mutex> mutex_;
    std::unique_ptr<std::condition_variable> condition_;

    // methods
    std::size_t getPoolSize() const noexcept;
    void workerThread() noexcept;
    void addTask(Task) noexcept;
    void executeTask() noexcept;
};
}
