# README

{EPITECH} | Second year | Object-Oriented programming

- `Plazza project:`
    * The purpose of the project is to simulate a pizzeria, which is composed of two main parts:
        ** the Reception:
            - Takes and send orders to the kitchen
            - Receives the finished pizza and gives it to the customer
            - Keeps a log of all orders made
        ** multiple Kitchens, each containing:
            - a fridge with ingredients stocks
            - cooks

    * Load balancing
    .You will learn to deal with various problems, including load balancing, process and thread synchronizationand communication.Before you get started, should take some time to read up on the following tools you’ll need to use: •Processes (man fork,man exit,man wait,man ...) •Inter-process communication (IPC) •STL threads •POSIX threads (man pthread_*)




    Processes ( man fork , man exit , man wait , man ... )
    Inter-process communication (IPC)
    STL threads
    POSIX threads ( man pthread_* )

- `Tools:`
    * Epitech project made in `C++` version 20
    * Compiled with `CMake`, minimum version required : 3.6
    * a `justfile` is provided to compile it



## Usage:

- `How to compile the project:`
    * To build on debug mode: `mkdir build && just debug`
    * To build on release mode: `mkdir build && just build`

- `How to start the program`:
    * `./plazza <> `\

## Highlights:

- C++ thread pool implementation : class `ThreadPool`
    * Generic creation and run of a thread pool.

    * You can choose the number of threads you want in your pool.
    * Public method `addTask` allows to emplace a task (represented by a `std::function`) in a list that the pool will empty and execute.
    * Public method `getBusyThreads` allows to know outside of the thread pool the number of threads executing a task.


./plazza 2 5 2000

    The first parameter is a multiplier for the cooking time of the pizzas. It is used to examine your programmore easily, so it mustINEVITABLYbe implemented. Otherwise it will not be possible to grade you.Moreover this parameterMUSTbe able to accept numbers with value in between 0 to 1 to obtain adivisor of the pizzas cooking time. . .Cooking time is detailed later.
    The second parameter is the number of cooks per kitchen.Cook definition is detailed later.
    The third parameter is the time in milliseconds, used by the kitchen stock to replace ingredients.In-gredient definition is detailed later.

The purpose of this project is to make you realize a simulation of a pizzeria, which is composed of the reception that accepts new commands, of several kitchens, themselves with several cooks, themselves cooking several pizzas.
