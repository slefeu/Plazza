# Process

## Description

The `Process` class is a wrapper around the `fork()` function. It allows to create a child process and to manage it.

## Constructor

The constructor of the `Process` class calls the `fork()` function. The `fork()` function creates a child process that is a copy of the parent process. The child process has its own pid. The pid of the parent process is returned by the `fork()` function. If the pid returned by the `fork()` function is 0, it means that we are in the child process.

## Destructor

The destructor of the `Process` class kills the process if it is still running.

## Wait

The `wait()` function waits for the process to finish. It calls the `wait()` function. If the process is a child, it calls the `exit()` function.

## IsChild

The `isChild()` function checks if the process is a child. It returns true if the pid returned by the `fork()` function is 0.

## IsRunning

The `isRunning()` function checks if the process is running. It calls the `waitpid()` function with the WNOHANG option. If it returns -1, it means that an error occured and that the process is not running. If it returns 0, it means that the process is still running. Otherwise, it means that the process has finished.

## Kill

The `kill()` function kills the process. It calls the `kill()` function with SIGKILL as parameter. If the process is a child, it calls the `exit()` function.

## GetPid

The `getPid()` function returns the pid of the process. If we are in a child, it returns its own pid with the `getpid()` function. Otherwise, it returns its own pid member variable.

## GetCurrentPid

The `getCurrentPid()` function returns the pid of the current process. It calls the `getpid()` function.

## Usage

```cpp
#include <Process.hpp>

int main()
{
    Process process;

    if (process.isChild()) {
        // Do something in the child process
    } else {
        // Do something in the parent process
        process.wait();
    }

    return (0);
}
```