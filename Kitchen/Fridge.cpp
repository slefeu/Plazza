/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Fridge
*/

#include "Fridge.hpp"

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

void Fridge::remove(const pizza::Ingredients ingredient) noexcept
{
    stocks_[ingredient]--;
}

bool Fridge::contains(const pizza::Ingredients ingredient) const noexcept
{
    return (stocks_[ingredient] != 0);
}

} // namespace plazza
