/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** Reception
*/

#pragma once

#include <string>

namespace plazza
{
class Reception
{
  public:
    explicit Reception(char** av);
    Reception(const Reception& other) noexcept = default;
    Reception(Reception&& other) noexcept = default;
    ~Reception() noexcept = default;

    Reception& operator=(const Reception& rhs) noexcept = default;
    Reception& operator=(Reception&& rhs) noexcept = default;

    void executeShell();

  protected:
  private:
    // methods
    static double parseArgument(const std::string& str);
    void executeCommand();
    void setUserInput() noexcept;
    void exit() noexcept;
    void log();
    void status();

    // attributes
    std::string command_;
    int cooks_ = 0;
    double multiplier_ = 0;
    int time_ = 0;
    bool isEnd_ = false;
};
}