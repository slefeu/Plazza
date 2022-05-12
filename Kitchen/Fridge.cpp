/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Fridge
*/

#include "Fridge.hpp"

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

void Fridge::takeIngredients(
    const std::vector<pizza::Ingredients>& list) noexcept
{
    for (auto it = std::begin(list); it != std::end(list); ++it) {
        remove(*it);
    }
}

unsigned int Fridge::getRestockTime() const noexcept
{
    return (restock_time_);
}

void Fridge::remove(const pizza::Ingredients ingredient) noexcept
{
    stocks_[static_cast<unsigned int>(ingredient)]--;
}

bool Fridge::contains(const pizza::Ingredients ingredient) const noexcept
{
    return (stocks_[static_cast<unsigned int>(ingredient)] != 0);
}

void Fridge::display() const noexcept
{
    unsigned int index = 0;

    std::cout << "\nKitchen stock:" << std::endl;
    for (auto i : stocks_) {
        std::cout << static_cast<pizza::Ingredients>(index) << ": "
                  << std::to_string(i) << std::endl;
        ++index;
    }
}

bool Fridge::hasEnough(
    const std::vector<pizza::Ingredients>& list) const noexcept
{
    for (auto i : list) {
        if (!contains(i))
            return (false);
    }
    return (true);
}

} // namespace plazza
