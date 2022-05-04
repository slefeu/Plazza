/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Clock
*/

#pragma once

#include <chrono>

class Clock
{
  public:
    Clock() noexcept = default;
    Clock(const Clock& other) noexcept = default;
    Clock(Clock&& other) noexcept = default;
    ~Clock() noexcept = default;

    Clock& operator=(const Clock& rhs) noexcept = default;
    Clock& operator=(Clock&& rhs) noexcept = default;

    void setPauseStart() noexcept;
    bool checkElapsedTime() noexcept;

  protected:
  private:
    static constexpr unsigned int MAX_TIME = 5;
    bool idle_ = false;
    std::chrono::high_resolution_clock::time_point start_;
};