/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Threads
*/

#include "Threads.hpp"

namespace threads
{

ThreadPool::ThreadPool(unsigned int nbThreads) noexcept
    : mutex_(std::make_unique<std::mutex>())
    , condition_(std::make_unique<std::condition_variable>())
{
    {
        std::unique_lock<std::mutex> lock(*mutex_);
        while (nbThreads > workers_.size()) {
            std::thread worker([this]() { this->workerThread(); });
            workers_.emplace_back(std::move(worker));
        }
    }
}

ThreadPool::~ThreadPool() noexcept
{
    {
        std::unique_lock<std::mutex> lock(*mutex_);
        finished_ = true;
    }
    for (auto& worker : workers_)
        worker.join();
    condition_->notify_all();
}

std::size_t ThreadPool::getPoolSize() const noexcept
{
    return (workers_.size());
}

void ThreadPool::workerThread() noexcept
{
    while (true) {
        executeTask();
    }
}

void ThreadPool::executeTask() noexcept
{
    std::unique_lock<std::mutex> lock(*mutex_);
    condition_->wait(lock, [this] { return (finished_ || !queue_.empty()); });
    if (finished_ && queue_.empty())
        return;
    Task task = queue_.front();
    task.f();
    queue_.pop();
}

void ThreadPool::addTask(const Task& task) noexcept
{
    {
        std::unique_lock<std::mutex> lock(*mutex_);
        queue_.emplace(task);
    }
    condition_->notify_one();
}
} // namespace threads
