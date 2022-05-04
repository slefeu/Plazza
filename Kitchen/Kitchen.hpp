/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Kitchen
*/

#pragma once

class Kitchen
{
public:
    explicit Kitchen(unsigned int cooks) noexcept;
    Kitchen(const Kitchen &other) noexcept = default;
    Kitchen(Kitchen &&other) noexcept = default;
    ~Kitchen() noexcept = default;

    Kitchen &operator=(const Kitchen &rhs) noexcept = default;
    Kitchen &operator=(Kitchen &&rhs) noexcept = default;

protected:
private:
    unsigned int nbCooks = 0;
};