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
#include <cerrno>
#include <cstring>
#include <iostream>

#include "Errors.hpp"

NamedPipe::NamedPipe(std::string name)
    : path_("/tmp/" + name)
{
    std::string outpath = path_ + ".out";
    std::string inpath = path_ + ".in";
    ::mkfifo(outpath.c_str(), 0777);
    ::mkfifo(inpath.c_str(), 0777);
    fd_in_ = ::open(inpath.c_str(), O_RDWR | O_CLOEXEC);
    fd_out_ = ::open(outpath.c_str(), O_RDWR | O_CLOEXEC);
    if (fd_out_ == -1 || fd_in_ == -1) {
        throw CommunicationError("open() failed");
    }
}

std::bitset<64> NamedPipe::read(IPCDirection direction, bool wait) const
{
    int fd = direction == IPCDirection::IN ? fd_in_ : fd_out_;

    if (wait) {
        fcntl(fd, F_SETFL, O_RDWR | O_CLOEXEC);
    } else {
        fcntl(fd, F_SETFL, O_RDWR | O_CLOEXEC | O_NONBLOCK);
    }
    std::array<char, 8> buffer{};
    if (::read(fd, buffer.data(), 8) == -1) {
        if (errno == EAGAIN)
            return ({ 0; });
        throw CommunicationError("read() failed");
    }
    std::string str(buffer.begin(), buffer.end());
    return charToBitset(str);
}

void NamedPipe::write(IPCDirection direction, std::bitset<64> bitset) const
{
    int fd = direction == IPCDirection::IN ? fd_in_ : fd_out_;

    std::string buffer = bitsetToChar(bitset);
    if (::write(fd, buffer.c_str(), 8) == -1) {
        throw CommunicationError("write() failed");
    }
}

std::string NamedPipe::bitsetToChar(std::bitset<64> bitset)
{
    std::string result;
    for (int i = 0; i < 8; i++) {
        result += static_cast<char>(bitset.to_ulong());
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

void NamedPipe::close() const
{
    ::close(fd_in_);
    ::close(fd_out_);
}