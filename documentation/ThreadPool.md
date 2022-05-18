# Threadpool

A thread pool is a group of pre-instantiated, idle threads which stand ready to be put to work. The goal of a thread pool is to maintain a pool of available threads in order to minimize the overhead associated with creating new threads.

## Constructors and Destructors

The constructor creates `nbThreads` threads and add them to the `workers_` vector.

```cpp
ThreadPool::ThreadPool(unsigned int nbThreads) noexcept
{
    while (nbThreads > workers_.size()) {
        workers_.emplace_back([this]() { this->workerThread(); });
    }
}
```

The destructor waits until all threads have finished to join them. It also notifies all workers that the pool is finished.

```cpp
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
```


## Methods

  * `waitForExecution()` : Wait until the queue is empty. The method uses a mutex and a condition variable to avoid busy waiting. It also uses a unique lock to ensure that the mutex is released when it goes out of scope.

  * `getBusyThreads()` : Returns the number of busy threads in the pool.

  * `addTask()` : Add a task to the queue and notify one worker that there is a task available. It uses a lock to ensure that only one thread at a time can access the queue.

  * `workerThread()` : The worker thread loops until it is notified by the destructor that the pool is finished. At each iteration, it tries to get a task from the queue, and executes it if it succeeds. When a thread finishes its task, it notifies any thread waiting for the queue to be empty, and decreases the number of busy threads.

  * `executeTask()` : Execute a task by calling its operator().

  * `getTask()` : Get a task from the queue if there is one available. The method uses a mutex and a condition variable to avoid busy waiting. It also uses a unique lock to ensure that the mutex is released when it goes out of scope.


## Attributes

* `finished_` : A boolean that is set to true when the thread pool is finished.

* `queue_` : A queue of tasks to execute.

* `workers_` : A vector of workers threads.

* `mutex_` : A mutex used to synchronize access to the queue and the `finished_` variable.

* `wait_mutex_` : A mutex used to synchronize access to the wait condition variable.

* `condition_` : A condition variable used to avoid busy waiting when a thread tries to get a task from the queue. It is notified when a task is added to the queue, or when the thread pool is finished.

* `wait_condition_` : A condition variable used to avoid busy waiting when a thread tries to wait for the queue to be empty. It is notified when a thread finishes its task, or when the thread pool is finished.

* `busyThreads_` : The number of busy threads in the pool.

## Usage example

```cpp
#include <cstdio>
#include <threads/ThreadPool.h>

void test(int i)
{
    printf("Hello from thread %d\n", i);
}

int main()
{
    threads::ThreadPool pool(4);

    for (int i = 0; i < 100; ++i) {
        pool.addTask(std::bind(test, i));
    }

    pool.waitForExecution();

    return 0;
}
```