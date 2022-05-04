/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Fridge
*/

#pragma once

#include <array>

#include "APizza.hpp"

namespace plazza
{
class Fridge
{
  public:
    explicit Fridge(unsigned int time) noexcept;
    Fridge(const Fridge& other) noexcept = default;
    Fridge(Fridge&& other) noexcept = default;
    ~Fridge() noexcept = default;

    Fridge& operator=(const Fridge& rhs) noexcept = default;
    Fridge& operator=(Fridge&& rhs) noexcept = default;

    void restock() noexcept;
    bool contains(pizza::Ingredients ingredient) const noexcept;
    void remove(pizza::Ingredients ingredient) noexcept;

  protected:
  private:
    static constexpr unsigned int MAX_STOCK = 5;
    unsigned int restock_time_;
    std::array<std::size_t, 10> stocks_{{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}};
};
}
