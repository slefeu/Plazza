/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Threads
*/

#include "Threads.hpp"

#include <iostream>
namespace threads
{

ThreadPool::ThreadPool(unsigned int nbThreads) noexcept
{
    while (nbThreads > workers_.size()) {
        workers_.emplace_back([this]() { this->workerThread(); });
    }
}

ThreadPool::~ThreadPool() noexcept
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        finished_ = true;
    }
    condition_.notify_all();
    for (auto& worker : workers_) {
        worker.join();
    }
}

void ThreadPool::waitForExecution() noexcept
{
    std::unique_lock<std::mutex> lock(wait_mutex_);
    wait_condition_.wait(lock, [this] { return (queue_.empty()); });
}

void ThreadPool::workerThread() noexcept
{
    while (!finished_) {
        executeTask(getTask());
    }
}

void ThreadPool::executeTask(const Task& task) noexcept
{
    task.f();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        wait_condition_.notify_one();
    }
}

Task ThreadPool::getTask() noexcept
{
    Task task{};
    task.f = [] { return; };

    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(
        lock, [this] { return (this->finished_ || !this->queue_.empty()); });
    if (finished_ && queue_.empty())
        return task;
    task = queue_.front();
    queue_.pop();
    return (task);
}

void ThreadPool::addTask(const Task& task) noexcept
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.emplace(task);
    }
    condition_.notify_one();
}
} // namespace threads
