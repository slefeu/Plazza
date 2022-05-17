/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen handlers
*/

#include "Kitchen.hpp"

#include <unistd.h>

#include <bitset>
#include <iostream> //pour des prints de débug
#include <utility>

#include "DefaultPizzas.hpp"
#include "Errors.hpp"
#include "Factory.hpp"
#include "NamedPipe.hpp"
#include "Pizza.hpp"
#include "Serializer.hpp"

namespace plazza
{
Kitchen::Kitchen(double multiplier,
    unsigned int nb_cooks,
    unsigned int restock_time,
    std::unique_ptr<NamedPipe> pipe) noexcept
    : cooks_(nb_cooks)
    , max_pizza_(nb_cooks * 2)
    , multiplier_(multiplier)
    , fridge_(Fridge(restock_time / 1000))
    , pipe_(std::move(pipe))
{
}

void Kitchen::shutdown() noexcept
{
    running_ = false;
    pipe_->close();
}

void Kitchen::addWaitPizza(pizza::Pizza pizza)
{
    waiting_.emplace(pizza);
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

void Kitchen::sendAvailability() const noexcept
{
    // TODO(slefeu): Ajouter une condition de vérification de disponiblité
    if (true) {
        pipe_->write(IPCDirection::IN,
            PizzaSerializer::createRequestType(RequestType::Success));
    } else {
        pipe_->write(IPCDirection::IN,
            PizzaSerializer::createRequestType(RequestType::Error));
    }
}

pizza::Pizza Kitchen::getOrder() const noexcept
{
    IPCDirection dir_in = IPCDirection::IN;
    IPCDirection dir_out = IPCDirection::OUT;
    std::bitset<64> success =
        PizzaSerializer::createRequestType(RequestType::Success);
    std::array<std::bitset<64>, 5> packed = {};

    pipe_->write(IPCDirection::IN, success);
    for (int i = 0; i < 5; i++) {
        packed[i] = pipe_->read(IPCDirection::OUT, true);
        pipe_->write(IPCDirection::IN, success);
    }
    return (PizzaSerializer::deserializePizza(packed));
}

void Kitchen::getStatus() const noexcept
{
    std::bitset<64> success =
        PizzaSerializer::createRequestType(RequestType::Success);

    std::cout << "Status : yes" << std::endl;
    fridge_.display();
    // TODO(slefeu) : Print les trucs de la kitchen
    pipe_->write(IPCDirection::IN, success);
}

void Kitchen::checkRequest() noexcept
{
    std::bitset<64> request = pipe_->read(IPCDirection::OUT, false);
    RequestType requestType = PizzaSerializer::getRequestType(request);

    if (requestType != RequestType::Empty) {
        clock_.reset();
        if (requestType == RequestType::Availability) {
            sendAvailability();
        }
        if (requestType == RequestType::Order) {
            addWaitPizza(getOrder());
        }
        if (requestType == RequestType::Status) {
            getStatus();
        }
    }
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
        checkRequest();
        if (!clock_.getIdle()) {
            if (clock_.isNSeconds(fridge_.getRestockTime())) {
                fridge_.restock();
                clock_.resetStocks();
            }
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