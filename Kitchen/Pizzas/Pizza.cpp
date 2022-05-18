/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"

namespace pizza
{
Pizza::Pizza(PizzaType type, double time) noexcept
    : type_(type)
    , size_(PizzaSize::S)
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

PizzaSize Pizza::getPizzaSize() const noexcept
{
    return (size_);
}

void Pizza::setCookingTime(CookingTime& time) noexcept
{
    cooking_time_ = time;
}

void Pizza::setPizzaType(PizzaType& type) noexcept
{
    type_ = type;
}

void Pizza::setSize(PizzaSize size) noexcept
{
    size_ = size;
}

void Pizza::addIngredient(Ingredients& ingredient) noexcept
{
    ingredients_.emplace_back(ingredient);
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

std::ostream& operator<<(std::ostream& output, PizzaSize size) noexcept
{
    switch (size) {
        case PizzaSize::S: output << "S"; break;
        case PizzaSize::M: output << "M"; break;
        case PizzaSize::L: output << "L"; break;
        case PizzaSize::XL: output << "XL"; break;
        case PizzaSize::XXL: output << "XXL"; break;
    }
    return (output);
}

std::ostream& operator<<(std::ostream& output, PizzaType type) noexcept
{
    switch (type) {
        case PizzaType::Americana: output << "americana"; break;
        case PizzaType::Margarita: output << "margarita"; break;
        case PizzaType::Regina: output << "regina"; break;
        case PizzaType::Fantasia: output << "fantasia"; break;
        default: output << "custom"; break;
    }
    return (output);
}

std::ostream& operator<<(std::ostream& output, Pizza& pizza) noexcept
{
    output << pizza.getPizzaType()
           << " " << pizza.getPizzaSize();
    for (const auto& ingredient : pizza.getIngredients()) {
        output << " " << ingredient;
    }
    return (output);
}
} // namespace pizza