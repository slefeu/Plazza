/*
** EPITECH PROJECT, 2022
** Plazza
** File description: hpp file
** PizzaFactory
*/

#ifndef PIZZAFACTORY_
#define PIZZAFACTORY_

namespace pizza {
class PizzaFactory {
    public:
        PizzaFactory() noexcept = default;
        PizzaFactory(PizzaFactory const &other) noexcept = default;
        PizzaFactory(PizzaFactory &&other) noexcept = default;
        PizzaFactory &operator=(PizzaFactory const &other) noexcept = default;
        PizzaFactory &operator=(PizzaFactory &&other) noexcept = default;
        ~PizzaFactory() noexcept = default;
    private:
        
};
}

#endif /* !PIZZAFACTORY_*/