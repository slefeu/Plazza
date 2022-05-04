/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Clock
*/

#include "Clock.hpp"

void Clock::setPauseStart() noexcept
{
    start_ = std::chrono::high_resolution_clock::now();
}

bool Clock::checkElapsedTime() noexcept
{
    auto end = std::chrono::system_clock::now();

    if (std::chrono::duration_cast<std::chrono::seconds>(end - start_).count()
        >= MAX_TIME)
        return (true);
    return (false);
}