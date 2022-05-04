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

// définir pack et unpack
} // namespace pizza