/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Factory
*/

#pragma once
#include <memory>

#include "DefaultPizzas.hpp"

class Factory
{
  public:
    Factory() noexcept = delete;
    Factory(const Factory& other) noexcept = delete;
    Factory(Factory&& other) noexcept = delete;
    ~Factory() noexcept = delete;

    Factory& operator=(const Factory& rhs) noexcept = delete;
    Factory& operator=(Factory&& rhs) noexcept = delete;

    static pizza::Pizza createPizza(
        pizza::PizzaType type, pizza::PizzaSize size, double multiplier);

  protected:
  private:
    static pizza::Pizza createRegina(
        const pizza::PizzaSize size, const double multiplier);
    static pizza::Pizza createMargarita(
        const pizza::PizzaSize size, const double multiplier);
    static pizza::Pizza createAmericana(
        const pizza::PizzaSize size, const double multiplier);
    static pizza::Pizza createFantasia(
        const pizza::PizzaSize size, const double multiplier);
};