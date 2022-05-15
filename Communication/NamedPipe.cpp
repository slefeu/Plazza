/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** NamedPipe
*/

#include "NamedPipe.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cstring>

#include "Errors.hpp"

NamedPipe::NamedPipe(std::string name)
    : path_("/tmp/" + name)
{
    ::mkfifo(path_.c_str(), 0666);
}

std::bitset<64> NamedPipe::read(bool wait)
{
    int options = O_RDONLY | O_CLOEXEC;
    if (!wait) {
        options |= O_NONBLOCK;
    }
    int fd = ::open(path_.c_str(), options);
    if (fd == -1) {
        throw CommunicationError("open() failed");
    }
    std::array<char, 8> buffer{};
    if (::read(fd, buffer.data(), 8) == -1) {
        return (std::bitset<64>(0));
    }
    ::close(fd);
    std::string str(buffer.begin(), buffer.end());
    return charToBitset(str);
}

void NamedPipe::write(std::bitset<64> bitset)
{
    int fd = ::open(path_.c_str(), O_WRONLY | O_CLOEXEC);
    if (fd == -1) {
        throw CommunicationError("open() failed");
    }
    std::string buffer = bitsetToChar(bitset);
    if (::write(fd, buffer.c_str(), 8) == -1) {
        throw CommunicationError("write() failed");
    }
    ::close(fd);
}

std::string NamedPipe::bitsetToChar(std::bitset<64> bitset)
{
    std::string result;
    for (int i = 0; i < 8; i++) {
        result += static_cast<unsigned char>(bitset.to_ulong());
        bitset >>= 8;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::bitset<64> NamedPipe::charToBitset(std::string buffer)
{
    std::bitset<64> bitset;
    for (int i = 0; i < 8; i++) {
        bitset <<= 8;
        bitset |= static_cast<unsigned char>(buffer[i]);
    }
    return bitset;
}

void NamedPipe::close()
{
    ::unlink(path_.c_str());
}