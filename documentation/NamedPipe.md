
# FIFO wrapper : NamedPipe class

## Description

The `NamedPipe` class is a wrapper around the `mkfifo` and `open` system calls.
It allows to create a named pipe with two directions, one for reading and one for writing.

## Constructor

The constructor takes the name of the pipe as a parameter.
It creates two named pipes, one for reading and one for writing.
The names are created by appending `.in` and `.out` to the given name.
The constructor also opens both pipes with the `open` system call.

## Read and write methods

The `read` method takes a direction (either `IN` or `OUT`) and a boolean as parameters.
If the boolean is set to true, the method will wait until data is available in the pipe.
Otherwise, it will return an empty bitset if no data is available.
The method returns a bitset containing the data read from the pipe.
The `write` method takes a direction (either `IN` or `OUT`) and a bitset as parameters.
It writes the bitset to the pipe in the given direction.

## Close method

The `close` method closes both pipes.

## Private methods

The `charToBitset` and `bitsetToChar` methods are used to convert between bitsets and strings.
The `bitsetToChar` method converts a bitset to a string by converting each byte of the bitset to a character.
The `charToBitset` method converts a string to a bitset by converting each character to a byte.

## Usage example :

```c++
#include "NamedPipe.hpp"

int main()
{
    NamedPipe pipe("mypipe");

    pipe.write(IPCDirection::IN, std::bitset<64>{0xDEADBEEF});
    std::bitset<64> data = pipe.read(IPCDirection::OUT);

    return 0;
}
```
