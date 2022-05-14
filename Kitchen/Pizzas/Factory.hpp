/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Factory
*/

#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <memory>

#include "Errors.hpp"
#include "Pizza.hpp"

template <typename ElementType>
class Factory
{
  public:
    Factory() noexcept = default;
    Factory(const Factory& other) noexcept = delete;
    Factory(Factory&& other) noexcept = delete;
    ~Factory() noexcept = default;

    Factory& operator=(const Factory& rhs) noexcept = delete;
    Factory& operator=(Factory&& rhs) noexcept = delete;

    void addElement(
        std::string name, std::function<ElementType()> element) noexcept
    {
        if (elements_.find(name) == elements_.end()) {
            elements_.emplace(name, element);
        }
    }
    ElementType getElement(std::string& name)
    {
        if (elements_.find(name) != elements_.end()) {
            return elements_[name]();
        }
        throw(ExecutionError("Incorrect element name"));
    }
    void removeElement(std::string& name)
    {
        if (elements_.find(name) == elements_.end()) {
            throw(ExecutionError("Incorrect element name"));
        }
        elements_.erase(name);
    }
    void resetFactory() noexcept
    {
        elements_.clear();
    }
    std::map<std::string, std::function<ElementType()>>&
    getAll() noexcept
    {
        return (elements_);
    }

  protected:
  private:
    std::map<std::string, std::function<ElementType()>> elements_;
};

template class Factory<pizza::Pizza>;