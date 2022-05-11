/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Americana
*/

#include "DefaultPizzas.hpp"

namespace pizza
{

PizzaRegina::PizzaRegina(double modifier) noexcept
    : Pizza(pizza::PizzaType::Regina, (2 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Gruyere);
    ingredients_.emplace_back(Ingredients::Ham);
    ingredients_.emplace_back(Ingredients::Mushrooms);
}

PizzaMargarita::PizzaMargarita(double modifier) noexcept
    : Pizza(pizza::PizzaType::Margarita, (1 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Gruyere);
}

PizzaAmericana::PizzaAmericana(double modifier) noexcept
    : Pizza(pizza::PizzaType::Americana, (2 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Gruyere);
    ingredients_.emplace_back(Ingredients::Steak);
}

PizzaFantasia::PizzaFantasia(double modifier) noexcept
    : Pizza(pizza::PizzaType::Fantasia, (4 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Eggplant);
    ingredients_.emplace_back(Ingredients::GoatCheese);
    ingredients_.emplace_back(Ingredients::ChiefLove);
}

} // namespace pizza