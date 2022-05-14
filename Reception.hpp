/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** Reception
*/

#pragma once

#include <map>
#include <string>
#include <vector>

#include "Factory.hpp"
#include "Pizza.hpp"
#include "Serializer.hpp"

namespace plazza
{
static constexpr std::string_view validIgredients =
    "Valid ingredients : Dough, Tomato, Gruyere, Ham, "
    "Mushrooms, Steak, Eggplant, GoatCheese, ChiefLove";
class Reception
{
  public:
    explicit Reception(char** av);
    Reception(const Reception& other) noexcept = default;
    Reception(Reception&& other) noexcept = default;
    ~Reception() noexcept = default;

    Reception& operator=(const Reception& rhs) noexcept = default;
    Reception& operator=(Reception&& rhs) noexcept = default;

    void executeShell();
    static std::string& trim(std::string&);

  protected:
  private:
    // methods
    static double parseArgument(const std::string& str);
    static bool checkPizzaNumber(std::string);
    void initPizzas();
    bool checkPizzaType(std::string&);
    bool checkPizzaSize(std::string&);
    void executeCommand();
    void orderPizza(std::string&);
    void checkOrderSyntax();
    bool checkOrder(std::string&);
    void setUserInput() noexcept;
    void addPizza();
    void exit() noexcept;
    void log();
    void list() noexcept;
    void status();
    // attributes
    std::string command_;
    std::vector<std::string> pizzaTypes_;
    std::map<std::string, pizza::PizzaSize> pizzaSizes_;
    std::map<std::string, pizza::Ingredients> ingredients_;
    int cooks_ = 0;
    double multiplier_ = 0;
    int time_ = 0;
    bool isEnd_ = false;
    Factory<pizza::Pizza> pizzaFactory_;
};
}