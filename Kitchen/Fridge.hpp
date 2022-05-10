/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Fridge
*/

#pragma once

#include <array>

#include "Pizza.hpp"

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
    unsigned int getRestockTime() const noexcept;
    bool hasEnough(const std::vector<pizza::Ingredients>& list) const noexcept;
    void takeIngredients(const std::vector<pizza::Ingredients>& list) noexcept;
    void display() const noexcept;

  protected:
  private:
    static constexpr unsigned int MAX_STOCK = 5;
    unsigned int restock_time_;
    std::array<std::size_t, 9> stocks_{{5, 5, 5, 5, 5, 5, 5, 5, 5}};

    // methods
    bool contains(pizza::Ingredients ingredient) const noexcept;
    void remove(pizza::Ingredients ingredient) noexcept;
};
}
