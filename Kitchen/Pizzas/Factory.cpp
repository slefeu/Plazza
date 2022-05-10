/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Factory
*/

#include "Factory.hpp"

#include <functional>
#include <iostream>
#include <map>

#include "Errors.hpp"

pizza::Pizza Factory::createPizza(const pizza::PizzaType type,
    const pizza::PizzaSize size,
    const double multiplier)
{
    static std::map<pizza::PizzaType,
        std::function<pizza::Pizza(pizza::PizzaSize, double)>>
        creator_ = {
            {pizza::PizzaType::Regina, createRegina},
            {pizza::PizzaType::Margarita, createMargarita},
            {pizza::PizzaType::Americana, createAmericana},
            {pizza::PizzaType::Fantasia, createFantasia},
        };
    auto iterator = creator_.find(type);

    if (iterator == creator_.end())
        throw(ExecutionError("Wrong pizza type."));
    return (iterator->second(size, multiplier));
}

pizza::Pizza Factory::createRegina(
    const pizza::PizzaSize size, const double multiplier)
{
    pizza::Pizza pizza = pizza::PizzaRegina(size, multiplier);
    return (pizza);
}
pizza::Pizza Factory::createMargarita(
    const pizza::PizzaSize size, const double multiplier)
{
    pizza::Pizza pizza = pizza::PizzaMargarita(size, multiplier);
    return (pizza);
}

pizza::Pizza Factory::createAmericana(
    const pizza::PizzaSize size, const double multiplier)
{
    pizza::Pizza pizza = pizza::PizzaAmericana(size, multiplier);
    return (pizza);
}
pizza::Pizza Factory::createFantasia(
    const pizza::PizzaSize size, const double multiplier)
{
    pizza::Pizza pizza = pizza::PizzaFantasia(size, multiplier);
    return (pizza);
}
