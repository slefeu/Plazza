/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Factory
*/

#include "Factory.hpp"

#include <functional>
#include <iostream>
#include <map>

#include "Errors.hpp"

template <typename ElementType>
void Factory<ElementType>::addElement(
    std::string name, std::function<ElementType()> element) noexcept
{
    if (elements_.find(name) == elements_.end()) {
        elements_.emplace(name, element);
    }
}

template <typename ElementType>
ElementType Factory<ElementType>::getElement(std::string& name)
{
    if (elements_.find(name) != elements_.end()) {
        return elements_[name]();
    }
    throw(ExecutionError("Incorrect element name"));
}

template <typename ElementType>
void Factory<ElementType>::removeElement(std::string& name)
{
    if (elements_.find(name) == elements_.end()) {
        throw(ExecutionError("Incorrect element name"));
    }
    elements_.erase(name);
}

template <typename ElementType>
void Factory<ElementType>::resetFactory() noexcept
{
    elements_.clear();
}

template <typename ElementType>
std::map<std::string, std::function<ElementType()>>&
Factory<ElementType>::getAll() noexcept
{
    return (elements_);
}

template class Factory<pizza::Pizza>;