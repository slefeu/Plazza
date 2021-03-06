/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** Reception
*/

#include "Reception.hpp"

#include <poll.h>

#include <bitset>
#include <csignal>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>

#include "DefaultPizzas.hpp"
#include "Errors.hpp"
#include "Factory.hpp"
#include "Kitchen.hpp"
#include "KitchenProcess.hpp"
#include "NamedPipe.hpp"
#include "Pizza.hpp"
#include "Process.hpp"
#include "Serializer.hpp"

namespace plazza
{
static bool isDigits(const std::string& str)
{
    return (str.find_first_not_of("0123456789.") == std::string::npos);
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
    double& multiplier = multiplier_;

    pizzaFactory_.addElement("margarita", [&multiplier]() {
        pizza::PizzaMargarita margarita(multiplier);
        return margarita;
    });
    pizzaFactory_.addElement("regina", [&multiplier]() {
        pizza::PizzaRegina regina(multiplier);
        return regina;
    });
    pizzaFactory_.addElement("americana", [&multiplier]() {
        pizza::PizzaAmericana americana(multiplier);
        return americana;
    });
    pizzaFactory_.addElement("fantasia", [&multiplier]() {
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
    pizzaSizes_ = {{"S", pizza::PizzaSize::S},
        {"M", pizza::PizzaSize::M},
        {"L", pizza::PizzaSize::L},
        {"XL", pizza::PizzaSize::XL},
        {"XXL", pizza::PizzaSize::XXL}};
    ingredients_ = {{"Dough", pizza::Ingredients::Dough},
        {"Tomato", pizza::Ingredients::Tomato},
        {"Gruyere", pizza::Ingredients::Gruyere},
        {"Ham", pizza::Ingredients::Ham},
        {"Mushrooms", pizza::Ingredients::Mushrooms},
        {"Steak", pizza::Ingredients::Steak},
        {"Eggplant", pizza::Ingredients::Eggplant},
        {"GoatCheese", pizza::Ingredients::GoatCheese},
        {"ChiefLove", pizza::Ingredients::ChiefLove}};
    initPizzas();
    std::ofstream ofs;
    ofs.open("history.log", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void Reception::setUserInput() noexcept
{
    std::string command;
    struct pollfd pfd = { STDIN_FILENO, POLLIN, 0 };

    int ret = poll(&pfd, 1, 1000);
    if (ret == 1) {
        getline(std::cin, command);
        if (std::cin.eof() || std::cin.fail()) {
            command_ = "";
            exit();
        } else {
            command_ = command;
        }
    } else if (ret == 0) {
        command_ = "";
    }
}

void Reception::exit() noexcept
{
    isEnd_ = true;

    for (KitchenProcess& kitchen : kitchens_) {
        kitchen.getProcess().kill();
    }
}

void Reception::status()
{
    cleanKitchens();
    if (kitchens_.empty())
        std::cout << "[RECEPTION] No kitchen running" << std::endl;
    for (KitchenProcess& kitchen : kitchens_) {
        kitchen.getPipe().write(IPCDirection::OUT,
            PizzaSerializer::createRequestType(RequestType::Status));
        PizzaSerializer::getRequestType(
            kitchen.getPipe().read(IPCDirection::IN, true));
    }
}

void Reception::list() noexcept
{
    std::map<std::string, std::function<pizza::Pizza()>> pizzaList =
        pizzaFactory_.getAll();
    std::cout << "[RECEPTION] Pizza list : " << std::endl;
    for (auto const& [key, val] : pizzaList) {
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
            throw(ExecutionError("Incorrect ingredient : " + ingredient + "\n"
                                 + validIgredients.data()));
        }
        ingredients.emplace_back(ingredients_.find(ingredient)->second);
    }
    pizzaFactory_.addElement(
        name, [multiplier, pizza_multiplier, ingredients]() {
            pizza::Pizza pizza(
                pizza::PizzaType::Custom, multiplier * pizza_multiplier);
            for (auto value : ingredients) {
                pizza.addIngredient(value);
            }
            return (pizza);
        });
    pizzaTypes_.push_back(name);
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

bool Reception::checkOrder(std::string& order)
{
    std::stringstream stream(trim(order));
    std::string type;
    std::string size;
    std::string number;

    try {
        stream >> type >> size >> number;
        if (type.empty() || size.empty() || number.empty())
            throw(ExecutionError("Invalid command : " + order));
        if (!checkPizzaType(type))
            throw(ExecutionError("Invalid pizza type : " + type));
        if (!checkPizzaSize(size))
            throw(ExecutionError("Invalid pizza size : " + size));
        if (!checkPizzaNumber(number))
            throw(ExecutionError("Invalid pizza number : " + number));
    } catch (const ExecutionError& ex) {
        std::cerr << ex.what() << std::endl;
        return (false);
    }
    return (true);
}

void Reception::sendPizza(KitchenProcess& kitchen, pizza::Pizza pizza)
{
    std::array<std::bitset<64>, PizzaSerializer::ARRAY_SIZE> pizza_serialized =
        PizzaSerializer::serializePizza(pizza);

    kitchen.getPipe().write(IPCDirection::OUT,
        PizzaSerializer::createRequestType(RequestType::Order));
    kitchen.getPipe().read(IPCDirection::IN, true);
    for (const std::bitset<64>& bitset : pizza_serialized) {
        kitchen.getPipe().write(IPCDirection::OUT, bitset);
        kitchen.getPipe().read(IPCDirection::IN, true);
    }
}

void Reception::orderPizza(std::string& order)
{
    std::stringstream stream(trim(order));
    std::string type;
    std::string size;
    std::string number;

    stream >> type >> size >> number;
    pizza::Pizza pizza = pizzaFactory_.getElement(type);
    pizza.setSize(pizzaSizes_.find(size)->second);
    number.erase(0, 1);
    for (int i = 0; i < std::stoi(number); i++) {
        KitchenProcess& kitchen = getKitchen();
        sendPizza(kitchen, pizza);
        std::cout << "[RECEPTION] Pizza send to kitchen " << kitchen.getProcess().getPid() << " : " << pizza << std::endl;;
    }
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
        {"list", &Reception::list},
        {"status", &Reception::status},
        {"addPizza", &Reception::addPizza},
    };

    command_ = trim(command_);

    if (command_.empty())
        return;
    for (auto const& [key, val] : creator) {
        if (command_.rfind(key, 0) == 0
            && (command_[key.length()] == ' '
                || command_[key.length()] == '\0')) {
            return (((*this).*(val))());
        }
    }
    checkOrderSyntax();
}

void Reception::checkCookedPizza()
{
    RequestType answer = RequestType::Empty;

    for (KitchenProcess& kitchen : kitchens_) {
        answer = PizzaSerializer::getRequestType(kitchen.getPipe().read(IPCDirection::IN, false));
        if (answer == RequestType::Cooked) {
            getCookedPizza(kitchen);
        }
    } 
}

pizza::Pizza Reception::getPizza(KitchenProcess& kitchen)
{
    std::array<std::bitset<64>, 5> packed = {};
    std::bitset<64> success =
        PizzaSerializer::createRequestType(RequestType::Success);

    for (int i = 0; i < 5; i++) {
        packed[i] = kitchen.getPipe().read(IPCDirection::IN, true);
        kitchen.getPipe().write(IPCDirection::OUT, success);
    }
    return (PizzaSerializer::deserializePizza(packed));
}

void Reception::addLog(std::string string) noexcept
{
    std::time_t time = std::time(nullptr);
    std::tm* now = std::localtime(&time);
    std::ofstream fout("history.log", std::ios_base::app);

    if(fout.is_open()) {
        fout << "[" << std::put_time(now,"%Y/%m/%d %T") << "] " << string << std::endl;
    }
    fout.close();
}

void Reception::addLog(pizza::Pizza &pizza) noexcept
{
    std::time_t time = std::time(nullptr);
    std::tm* now = std::localtime(&time);
    std::ofstream fout("history.log", std::ios_base::app);

    if(fout.is_open()) {
        fout << "[" << std::put_time(now,"%Y/%m/%d %T") << "] " << pizza << std::endl;
    }
    fout.close();
}

void Reception::getCookedPizza(KitchenProcess& kitchen)
{
    kitchen.getPipe().write(IPCDirection::OUT,
        PizzaSerializer::createRequestType(RequestType::Success));
    unsigned long count = kitchen.getPipe().read(IPCDirection::IN, true).to_ulong();
    kitchen.getPipe().write(IPCDirection::OUT,
        PizzaSerializer::createRequestType(RequestType::Success));
    std::cout << "[RECEPTION] " << count << " pizzas cooked and ready from " << kitchen.getProcess().getPid() << " : " << std::endl;
    for (int i = 0; i < count; i++) {
        pizza::Pizza pizza = getPizza(kitchen);
        std::cout << "[RECEPTION] " << pizza << std::endl;
        addLog(pizza);
    }
}

void Reception::executeShell()
{
    while (!isEnd_) {
        try {
            setUserInput();
            checkCookedPizza();
            if (!command_ .empty()) {
                executeCommand();
            }
        } catch (const Error& error) {
            std ::cout << error.what() << std ::endl;
        }
    }
}

KitchenProcess& Reception::createKitchen()
{
    std::unique_ptr<Process> process = std::make_unique<Process>();
    std::unique_ptr<NamedPipe> pipe =
        std::make_unique<NamedPipe>(std::to_string(process->getPid()));

    if (process->isChild()) {
        Kitchen kitchen(multiplier_, cooks_, time_, std::move(pipe));
        kitchen.run();
        process->kill();
    }
    kitchens_.emplace_back(std::move(process), std::move(pipe));
    return (kitchens_.back());
}

void Reception::cleanKitchens() noexcept
{
    auto new_end = std::remove_if(kitchens_.begin(),
        kitchens_.end(),
        [](KitchenProcess& val) { return !val.getProcess().isRunning(); });
    kitchens_.erase(new_end, kitchens_.end());
}

KitchenProcess& Reception::getKitchen()
{
    RequestType answer = RequestType::Empty;
    cleanKitchens();

    for (KitchenProcess& kitchen : kitchens_) {
        kitchen.getPipe().write(IPCDirection::OUT,
            PizzaSerializer::createRequestType(RequestType::Availability));
        answer = PizzaSerializer::getRequestType(
            kitchen.getPipe().read(IPCDirection::IN, true));
        if (answer == RequestType::Success) {
            return (kitchen);
        }
    }
    return (createKitchen());
}

} // namespace plazza