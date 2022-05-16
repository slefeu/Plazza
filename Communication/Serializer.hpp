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

enum class RequestType {
    Empty = 0,
    Error = 1,
    Success = 2,
    Availability = 4,
    Order = 8,
    Status = 16
};
class PizzaSerializer
{
  public:
    PizzaSerializer() noexcept = delete;
    PizzaSerializer(const PizzaSerializer& other) noexcept = default;
    PizzaSerializer(PizzaSerializer&& other) noexcept = default;
    ~PizzaSerializer() noexcept = delete;

    PizzaSerializer& operator=(const PizzaSerializer& rhs) noexcept = default;
    PizzaSerializer& operator=(PizzaSerializer&& rhs) noexcept = default;

    static constexpr int ARRAY_SIZE = 5;
    static std::array<std::bitset<64>, ARRAY_SIZE> serializePizza(
        const pizza::Pizza&) noexcept;
    static std::bitset<8> serializeCommand(char name) noexcept;
    static pizza::Pizza deserializePizza(
        const std::array<std::bitset<64>, ARRAY_SIZE>& data) noexcept;
    static RequestType getRequestType(std::bitset<64> type);
    static std::bitset<64> createRequestType(RequestType type);

  protected:
  private:
    static std::bitset<64> enumToBitset(unsigned int, std::bitset<64>) noexcept;
    static std::bitset<64> enumlistToBitset(
        const std::vector<pizza::Ingredients>& ingredients) noexcept;
    static std::size_t getDoubleFractional(double value) noexcept;
    static std::size_t bitsetToInt(const std::bitset<64>& data);
    static double findCookingTime(const std::bitset<64>& integral,
        const std::bitset<64>& fractional) noexcept;
    static std::vector<pizza::Ingredients> bitsetToIngredients(
        const std::bitset<64>& data) noexcept;
};
