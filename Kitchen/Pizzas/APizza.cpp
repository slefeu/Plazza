/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** APizza
*/

#include "APizza.hpp"

namespace pizza
{

APizza::APizza(PizzaType type, PizzaSize size, int time) noexcept
    : type_(type)
    , size_(size)
    , cooking_time_(time)
{
}

std::vector<Ingredients> APizza::getIngredients() const noexcept
{
    return (ingredients_);
}

CookingTime APizza::getCookingTime() const noexcept
{
    return (cooking_time_);
}

PizzaType APizza::getPizzaType() const noexcept
{
    return (type_);
}

// définir pack et unpack
} // namespace pizza