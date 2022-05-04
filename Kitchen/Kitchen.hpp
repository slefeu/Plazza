/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include "Clock.hpp"
#include "Fridge.hpp"
#include "Threads.hpp"

namespace plazza
{

class Kitchen
{
  public:
    explicit Kitchen(unsigned int nb_cooks,
        int multiplier,
        unsigned int restock_time) noexcept;
    Kitchen(const Kitchen& other) noexcept = delete;
    Kitchen(Kitchen&& other) noexcept = default;
    ~Kitchen() noexcept = default;

    Kitchen& operator=(const Kitchen& rhs) noexcept = delete;
    Kitchen& operator=(Kitchen&& rhs) noexcept = default;

  protected:
  private:
    threads::ThreadPool cooks_;
    unsigned int max_pizza_;
    int multiplier_;
    bool full_{false};
    Clock clock_;
    Fridge fridge_;
};
} // namespace plazza