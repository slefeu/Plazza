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
    explicit Kitchen(unsigned int nb_cooks,
        int multiplier,
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
    int multiplier_;
    bool full_{false};
    bool running_{true};
    Clock clock_;
    Fridge fridge_;
    std::mutex mutex_;
    std::queue<std::unique_ptr<pizza::APizza>> waiting_ = {};
    std::queue<std::unique_ptr<pizza::APizza>> cooking_ = {};
    std::queue<std::unique_ptr<pizza::APizza>> cooked_ = {};

    // method
    void shutdown() noexcept;
    void task(const pizza::APizza pizza) noexcept;
    std::optional<threads::Task> createTask() noexcept;
};
} // namespace plazza