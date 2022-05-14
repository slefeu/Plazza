/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** main
*/
#include <iostream>

#include "DefaultPizzas.hpp"
#include "Errors.hpp"
#include "Reception.hpp"
#include "Serializer.hpp"

#include <vector>

int main()
{
    // if (ac != 4) {
    //     std::cerr << "Not the right amount of arguments" << std::endl;
    //     return (84);
    // }
    // try {
    //     plazza::Reception plazzaReception(av);
    //     plazzaReception.executeShell();
    // } catch (Error const& error) {
    //     std::cerr << error.what() << std::endl;
    //     return (84);
    // }
    auto pizza = pizza::PizzaRegina(10.3);
    auto objectAttribute = PizzaSerializer::serializePizza(pizza);
    auto new_pizza = PizzaSerializer::deserializePizza(objectAttribute);
    return (0);
}
