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

/**
 * @brief Construct a new Named Pipe object
 *
 * @param name The name of the pipe
 */
NamedPipe::NamedPipe(const std::string& name)
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

/**
 * @brief Read from the pipe
 *
 * @param direction The direction of the pipe
 * @param wait If the function should wait for data
 * @return std::bitset<64> The data read
 */
std::bitset<64> NamedPipe::read(const IPCDirection& direction, bool wait) const
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

/**
 * @brief Write to the pipe
 *
 * @param direction The direction of the pipe
 * @param bitset The data to write
 */
void NamedPipe::write(const IPCDirection& direction, const std::bitset<64>& bitset) const
{
    int fd = direction == IPCDirection::IN ? fd_in_ : fd_out_;

    std::string buffer = bitsetToChar(bitset);
    if (::write(fd, buffer.c_str(), 8) == -1) {
        throw CommunicationError("write() failed");
    }
}

/**
 * @brief Convert a bitset to a string
 *
 * @param bitset The bitset to convert
 * @return std::string The string
 */
std::string NamedPipe::bitsetToChar(std::bitset<64> bitset) noexcept
{
    std::string result;
    for (int i = 0; i < 8; i++) {
        result += static_cast<char>(bitset.to_ulong());
        bitset >>= 8;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

/**
 * @brief Convert a string to a bitset
 *
 * @param buffer The string to convert
 * @return std::bitset<64> The bitset
 */
std::bitset<64> NamedPipe::charToBitset(const std::string& buffer) noexcept
{
    std::bitset<64> bitset;
    for (int i = 0; i < 8; i++) {
        bitset <<= 8;
        bitset |= static_cast<unsigned char>(buffer[i]);
    }
    return bitset;
}

/**
 * @brief Close the pipe
 */
void NamedPipe::close() const noexcept
{
    ::close(fd_in_);
    ::close(fd_out_);
}