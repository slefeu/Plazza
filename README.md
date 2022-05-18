# {EPITECH} | Second year | OOP | Plazza

## Plazza project:

- `Tools:`
    * Project made in `C++` version 20
    * Compiled with `CMake`, minimum version required : 3.6
    * a `justfile` is provided to compile it  

The purpose of the project is to simulate a pizzeria, which is composed of two main parts:

    - a Reception:
        - Takes and send orders to kitchens
        - Receives the finished order and gives it to the customer
        - Keeps a log of all orders made

    - Kitchens containing:
        - a fridge with ingredients stocks
        - a set number of cooks, represented as a thread pool

- `Notions we had to implement and encapsulate:`
    * Load balancing
    * processes synchronization & commmunication (IPC)
    * POSIX threads synchronization & commmunication

For further details about the implementation of these notions, you can click [here](./documentation) to be redirected to our documentation.

## Usage:

- `How to compile the project:`
    * To build on debug mode : `mkdir build && just debug`<brk>

    * To build on release mode : `mkdir build && just build`

- `How to start the program`:
    * `./plazza 2 5 4000 `

The first parameter is a `multiplier` for the cooking time of the pizzas.  
-> If the value is between 0 and 1, kitchens will cook faster  
-> Else it will cook slower  
  
The second parameter is the `number of cooks` per kitchen.
Each kitchen represents its cooks in a thread pool.
  
The third parameter is the `time` in milliseconds, used by the kitchen to replace ingredients.

## Highlights:

- C++ thread pool implementation : [documentation](./documentation/ThreadPool.md)
    * Generic creation and run of a thread pool.
    * You can choose the number of threads you want in your pool.

- C++ process wrapper : [documentation](./documentation/Process.md)
    * This class is a wrapper to the unix `fork` and `wait` functions
    * It allows to create a new process and wait for its termination.

- C++ named pipe wrapper : [documentation](./documentation/NamedPipe.md)
    * The `NamedPipe` class is a wrapper around the `mkfifo` and `open` system calls.
    * It allows to create a named pipe with two directions, one for reading and one for writing.

- C++ class object serialization and deserialization : [documentation](./documentation/Serializer.md)
    * Send serialized datas during inter-process communication
    * Recovers the datas and recreates an instance of the class with the provided serialized datas
