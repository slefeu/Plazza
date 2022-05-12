/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** PizzaSerializer
*/

#pragma once

#include <array>
#include <bitset>

#include "Pizza.hpp"

class PizzaSerializer
{
  public:
    PizzaSerializer() noexcept = delete;
    PizzaSerializer(const PizzaSerializer& other) noexcept = default;
    PizzaSerializer(PizzaSerializer&& other) noexcept = default;
    ~PizzaSerializer() noexcept = delete;

    PizzaSerializer& operator=(const PizzaSerializer& rhs) noexcept = default;
    PizzaSerializer& operator=(PizzaSerializer&& rhs) noexcept = default;

    static std::array<std::bitset<64>, 5> serialize(
        const pizza::Pizza&) noexcept;

  protected:
  private:
    static std::bitset<64> enumToBitset(unsigned int, std::bitset<64>) noexcept;
    static std::bitset<64> enumlistToBitset(
        const std::vector<pizza::Ingredients>& ingredients) noexcept;
    static std::size_t getDoubleFractional(double value) noexcept;
};
