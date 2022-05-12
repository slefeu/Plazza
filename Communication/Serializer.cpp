/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** PizzaSerializer
*/

#include "Serializer.hpp"

std::bitset<64> PizzaSerializer::enumToBitset(
    unsigned int enum_value, std::bitset<64> value) noexcept
{
    value |= enum_value;
    return (value);
}

std::bitset<64> PizzaSerializer::enumlistToBitset(
    const std::vector<pizza::Ingredients>& ingredients) noexcept
{
    std::bitset<64> value(std::string(
        "0000000000000000000000000000000000000000000000000000000000000000"));
    for (auto it : ingredients) {
        value = enumToBitset(static_cast<int>(it), value);
    }
    return (value);
}

std::size_t PizzaSerializer::getDoubleFractional(double value) noexcept
{
    value *= 10000000;
    auto new_value = static_cast<std::size_t>(value);
    while ((new_value % 10) == 0)
        new_value /= 10;
    return (new_value);
}

std::array<std::bitset<64>, 5> PizzaSerializer::serialize(
    const pizza::Pizza& pizza) noexcept
{
    std::array<std::bitset<64>, 5> packed = {};
    std::bitset<64> default_bits(std::string(
        "0000000000000000000000000000000000000000000000000000000000000000 "));
    double time = pizza.getCookingTime();
    std::bitset<64> integral(time);
    std::bitset<64> fractional(
        getDoubleFractional(time - static_cast<std::size_t>(time)));

    packed[0] =
        enumToBitset(static_cast<int>(pizza.getPizzaType()), default_bits);
    packed[1] =
        enumToBitset(static_cast<int>(pizza.getPizzaSize()), default_bits);
    packed[2] = enumlistToBitset(pizza.getIngredients());
    packed[3] = integral;
    packed[4] = fractional;
    return (packed);
}

// unsigned int PizzaSerializer::bitsetToInt(const std::bitset<64>& data)
// {
//     auto result = long(data.to_ulong()));
//     return (result);
// }

// std::vector<pizza::Ingredients> PizzaSerializer::bitsetToIngredients(
//     std::bitset<64>)
// {
// }

// pizza::Pizza PizzaSerializer::deserialize(const std::array<std::bitset<64>,
// 4> &data)
// {
//     pizza::PizzaType type = bitsetToInt(data[0]);
//     pizza::PizzaSize size = bitsetToInt(data[1]);
//     std::vector<pizza::Ingredients> = bitsetToIngredients(data[2]);
//     double multiplier = data[3];

//     pizza::Pizza
// }