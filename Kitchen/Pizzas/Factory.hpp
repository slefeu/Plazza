/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Factory
*/

#pragma once
#include <functional>
#include <map>
#include <memory>

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

    void addElement(std::string, std::function<ElementType()>) noexcept;
    ElementType getElement(std::string&);
    void removeElement(std::string&);
    std::map<std::string, std::function<ElementType()>>& getAll() noexcept;
    void resetFactory() noexcept;

  protected:
  private:
    std::map<std::string, std::function<ElementType()>> elements_;
};

template class Factory<pizza::Pizza>;