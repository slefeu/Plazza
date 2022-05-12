/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** PizzaAmericana
*/

#pragma once
#include "Pizza.hpp"

namespace pizza
{
class PizzaRegina : public Pizza
{
  public:
    PizzaRegina(double modifier) noexcept;
    PizzaRegina(const PizzaRegina& other) noexcept = default;
    PizzaRegina(PizzaRegina&& other) noexcept = default;
    ~PizzaRegina() noexcept = default;

    PizzaRegina& operator=(const PizzaRegina& rhs) noexcept = default;
    PizzaRegina& operator=(PizzaRegina&& rhs) noexcept = default;

  protected:
  private:
};

class PizzaMargarita : public Pizza
{
  public:
    PizzaMargarita(double modifier) noexcept;
    PizzaMargarita(const PizzaMargarita& other) noexcept = default;
    PizzaMargarita(PizzaMargarita&& other) noexcept = default;
    ~PizzaMargarita() noexcept = default;

    PizzaMargarita& operator=(const PizzaMargarita& rhs) noexcept = default;
    PizzaMargarita& operator=(PizzaMargarita&& rhs) noexcept = default;

  protected:
  private:
};

class PizzaAmericana : public Pizza
{
  public:
    PizzaAmericana(double modifier) noexcept;
    PizzaAmericana(const PizzaAmericana& other) noexcept = default;
    PizzaAmericana(PizzaAmericana&& other) noexcept = default;
    ~PizzaAmericana() noexcept = default;

    PizzaAmericana& operator=(const PizzaAmericana& rhs) noexcept = default;
    PizzaAmericana& operator=(PizzaAmericana&& rhs) noexcept = default;

  protected:
  private:
};

class PizzaFantasia : public Pizza
{
  public:
    PizzaFantasia(double modifier) noexcept;
    PizzaFantasia(const PizzaFantasia& other) noexcept = default;
    PizzaFantasia(PizzaFantasia&& other) noexcept = default;
    ~PizzaFantasia() noexcept = default;

    PizzaFantasia& operator=(const PizzaFantasia& rhs) noexcept = default;
    PizzaFantasia& operator=(PizzaFantasia&& rhs) noexcept = default;

  protected:
  private:
};
} // namespace pizza