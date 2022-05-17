/*
** EPITECH PROJECT, 2022
** Plazza
** File description: hpp file
** NamedPipe
*/

#pragma once

#include <bitset>
#include <cstdio>
#include <fstream>
#include <string>

enum class IPCDirection { IN, OUT };

class NamedPipe
{
  public:
    NamedPipe(std::string name);
    NamedPipe(NamedPipe const& other) noexcept = delete;
    NamedPipe(NamedPipe&& other) noexcept = default;
    NamedPipe& operator=(NamedPipe const& other) noexcept = delete;
    NamedPipe& operator=(NamedPipe&& other) noexcept = default;
    ~NamedPipe() noexcept = default;
    void write(IPCDirection, std::bitset<64> bitset) const;
    std::bitset<64> read(IPCDirection, bool wait = false) const;
    void close() const;

  private:
    int fd_in_;
    int fd_out_;
    std::string path_;

    static std::bitset<64> charToBitset(std::string buffer);
    static std::string bitsetToChar(std::bitset<64> bitset);
};
