/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** Reception
*/

#include "Reception.hpp"
#include "DefaultPizzas.hpp"
#include "Factory.hpp"
#include "Pizza.hpp"

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

void Reception::initPizzas()
{
    double multiplier = multiplier_;
    pizzaFactory_.addElement("margarita", [&multiplier](){
        pizza::PizzaMargarita margarita(multiplier);
        return margarita;
    });
    pizzaFactory_.addElement("regina", [&multiplier](){
        pizza::PizzaRegina regina(multiplier);
        return regina;
    });
    pizzaFactory_.addElement("americana", [&multiplier](){
        pizza::PizzaAmericana americana(multiplier);
        return americana;
    });
    pizzaFactory_.addElement("fantasia", [&multiplier](){
        pizza::PizzaFantasia fantasia(multiplier);
        return fantasia;
    });
}

Reception::Reception(char** av)
{
    multiplier_ = parseArgument(av[1]);
    cooks_ = static_cast<int>(parseArgument(av[2]));
    time_ = static_cast<int>(parseArgument(av[3]));
    pizzaTypes_ = {"margarita", "regina", "americana", "fantasia"};
    pizzaSizes_ = {
        {"S", pizza::PizzaSize::S},
        {"M", pizza::PizzaSize::M},
        {"L", pizza::PizzaSize::L},
        {"XL", pizza::PizzaSize::XL},
        {"XXL", pizza::PizzaSize::XXL}
    };
    ingredients_ = {
        {"Dough", pizza::Ingredients::Dough},
        {"Tomato", pizza::Ingredients::Tomato},
        {"Gruyere", pizza::Ingredients::Gruyere},
        {"Ham", pizza::Ingredients::Ham},
        {"Mushrooms", pizza::Ingredients::Mushrooms},
        {"Steak", pizza::Ingredients::Steak},
        {"Eggplant", pizza::Ingredients::Eggplant},
        {"GoatCheese", pizza::Ingredients::GoatCheese},
        {"ChiefLove", pizza::Ingredients::ChiefLove}
    };
    initPizzas();
}

void Reception::setUserInput() noexcept
{
    std::string command;
    std::istream& stream = std::cin;

    getline(stream, command);
    if (stream.eof() || std::cin.fail()) {
        command_ = "";
        exit();
    } else {
        command_ = command;
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

void Reception::list()
{
    std::map<std::string, std::function<pizza::Pizza()>> pizzaList = pizzaFactory_.getAll();
    std::cout << "Pizza list : " << std::endl;
    for (auto const& [key, val] : pizzaList)
    {
        std::cout << "- " << key << std::endl;
    }
}

void Reception::addPizza()
{
    std::stringstream stream(trim(command_));
    std::string name;
    std::string ingredient;
    std::vector<pizza::Ingredients> ingredients;
    double pizza_multiplier = 0;
    double multiplier = multiplier_;

    if (std::count(command_.begin(), command_.end(), ' ') < 3) {
        throw(ExecutionError(
            "Usage : addPizza <name> <multiplier> ingredients [ingredients]"));
    }
    stream >> name >> name >> pizza_multiplier;
    while (!stream.eof()) {
        stream >> ingredient;
        if (ingredients_.find(ingredient) == ingredients_.end()) {
            throw(
                ExecutionError(
                    "Incorrect ingredient : " + ingredient +
                      "\nValid ingredients : Dough, Tomato, Gruyere, Ham, "
                      "Mushrooms, Steak, Eggplant, GoatCheese, ChiefLove"));
        }
        ingredients.emplace_back(ingredients_.find(ingredient)->second);
    }
    pizzaFactory_.addElement(
        name, [&multiplier, &pizza_multiplier, &ingredients]() {
            pizza::Pizza pizza(pizza::PizzaType::Custom, multiplier * pizza_multiplier);
            for (auto& value : ingredients) {
                pizza.addIngredients(value);
            }
            return pizza;
        });
}

std::string& Reception::trim(std::string& string)
{
    string.erase(string.begin(),
        std::find_if(string.begin(),
            string.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    string.erase(std::find_if(string.rbegin(),
                     string.rend(),
                     std::not1(std::ptr_fun<int, int>(std::isspace)))
                     .base(),
        string.end());
    return (string);
}

bool Reception::checkPizzaType(std::string& type)
{
    if (std::find_if_not(type.begin(), type.end(), ::isalpha) != type.end())
        return (false);
    if (std::find(pizzaTypes_.begin(), pizzaTypes_.end(), type)
        == pizzaTypes_.end())
        return (false);
    return (true);
}

bool Reception::checkPizzaSize(std::string& size)
{
    if (pizzaSizes_.find(size) == pizzaSizes_.end())
        return (false);
    return (true);
}

bool Reception::checkPizzaNumber(std::string number)
{
    if (number.at(0) != 'x')
        return (false);
    number.erase(0, 1);
    if (number.empty() || isdigit(number.at(0)) == 0 || number.at(0) == '0')
        return (false);
    number.erase(0, 1);
    if (std::find_if_not(number.begin(), number.end(), ::isdigit)
               != number.end())
        return (false);
    return (true);
}

bool Reception::checkOrder(std::string &order)
{
    std::stringstream stream(trim(order));
    std::string type;
    std::string size;
    std::string number;

    try {
        stream >> type >> size >> number;
        if (type.empty() || size.empty() || number.empty())
            throw(ExecutionError("Incorrect order : " + order));
        if (!checkPizzaType(type))
            throw(ExecutionError("Incorrect pizza type : " + type));
        if (!checkPizzaSize(size))
            throw(ExecutionError("Incorrect pizza size : " + size));
        if (!checkPizzaNumber(number))
            throw(ExecutionError("Incorrect pizza number : " + number));
    } catch (const ExecutionError &ex) {
        std::cerr << "Error : " << ex.what() << std::endl;
        return (false);
    }
    return (true);
}

void Reception::orderPizza(std::string &order)
{
    std::stringstream stream(trim(order));
    std::string type;
    std::string size;
    std::string number;

    stream >> type >> size >> number;
    pizza::Pizza pizza = pizzaFactory_.getElement(type);
    pizza.setPizzaSize(pizzaSizes_.find(size)->second);
    std::cout << pizza;
}

void Reception::checkOrderSyntax()
{
    size_t pos = 0;
    std::string order;

    while ((pos = command_.find(';')) != std::string::npos) {
        order = command_.substr(0, pos);
        if (checkOrder(order))
            orderPizza(order);
        command_.erase(0, pos + 1);
    }
    if (checkOrder(command_))
        orderPizza(command_);
}

void Reception::executeCommand()
{
    static std::map<std::string, void (Reception::*)()> creator = {
        {"exit", &Reception::exit},
        {"log", &Reception::log},
        {"list", &Reception::list},
        {"status", &Reception::status},
        {"addPizza", &Reception::addPizza},
    };

    command_ = trim(command_);

    if (command_.empty())
        return;
    for (auto const& [key, val] : creator)
    {
        if (command_.rfind(key, 0) == 0) {
            return (((*this).*(val))());
        }
    }
    checkOrderSyntax();
}

void Reception::executeShell()
{
    while (!isEnd_) {
        std::cout << "> ";
        try {
            setUserInput();
            executeCommand();
        } catch (const Error& error) {
            std ::cout << error.what() << std ::endl;
        }
    }
}
} // namespace plazza