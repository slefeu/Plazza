/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"

namespace pizza
{

Pizza::Pizza(PizzaType type, PizzaSize size, double time) noexcept
    : type_(type)
    , size_(size)
    , cooking_time_(time)
{
}

std::vector<Ingredients> Pizza::getIngredients() const noexcept
{
    return (ingredients_);
}

CookingTime Pizza::getCookingTime() const noexcept
{
    return (cooking_time_);
}

PizzaType Pizza::getPizzaType() const noexcept
{
    return (type_);
}

std::ostream& operator<<(std::ostream& output, Ingredients rhs) noexcept
{
    switch (rhs) {
        case Ingredients::Dough: output << "Dough"; break;
        case Ingredients::Tomato: output << "Tomato"; break;
        case Ingredients::Gruyere: output << "Gruyere"; break;
        case Ingredients::Ham: output << "Ham"; break;
        case Ingredients::Mushrooms: output << "Mushrooms"; break;
        case Ingredients::Steak: output << "Steak"; break;
        case Ingredients::Eggplant: output << "Eggplant"; break;
        case Ingredients::GoatCheese: output << "GoatCheese"; break;
        case Ingredients::ChiefLove: output << "ChiefLove"; break;
    }
    return (output);
}
} // namespace pizza