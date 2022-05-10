/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Pizza
*/

#pragma once

#include <ostream>
#include <vector>

namespace pizza
{

using CookingTime = double;
static constexpr unsigned int TYPES = 4;
enum class PizzaType { Regina = 1, Margarita = 2, Americana = 4, Fantasia = 8 };
enum class PizzaSize { S = 1, M = 2, L = 4, XL = 8, XXL = 16 };
enum class Ingredients {
    Dough,
    Tomato,
    Gruyere,
    Ham,
    Mushrooms,
    Steak,
    Eggplant,
    GoatCheese,
    ChiefLove
};

class Pizza
{
  public:
    Pizza(PizzaType, PizzaSize, double) noexcept;
    Pizza(const Pizza& other) noexcept = default;
    Pizza(Pizza&& other) noexcept = default;
    ~Pizza() noexcept = default;

    Pizza& operator=(const Pizza& rhs) noexcept = default;
    Pizza& operator=(Pizza&& rhs) noexcept = default;

    CookingTime getCookingTime() const noexcept;
    PizzaType getPizzaType() const noexcept;
    std::vector<Ingredients> getIngredients() const noexcept;

  protected:
    PizzaType type_;
    PizzaSize size_;
    std::vector<Ingredients> ingredients_;
    CookingTime cooking_time_;

  private:
};

std::ostream& operator<<(std::ostream& output, Ingredients rhs) noexcept;
} // namespace pizza