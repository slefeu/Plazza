/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Americana
*/

#pragma once
#include "APizza.hpp"

namespace pizza
{

class Regina : public APizza
{
  public:
    Regina(PizzaSize size, int modifier) noexcept;
    Regina(const Regina& other) noexcept = default;
    Regina(Regina&& other) noexcept = default;
    ~Regina() noexcept = default;

    Regina& operator=(const Regina& rhs) noexcept = default;
    Regina& operator=(Regina&& rhs) noexcept = default;

  protected:
  private:
};

class Margarita : public APizza
{
public:
  Margarita(PizzaSize size, int modifier) noexcept;
  Margarita(const Margarita &other) noexcept = default;
  Margarita(Margarita &&other) noexcept = default;
  ~Margarita() noexcept = default;

  Margarita &operator=(const Margarita &rhs) noexcept = default;
  Margarita &operator=(Margarita &&rhs) noexcept = default;

protected:
private:
};

class Americana : public APizza
{
  public:
    Americana(PizzaSize size, int modifier) noexcept;
    Americana(const Americana& other) noexcept = default;
    Americana(Americana&& other) noexcept = default;
    ~Americana() noexcept = default;

    Americana& operator=(const Americana& rhs) noexcept = default;
    Americana& operator=(Americana&& rhs) noexcept = default;

  protected:
  private:
};

class Fantasia : public APizza
{
public:
  Fantasia(PizzaSize size, int modifier) noexcept;
  Fantasia(const Fantasia &other) noexcept = default;
  Fantasia(Fantasia &&other) noexcept = default;
  ~Fantasia() noexcept = default;

  Fantasia &operator=(const Fantasia &rhs) noexcept = default;
  Fantasia &operator=(Fantasia &&rhs) noexcept = default;

protected:
private:
};
} // namespace pizza