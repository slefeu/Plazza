/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen handlers
*/

#include "Kitchen.hpp"

namespace plazza
{
Kitchen::Kitchen(
    unsigned int nb_cooks, int multiplier, unsigned int restock_time) noexcept
    : cooks_(threads::ThreadPool(nb_cooks))
    , max_pizza_(nb_cooks * 2)
    , multiplier_(multiplier)
    , fridge_(Fridge(restock_time))
{
}
} // namespace plazza