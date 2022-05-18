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

    void setIdle(bool value) noexcept;
    bool isNSeconds(unsigned int seconds) noexcept;
    bool isIdle() const noexcept;
    bool getIdle() const noexcept;
    void reset() noexcept;
    void resetStocks() noexcept;
    template <typename T>
    static auto getSeconds(T seconds) noexcept
    {
        return (std::chrono::duration<T, std::ratio<1>>(seconds));
    }

  protected:
  private:
    bool idle_{false};
    static constexpr unsigned int MAX_TIME = 5;
    std::chrono::high_resolution_clock::time_point start_{
        {std::chrono::high_resolution_clock::now()}};
    std::chrono::high_resolution_clock::time_point restock_{
        {std::chrono::high_resolution_clock::now()}};
};