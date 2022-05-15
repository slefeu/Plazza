/*
** EPITECH PROJECT, 2022
** Plazza
** File description: hpp file
** NamedPipe
*/

#pragma once

#include <bitset>
#include <string>

class NamedPipe
{
  public:
    NamedPipe(std::string name);
    NamedPipe(NamedPipe const& other) noexcept = default;
    NamedPipe(NamedPipe&& other) noexcept = default;
    NamedPipe& operator=(NamedPipe const& other) noexcept = default;
    NamedPipe& operator=(NamedPipe&& other) noexcept = default;
    ~NamedPipe() noexcept = default;
    void write(std::bitset<64> bitset);
    std::bitset<64> read(bool wait = true);
    void close();

  private:
    std::string path_;

    static std::bitset<64> charToBitset(std::string buffer);
    static std::string bitsetToChar(std::bitset<64> bitset);
};
