/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** APizza
*/

#pragma once

#include <vector>

namespace pizza
{
enum PizzaType { Regina = 1, Margarita = 2, Americana = 4, Fantasia = 8 };
enum PizzaSize { S = 1, M = 2, L = 4, XL = 8, XXL = 16 };
enum Ingredients {
    Doe,
    Tomato,
    Gruyere,
    Ham,
    Mushrooms,
    Steak,
    Eggplant,
    GoatCheese,
    ChiefLove
};

class APizza
{
  public:
    APizza(PizzaType, PizzaSize, int) noexcept;
    APizza(const APizza& other) noexcept = default;
    APizza(APizza&& other) noexcept = default;
    ~APizza() noexcept = default;

    APizza& operator=(const APizza& rhs) noexcept = default;
    APizza& operator=(APizza&& rhs) noexcept = default;

    void pack();   // à définir
    void unpack(); //à définir
  protected:
    PizzaType type_;
    PizzaSize size_;
    std::vector<Ingredients> ingredients_;
    int cooking_time_;

  private:
};
} // namespace pizza