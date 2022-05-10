/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Americana
*/

#include "DefaultPizzas.hpp"

namespace pizza
{

PizzaRegina::PizzaRegina(pizza::PizzaSize size, double modifier) noexcept
    : Pizza(pizza::PizzaType::Regina, size, (2 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Gruyere);
    ingredients_.emplace_back(Ingredients::Ham);
    ingredients_.emplace_back(Ingredients::Mushrooms);
}

PizzaMargarita::PizzaMargarita(pizza::PizzaSize size, double modifier) noexcept
    : Pizza(pizza::PizzaType::Margarita, size, (1 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Gruyere);
}

PizzaAmericana::PizzaAmericana(pizza::PizzaSize size, double modifier) noexcept
    : Pizza(pizza::PizzaType::Americana, size, (2 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Gruyere);
    ingredients_.emplace_back(Ingredients::Steak);
}

PizzaFantasia::PizzaFantasia(pizza::PizzaSize size, double modifier) noexcept
    : Pizza(pizza::PizzaType::Fantasia, size, (4 * modifier))
{
    ingredients_.emplace_back(Ingredients::Dough);
    ingredients_.emplace_back(Ingredients::Tomato);
    ingredients_.emplace_back(Ingredients::Eggplant);
    ingredients_.emplace_back(Ingredients::GoatCheese);
    ingredients_.emplace_back(Ingredients::ChiefLove);
}

} // namespace pizza