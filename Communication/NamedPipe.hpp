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
    explicit NamedPipe(const std::string& name);
    NamedPipe(NamedPipe const& other) noexcept = delete;
    NamedPipe(NamedPipe&& other) noexcept = default;
    ~NamedPipe() noexcept = default;

    NamedPipe& operator=(NamedPipe const& other) noexcept = delete;
    NamedPipe& operator=(NamedPipe&& other) noexcept = default;

    void write(const IPCDirection&, const std::bitset<64>& bitset) const;
    std::bitset<64> read(const IPCDirection&, bool wait = false) const;
    void close() const noexcept;

  private:
    int fd_in_;
    int fd_out_;
    std::string path_;

    static std::bitset<64> charToBitset(const std::string& buffer) noexcept;
    static std::string bitsetToChar(std::bitset<64> bitset) noexcept;
};
