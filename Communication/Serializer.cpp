/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** PizzaSerializer
*/

#include "Serializer.hpp"

#include <cmath>
#include <map>

/**
 * @brief Convert an enum to a bitset
 *
 * @param enum_value The enum to convert
 * @param value The bitset to fill
 * @return std::bitset<64> The filled bitset
 */
std::bitset<64> PizzaSerializer::enumToBitset(
    unsigned int enum_value, std::bitset<64> value) noexcept
{
    value |= enum_value;
    return (value);
}

/**
 * @brief Convert a list of enum to a bitset
 *
 * @param ingredients The list of enum to convert
 * @return std::bitset<64> The filled bitset
 */
std::bitset<64> PizzaSerializer::enumlistToBitset(
    const std::vector<pizza::Ingredients>& ingredients) noexcept
{
    std::bitset<64> value;
    for (auto it : ingredients) {
        value = enumToBitset(static_cast<unsigned int>(it), value);
    }
    return (value);
}

/**
 * @brief Get the fractional part of a double
 *
 * @param value The double to get the fractional part
 * @return std::size_t The fractional part
 */
std::size_t PizzaSerializer::getDoubleFractional(double value) noexcept
{
    value *= 10000000;
    auto new_value = static_cast<std::size_t>(value);
    while ((new_value % 10) == 0 && new_value != 0)
        new_value /= 10;
    return (new_value);
}

/**
 * @brief Serialize a pizza
 *
 * @param pizza The pizza to serialize
 * @return std::array<std::bitset<64>, PizzaSerializer::ARRAY_SIZE> The serialized pizza
 */
std::array<std::bitset<64>, PizzaSerializer::ARRAY_SIZE>
PizzaSerializer::serializePizza(const pizza::Pizza& pizza) noexcept
{
    std::array<std::bitset<64>, 5> packed = {};
    std::bitset<64> default_bits;
    double time = pizza.getCookingTime();
    auto integral_value = static_cast<unsigned int>(time);
    std::bitset<64> integral(integral_value);
    std::bitset<64> fractional(getDoubleFractional(time - integral_value));

    packed[0] =
        enumToBitset(static_cast<int>(pizza.getPizzaType()), default_bits);
    packed[1] =
        enumToBitset(static_cast<int>(pizza.getPizzaSize()), default_bits);
    packed[2] = enumlistToBitset(pizza.getIngredients());
    packed[3] = integral;
    packed[4] = fractional;
    return (packed);
}

/**
 * @brief Serialize a command
 *
 * @param name The command to serialize
 * @return std::bitset<8> The serialized command
 */
std::bitset<8> serializeCommand(char name) noexcept
{
    std::bitset<8> command(name);
    return (command);
}

/**
 * @brief Convert a bitset to an int
 *
 * @param data The bitset to convert
 * @return std::size_t The converted bitset
 */
std::size_t PizzaSerializer::bitsetToInt(const std::bitset<64>& data)
{
    auto result = data.to_ulong();
    return (result);
}

/**
 * @brief Find the cooking time of a pizza
 *
 * @param integral The integral part of the cooking time
 * @param fractional The fractional part of the cooking time
 * @return double The cooking time
 */
double PizzaSerializer::findCookingTime(
    const std::bitset<64>& integral, const std::bitset<64>& fractional) noexcept
{
    auto first = static_cast<unsigned int>(integral.to_ulong());
    auto second = static_cast<double>(fractional.to_ulong());

    while (second >= 1)
        second = second / 10;
    return (first + second);
}

/**
 * @brief Convert a bitset to a list of ingredients
 *
 * @param data The bitset to convert
 * @return std::vector<pizza::Ingredients> The converted bitset
 */
std::vector<pizza::Ingredients> PizzaSerializer::bitsetToIngredients(
    const std::bitset<64>& data) noexcept
{
    std::vector<pizza::Ingredients> ingredients = {};

    for (std::size_t it = 0; it < 9; ++it) {
        if (data[it]) {
            ingredients.emplace_back(
                static_cast<pizza::Ingredients>(std::pow(2, it)));
        }
    }
    return (ingredients);
}

/**
 * @brief Deserialize a pizza
 *
 * @param data The pizza to deserialize
 * @return pizza::Pizza The deserialized pizza
 */
pizza::Pizza PizzaSerializer::deserializePizza(
    const std::array<std::bitset<64>, PizzaSerializer::ARRAY_SIZE>&
        data) noexcept
{
    auto type = static_cast<pizza::PizzaType>(data[0].to_ulong());
    auto size = static_cast<pizza::PizzaSize>(data[1].to_ulong());
    auto ingredients = bitsetToIngredients(data[2]);
    auto multiplier = findCookingTime(data[3], data[4]);
    pizza::Pizza pizza(type, multiplier);

    for (auto it : ingredients)
        pizza.addIngredient(it);
    pizza.setSize(size);
    return (pizza);
}
/**
 * @brief Get the request type of a bitset
 *
 * @param type The bitset to convert
 * @return RequestType The converted bitset
 */

RequestType PizzaSerializer::getRequestType(std::bitset<64> type)
{
    for (int i = 0; i < 6; i++) {
        if (type == std::bitset<64>(static_cast<unsigned long long>(std::pow(2, i)))) {
            return (static_cast<RequestType>(std::pow(2, i)));
        }
    }
    return (RequestType::Empty);
}

/**
 * @brief Create a request type
 *
 * @param type The request type to create
 * @return std::bitset<64> The created request type
 */
std::bitset<64> PizzaSerializer::createRequestType(RequestType type)
{
    return {std::bitset<64>(static_cast<int>(type))};
}