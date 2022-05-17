/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Fridge
*/

#include "Fridge.hpp"

#include <cmath>
#include <iostream>

namespace plazza
{
Fridge::Fridge(unsigned int time) noexcept
    : restock_time_(time)
{
}

void Fridge::restock() noexcept
{
    for (std::size_t index : stocks_) {
        if (stocks_[index] < MAX_STOCK) {
            stocks_[index]++;
        }
    }
}

unsigned int Fridge::getRestockTime() const noexcept
{
    return (restock_time_);
}

void Fridge::takeIngredients(
    const std::vector<pizza::Ingredients>& list) noexcept
{
    for (auto it = std::begin(list); it != std::end(list); ++it) {
        remove(std::log2(static_cast<double>(*it)));
    }
}

void Fridge::remove(const double ingredient) noexcept
{
    stocks_[static_cast<size_t>(ingredient)]--;
}

bool Fridge::contains(const double ingredient) const noexcept
{
    return (stocks_[static_cast<size_t>(ingredient)] != 0);
}

void Fridge::display() const noexcept
{
    unsigned int index = 0;

    std::cout << "\nKitchen stocks:" << std::endl;
    for (auto i : stocks_) {
        std::cout << static_cast<pizza::Ingredients>(std::pow(2, index)) << ": "
                  << std::to_string(i) << std::endl;
        ++index;
    }
}

bool Fridge::hasEnough(
    const std::vector<pizza::Ingredients>& list) const noexcept
{
    for (auto it : list) {
        if (!contains(std::log2(static_cast<double>(it))))
            return (false);
    }
    return (true);
}

} // namespace plazza
