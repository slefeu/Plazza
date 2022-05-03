/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** Reception
*/

#include "Reception.hpp"

#include <csignal>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>

#include "Errors.hpp"

namespace plazza
{
static bool isDigits(const std::string& str)
{
    return (str.find_first_not_of("0123456789") == std::string::npos);
}

double Reception::parseArgument(const std::string& str)
{
    std::stringstream stream(str);
    double number = 0;

    if (!plazza::isDigits(str) || (stream >> number).fail())
        throw(ArgumentError("Error, Wrong argument format."));
    return number;
}

Reception::Reception(char** av)
{
    multiplier_ = parseArgument(av[1]);
    cooks_ = static_cast<int>(parseArgument(av[2]));
    time_ = static_cast<int>(parseArgument(av[3]));
}

void Reception::setUserInput() noexcept
{
    std::string command;

    if (getline(std::cin, command) && std::cin.good())
        command_ = command;
    else {
        command_ = "";
        exit();
    }
}

void Reception::exit() noexcept
{
    isEnd_ = true;
}

void Reception::log()
{
}

void Reception::status()
{
}

void Reception::executeCommand()
{
    static std::map<std::string, void (Reception::*)()> creator = {
        {"exit", &Reception::exit},
        {"log", &Reception::log},
        {"status", &Reception::status},
    };
    // rajouter la commande pour lancer la commande de pizzas

    command_.erase(
        std::remove(command_.begin(), command_.end(), ' '), command_.end());
    command_.erase(
        std::remove(command_.begin(), command_.end(), '\t'), command_.end());

    auto iterator = creator.find(command_);

    if (iterator != creator.end())
        return (((*this).*(iterator->second))());
    if (!command_.empty())
        throw(ExecutionError("Command not found."));
}

namespace
{
std::function<void()> shutdownHandler;
void signalHandler(__attribute__((unused)) int signal)
{
    shutdownHandler();
}
} // namespace anonyme pour faire passer le contexte

void Reception::executeShell()
{
    shutdownHandler = [this]() { this->exit(); };
    std::signal(SIGINT, signalHandler);
    while (!isEnd_) {
        std::cout << "> ";
        try {
            setUserInput();
            executeCommand();
        } catch (const Error& e) {
            std ::cout << e.what() << std ::endl;
        }
    }
}
} // namespace plazza