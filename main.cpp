/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** main
*/

#include <iostream>

#include "Errors.hpp"
#include "Reception.hpp"

int main(int ac, char** av)
{
    if (ac != 4) {
        std::cerr << "Not the right amount of arguments" << std::endl;
        return (ERROR_CODE);
    }
    try {
        plazza::Reception plazzaReception(av);
        plazzaReception.executeShell();
    } catch (Error const& error) {
        std::cerr << error.what() << std::endl;
        return (ERROR_CODE);
    }
    return (SUCCESS_CODE);
}
