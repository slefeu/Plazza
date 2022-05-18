/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <unistd.h>

#include <memory>

#include "Clock.hpp"
#include "Fridge.hpp"
#include "NamedPipe.hpp"
#include "Threads.hpp"

namespace plazza
{
class Kitchen
{
  public:
    explicit Kitchen(double multiplier,
        unsigned int nb_cooks,
        unsigned int restock_time,
        std::unique_ptr<NamedPipe> pipe) noexcept;
    Kitchen(const Kitchen& other) noexcept = delete;
    Kitchen(Kitchen&& other) noexcept = delete;
    ~Kitchen() noexcept = default;

    Kitchen& operator=(const Kitchen& rhs) noexcept = delete;
    Kitchen& operator=(Kitchen&& rhs) noexcept = delete;
    void run() noexcept;

  protected:
  private:
    unsigned long nbCooks;
    threads::ThreadPool cooks_;
    double multiplier_;
    bool full_{false};
    bool running_{true};
    Clock clock_;
    Fridge fridge_;
    std::mutex mutex_;
    std::queue<pizza::Pizza> waiting_ = {};
    std::queue<pizza::Pizza> cooking_ = {};
    std::queue<pizza::Pizza> cooked_ = {};
    std::unique_ptr<NamedPipe> pipe_;

    void checkRequest() noexcept;
    void shutdown() noexcept;
    void task(pizza::Pizza) noexcept;
    std::optional<threads::Task> createTask() noexcept;
    void sendAvailability() const noexcept;
    pizza::Pizza getOrder() const noexcept;
    void sendBackCooked() noexcept;
    void sendPizza(pizza::Pizza pizza) const noexcept;
    void getStatus() noexcept;
    void restock() noexcept;
    void tryMakePizzas() noexcept;
    void addWaitPizza(pizza::Pizza) noexcept;
    void displayAvailableCooks() const noexcept;
    void displayBusyCooks() noexcept;
    void remove(pizza::Pizza) noexcept;
    void displayWaitingPizzas() const noexcept;
};

bool operator!=(const pizza::Pizza& first, const pizza::Pizza& second) noexcept;

} // namespace plazza