/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen handlers
*/

#include "Kitchen.hpp"

#include <iostream> //pour des prints de débug

#include "DefaultPizzas.hpp"
#include "Pizzas/APizza.hpp"

namespace plazza
{

Kitchen::Kitchen(
    unsigned int nb_cooks, int multiplier, unsigned int restock_time) noexcept
    : cooks_(nb_cooks)
    , max_pizza_(nb_cooks * 2)
    , multiplier_(multiplier)
    , fridge_(Fridge(restock_time))
{
}

void Kitchen::shutdown() noexcept
{
    running_ = false;
}

std::optionalthreads::Task Kitchen::createTask() noexcept
{
    const std::unique_ptr<pizza::APizza>& pizza_ptr = waiting_.front();
    const pizza::APizza pizza = *pizza_ptr;

    cooking_.emplace(std::make_unique<pizza::APizza>(pizza));
    waiting_.pop();
    return ([pizza, this] { return plazza::Kitchen::task(pizza); });
}

void Kitchen::run() noexcept
{
    waiting_.emplace(
        std::make_unique<pizza::APizza>(pizza::Regina, pizza::PizzaSize::M, 1));
    waiting_.emplace(
        std::make_unique<pizza::APizza>(pizza::Regina, pizza::PizzaSize::M, 1));
    waiting_.emplace(
        std::make_unique<pizza::APizza>(pizza::Regina, pizza::PizzaSize::M, 1));

    cooks_.addTask(createTask());
    cooks_.addTask(createTask());
    cooks_.addTask(createTask());
    cooks_.waitForExecution();

    // while (running_) {
    //     if (!clock_.getIdle()) {
    //         if (clock_.isNSeconds(fridge_.getRestockTime())) {
    //             fridge_.restock();
    //         }
    //         // if (waiting_.empty() && cooked_.empty()) {
    //         //     clock_.setIdle(true);
    //         //     std::cout << "is idle\n";
    //         // }
    //     } else {
    //         if (clock_.isIdle()) {
    //             shutdown();
    //         }
    //     }
    // }
}

void Kitchen::task(const pizza::APizza pizza) noexcept
{
    std::this_thread::sleep_for(std::chrono::seconds(pizza.getCookingTime()));
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cooked_.emplace(std::make_unique<pizza::APizza>(pizza));
        std::cout << "pizza " << static_cast<int>(pizza.getPizzaType())
                  << " cooked\n";
    }
}

} // namespace plazza