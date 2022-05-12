/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen handlers
*/

#include "Kitchen.hpp"

#include <iostream> //pour des prints de débug

#include "DefaultPizzas.hpp"
#include "Errors.hpp"
#include "Factory.hpp"

namespace plazza
{
Kitchen::Kitchen(double multiplier,
    unsigned int nb_cooks,
    unsigned int restock_time) noexcept
    : cooks_(nb_cooks)
    , max_pizza_(nb_cooks * 2)
    , multiplier_(multiplier)
    , fridge_(Fridge(restock_time / 1000))
{
}

void Kitchen::shutdown() noexcept
{
    running_ = false;
}

void Kitchen::addWaitPizza(const pizza::PizzaType type,
    const pizza::PizzaSize size,
    const double multiplier)
{
    // waiting_.emplace(Factory::createPizza(type, size, multiplier));
}

std::optional<threads::Task> Kitchen::createTask() noexcept
{
    pizza::Pizza pizza = waiting_.front();
    auto list = pizza.getIngredients();

    if (!fridge_.hasEnough(list))
        return (std::nullopt);
    fridge_.takeIngredients(list);
    waiting_.pop();
    return ([this, pizza] { return plazza::Kitchen::task(pizza); });
}

void Kitchen::tryMakePizzas() noexcept
{
    while (!waiting_.empty()) {
        auto task = createTask();
        if (task.has_value())
            cooks_.addTask(task.value());
    }
    cooks_.waitForExecution();
}

void Kitchen::run() noexcept
{
    // quand on va recevoir une pizza, voilà le format pour essayer de la mettre
    // dans la waiting list
    //  try {
    //      addWaitPizza(pizza::Americana, pizza::PizzaSize::M, 1);
    //  } catch (const ExecutionError& error) {
    //      std ::cout << error.what() << std ::endl;
    //  }
    //  il va falloir checker la quantité de pizzas dans waiting + cooked pour
    //  voir si ça dépasse pas max_pizza !!
    //à faire soit dans addPizza, soit dans l'IPC ?
    // manque la méthode pour enlever les pizzas de la kitchen du coup (pour pop
    // de cooked)
    while (running_) {
        if (!clock_.getIdle()) {
            if (clock_.isNSeconds(fridge_.getRestockTime()))
                fridge_.restock();
            {
                std::unique_lock<std::mutex> lock(mutex_);
                if (waiting_.empty()
                    && cooked_.empty()) // va loop à l'infinie car je pop pas
                                        // dans cooked pour l'instant
                    clock_.setIdle(true);
            }
            tryMakePizzas();
        } else {
            if (clock_.isIdle()) {
                shutdown();
            }
        }
    }
}

void Kitchen::task(pizza::Pizza pizza) noexcept
{
    std::this_thread::sleep_for(Clock::getSeconds(pizza.getCookingTime()));
    std::unique_lock<std::mutex> lock(mutex_);
    cooked_.emplace(pizza);
}

} // namespace plazza