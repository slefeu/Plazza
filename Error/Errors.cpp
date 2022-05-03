/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** Errors
*/

#include "Errors.hpp"

Error::Error(std::string message) noexcept
    : message_(std::move(message)){};

const char* Error::what() const noexcept
{
    return (message_.c_str());
}

ArgumentError::ArgumentError(std::string message) noexcept
    : Error(std::move(message)){};

ExecutionError::ExecutionError(std::string message) noexcept
    : Error(std::move(message)){};