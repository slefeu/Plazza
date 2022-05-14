/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** PizzaSerializer
*/

#include "Serializer.hpp"
#include <map>

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
        value = enumToBitset(static_cast<unsigned int>(it), value);
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

std::array<std::bitset<64>, 5> PizzaSerializer::serializePizza(
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

std::bitset<8> serializeCommand(char name) noexcept
{
    std::bitset<8> command(name);
    return (command);
}

std::size_t PizzaSerializer::bitsetToInt(const std::bitset<64>& data)
{
    auto result = data.to_ulong();
    return (result);
}

double PizzaSerializer::findCookingTime(
    const std::bitset<64>& integral, const std::bitset<64>& fractional) noexcept
{
    auto first = integral.to_ulong();
    auto second = static_cast<double>(fractional.to_ulong());

    while (second >= 1)
        second = second / 10;
    return (first + second);
}

std::vector<pizza::Ingredients> PizzaSerializer::bitsetToIngredients(
    const std::bitset<64>& data) noexcept
{
    std::vector<pizza::Ingredients> ingredients = {};

    for (std::size_t it = 0; it < 9; ++it) {
        if (data[it]) {
            ingredients.emplace_back(static_cast<pizza::Ingredients>(it));
        }
    }
    return (ingredients);
}

pizza::Pizza PizzaSerializer::deserializePizza(
    const std::array<std::bitset<64>, 5>& data) noexcept
{
    auto type = static_cast<pizza::PizzaType>(data[0].to_ulong());
    auto size = static_cast<pizza::PizzaSize>(data[1].to_ulong());
    auto ingredients = bitsetToIngredients(data[2]);
    auto multiplier = findCookingTime(data[3], data[4]);
    pizza::Pizza pizza;

    static std::map<pizza::PizzaType, pizza::Pizza(double)> creator_ = {
        {pizza::PizzaType::Regina, pizza::PizzaRegina()},
        {pizza::PizzaType::Margarita, pizza::PizzaMargarita()},
        {pizza::PizzaType::Americana, pizza::PizzaAmericana()},
        {pizza::PizzaType::Fantasia, pizza::PizzaFantasia()},
    };
    auto iterator = creator_.find(type);

    if (iterator == creator_.end()) {
        auto pizza = pizza::Pizza(pizza::PizzaType::Custom, multiplier);
        for (auto it : ingredients)
            pizza.addIngredient(it);
    } else
        pizza = iterator->second(multiplier);
    pizza.setSize(size);
    return (pizza);
}