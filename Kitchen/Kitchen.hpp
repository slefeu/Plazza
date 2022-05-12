/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <memory>

#include "Clock.hpp"
#include "Fridge.hpp"
#include "Threads.hpp"

namespace plazza
{
class Kitchen
{
  public:
    explicit Kitchen(double multiplier,
        unsigned int nb_cooks,
        unsigned int restock_time) noexcept;
    Kitchen(const Kitchen& other) noexcept = delete;
    Kitchen(Kitchen&& other) noexcept = delete;
    ~Kitchen() noexcept = default;

    Kitchen& operator=(const Kitchen& rhs) noexcept = delete;
    Kitchen& operator=(Kitchen&& rhs) noexcept = delete;
    void run() noexcept; // à mettre en private quand la kitchen fonctionnera

  protected:
  private:
    threads::ThreadPool cooks_;
    unsigned int max_pizza_;
    double multiplier_;
    bool full_{false};
    bool running_{true};
    Clock clock_;
    Fridge fridge_;
    std::mutex mutex_;
    std::queue<pizza::Pizza> waiting_ = {};
    std::queue<pizza::Pizza> cooked_ = {};

    // methods
    void shutdown() noexcept;
    void task(pizza::Pizza pizza) noexcept;
    std::optional<threads::Task> createTask() noexcept;
    void tryMakePizzas() noexcept;
    void addWaitPizza(pizza::PizzaType, pizza::PizzaSize, double);
};
} // namespace plazza