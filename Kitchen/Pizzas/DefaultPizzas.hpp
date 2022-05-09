/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** PizzaAmericana
*/

#pragma once
#include "APizza.hpp"

namespace pizza
{

class PizzaRegina : public APizza
{
  public:
    PizzaRegina(PizzaSize size, int modifier) noexcept;
    PizzaRegina(const PizzaRegina& other) noexcept = default;
    PizzaRegina(PizzaRegina&& other) noexcept = default;
    ~PizzaRegina() noexcept = default;

    PizzaRegina& operator=(const PizzaRegina& rhs) noexcept = default;
    PizzaRegina& operator=(PizzaRegina&& rhs) noexcept = default;

  protected:
  private:
};

class PizzaMargarita : public APizza
{
  public:
    PizzaMargarita(PizzaSize size, int modifier) noexcept;
    PizzaMargarita(const PizzaMargarita& other) noexcept = default;
    PizzaMargarita(PizzaMargarita&& other) noexcept = default;
    ~PizzaMargarita() noexcept = default;

    PizzaMargarita& operator=(const PizzaMargarita& rhs) noexcept = default;
    PizzaMargarita& operator=(PizzaMargarita&& rhs) noexcept = default;

  protected:
  private:
};

class PizzaAmericana : public APizza
{
  public:
    PizzaAmericana(PizzaSize size, int modifier) noexcept;
    PizzaAmericana(const PizzaAmericana& other) noexcept = default;
    PizzaAmericana(PizzaAmericana&& other) noexcept = default;
    ~PizzaAmericana() noexcept = default;

    PizzaAmericana& operator=(const PizzaAmericana& rhs) noexcept = default;
    PizzaAmericana& operator=(PizzaAmericana&& rhs) noexcept = default;

  protected:
  private:
};

class PizzaFantasia : public APizza
{
  public:
    PizzaFantasia(PizzaSize size, int modifier) noexcept;
    PizzaFantasia(const PizzaFantasia& other) noexcept = default;
    PizzaFantasia(PizzaFantasia&& other) noexcept = default;
    ~PizzaFantasia() noexcept = default;

    PizzaFantasia& operator=(const PizzaFantasia& rhs) noexcept = default;
    PizzaFantasia& operator=(PizzaFantasia&& rhs) noexcept = default;

  protected:
  private:
};
} // namespace pizza