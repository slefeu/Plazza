# POSIX Process encapsulation : Process class

 This class is a wrapper to the UNIX `fork` and `wait` functions. It allows to create a new process and wait for its termination.

## Constructors

The default constructor of this class uses the fork function to create a new process. The process id is saved in the `pid_` member of the class.
If the `pid_` member is equal to 0, it means that it is the child process.
If it is not equal to 0, it means that it is the parent process.

## Destructor

The destructor kills the child process if it is still alive when the object goes out of scope. The `kill` function is used to terminate the child process, with the SIGKILL signal as a flag.
It does nothing if it is not the parent process.

## Methods

```c++
void wait() const noexcept
```
- This method waits for the child process to terminate by calling the `wait` function of the UNIX api.
- It does nothing if it's the child process.

```c++
bool isChild() const noexcept
```
- This method returns true if it is the child process, false otherwise.

```c++
bool Process::isRunning() const noexcept
```
- This method uses the `waitpid` function to check if the child process is running.
- It returns false if it is not the parent process or if the `waitpid` function fails.

```c++
void kill() const noexcept
```
- It kills the child process using the `kill` function of the UNIX api.
- If it's the child process, it calls `exit(0)`.

```c++
pid_t getPid() const
```
- This method returns the pid of the child process.
- If it is not the parent process, it calls the UNIX `gitpid`function to get its current pid.

## Usage

```c++
#include "Process.hpp"

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
