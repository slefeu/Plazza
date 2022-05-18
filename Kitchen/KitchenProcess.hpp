/*
** EPITECH PROJECT, 2022
** Plazza
** File description: hpp file
** KitchenProcess
*/

#pragma once

#include <memory>

#include "NamedPipe.hpp"
#include "Process.hpp"

class KitchenProcess
{
  public:
    KitchenProcess() noexcept = delete;
    KitchenProcess(
        std::unique_ptr<Process>, std::unique_ptr<NamedPipe>) noexcept;
    KitchenProcess(const KitchenProcess& other) noexcept = delete;
    KitchenProcess(KitchenProcess&& other) noexcept = default;
    ~KitchenProcess() noexcept = default;

    KitchenProcess& operator=(const KitchenProcess& rhs) noexcept = delete;
    KitchenProcess& operator=(KitchenProcess&& rhs) noexcept = default;

    NamedPipe& getPipe() const noexcept;
    Process& getProcess() const noexcept;

  private:
    std::unique_ptr<Process> process_;
    std::unique_ptr<NamedPipe> pipe_;
};