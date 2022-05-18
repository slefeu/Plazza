/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen handlers
*/

#include "Kitchen.hpp"

#include <iostream>

#include "DefaultPizzas.hpp"
#include "Factory.hpp"
#include "Serializer.hpp"

namespace plazza
{
Kitchen::Kitchen(double multiplier,
    unsigned int nb_cooks,
    unsigned int restock_time,
    std::unique_ptr<NamedPipe> pipe) noexcept
    : cooks_(nb_cooks)
    , nbCooks(nb_cooks)
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

void Kitchen::run() noexcept
{
    while (running_) {
        checkRequest();
        if (!clock_.getIdle()) {
            restock();
            tryMakePizzas();
            {
                std::unique_lock<std::mutex> lock(mutex_);
                if (waiting_.empty() && cooked_.empty() && cooking_.empty()) {
                    clock_.setIdle(true);
                }
            }
        } else {
            if (clock_.isIdle()) {
                shutdown();
            }
        }
    }
}

void Kitchen::tryMakePizzas() noexcept
{
    if (!waiting_.empty()) {
        auto task = createTask();
        if (task.has_value())
            cooks_.addTask(task.value());
        restock();
        clock_.setIdle(false);
    }
}

void Kitchen::addWaitPizza(pizza::Pizza pizza) noexcept
{
    waiting_.emplace(pizza);
}

std::optional<threads::Task> Kitchen::createTask() noexcept
{
    pizza::Pizza pizza = waiting_.front();
    auto list = pizza.getIngredients();

    if (!fridge_.hasEnough(list) || cooks_.getBusyThreads() == nbCooks)
        return (std::nullopt);
    fridge_.takeIngredients(list);
    waiting_.pop();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cooking_.emplace(pizza);
    }
    return ([this, pizza] { return plazza::Kitchen::task(pizza); });
}

void Kitchen::task(pizza::Pizza pizza) noexcept
{
    std::this_thread::sleep_for(Clock::getSeconds(pizza.getCookingTime()));
    std::unique_lock<std::mutex> lock(mutex_);
    remove(pizza);
    cooked_.emplace(pizza);
}

void Kitchen::sendAvailability() const noexcept
{
    if (waiting_.size() + cooking_.size() < nbCooks * 2) {
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

void Kitchen::displayWaitingPizzas() const noexcept
{
    auto list = waiting_;

    if (waiting_.empty()) {
        std::cout << "\nNo pizza waiting to be cooked" << std::endl;
    } else {
        std::cout << "\nPizzas waiting to be cooked :" << std::endl;
        for (std::size_t it = 0; it < list.size(); ++it) {
            std::cout << list.front() << std::endl;
            list.pop();
        }
    }
}

void Kitchen::displayBusyCooks() noexcept
{
    int count = 1;

    std::unique_lock<std::mutex> lock(mutex_);
    auto list = cooking_;

    std::cout << "\nBusy cooks :" << std::endl;
    for (std::size_t it = 0; it < list.size(); ++it) {
        std::cout << "Cook " << count
                  << " cooking: " << list.front().getPizzaType() << std::endl;
        list.pop();
        count++;
    }
}

void Kitchen::displayAvailableCooks() const noexcept
{
    std::cout << "\nAmount of available cooks :\n"
              << nbCooks - cooks_.getBusyThreads() << "/" << nbCooks
              << std::endl;
}

void Kitchen::getStatus() noexcept
{
    std::bitset<64> success =
        PizzaSerializer::createRequestType(RequestType::Success);

    std::cout << "Kitchen " << ::getpid() << " status :" << std::endl;
    fridge_.display();
    displayWaitingPizzas();
    displayAvailableCooks();
    displayBusyCooks();
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
            clock_.setIdle(false);
            addWaitPizza(getOrder());
        }
        if (requestType == RequestType::Status) {
            getStatus();
        }
    }
}

void Kitchen::restock() noexcept
{
    if (clock_.isNSeconds(fridge_.getRestockTime())) {
        fridge_.restock();
        clock_.resetStocks();
    }
}

void Kitchen::remove(pizza::Pizza pizza) noexcept
{
    std::queue<pizza::Pizza> reference_queue = {};
    unsigned long size = cooking_.size();
    unsigned int count = 0;

    while (cooking_.front() != pizza && !cooking_.empty()) {
        reference_queue.push(cooking_.front());
        cooking_.pop();
        count++;
    }
    if (cooking_.empty()) {
        while (!reference_queue.empty()) {
            cooking_.push(reference_queue.front());
            reference_queue.pop();
        }
    } else {
        cooking_.pop();
        while (!reference_queue.empty()) {
            cooking_.push(reference_queue.front());
            reference_queue.pop();
        }
        auto index = size - count - 1;
        while (index != 0) {
            auto elem = cooking_.front();
            cooking_.pop();
            cooking_.push(elem);
            --index;
        }
    }
}

bool operator!=(const pizza::Pizza& first, const pizza::Pizza& second) noexcept
{
    if (first.getPizzaType() != second.getPizzaType())
        return (true);
    if (first.getPizzaSize() != second.getPizzaSize())
        return (true);
    if (first.getCookingTime() != second.getCookingTime())
        return (true);
    if (first.getIngredients() != second.getIngredients())
        return (true);
    return (false);
}

} // namespace plazza