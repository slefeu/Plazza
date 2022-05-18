# Process

This class is a wrapper to the unix fork and wait functions. It allows to create a new process and wait for its termination.

## Constructors

The default constructor of this class uses the fork function to create a new process. The process id is saved in the `pid_` member of the class. If the `pid_` member is equal to 0, it means that it is the child process. If it is not equal to 0, it means that it is the parent process.

## Destructor

The destructor kills the child process if it is still alive when the object goes out of scope. The kill function with SIGKILL signal is used to terminate the child process. It does nothing if it is not the parent process.

## Methods

  * `wait()` : This function waits for the child process to terminate by calling the wait function of the unix api. This function does nothing if it is the child process.
  * `isChild()` : This function returns true if it is the child process and false otherwise.
  * `isRunning()` : This function uses the waitpid function to check if the child process is running. It returns false if it is not the parent process or if the waitpid function fails.
  * `kill()` : This function kills the child process using the kill function of the unix api with SIGKILL signal. If it is the child process, it calls exit with 0 as parameter.
  * `getPid()` : This function returns the pid of the child process. If it is not the parent process, it calls getpid of unix api to get its current pid.
  * `getCurrentPid()` : This function returns the current pid using getpid of unix api.

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