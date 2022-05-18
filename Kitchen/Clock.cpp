/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Clock
*/

#include "Clock.hpp"

void Clock::setIdle(bool value) noexcept
{
    idle_ = value;
    start_ = std::chrono::high_resolution_clock::now();
}

bool Clock::getIdle() const noexcept
{
    return (idle_);
}

bool Clock::isIdle() const noexcept
{
    auto end = std::chrono::system_clock::now();

    if (std::chrono::duration_cast<std::chrono::seconds>(end - start_).count()
        >= MAX_TIME)
        return (true);
    return (false);
}

void Clock::reset() noexcept
{
    start_ = std::chrono::high_resolution_clock::now();
}

void Clock::resetStocks() noexcept
{
    restock_ = std::chrono::high_resolution_clock::now();
}

bool Clock::isNSeconds(unsigned int seconds) noexcept
{
    auto end = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::seconds>(end - restock_).count()
        >= seconds) {
        return (true);
    }
    return (false);
}