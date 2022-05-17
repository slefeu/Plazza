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
    KitchenProcess(
        std::unique_ptr<Process>, std::unique_ptr<NamedPipe>) noexcept;
    KitchenProcess(KitchenProcess const& other) noexcept = delete;
    KitchenProcess(KitchenProcess&& other) noexcept = default;
    KitchenProcess& operator=(KitchenProcess const& other) noexcept = delete;
    KitchenProcess& operator=(KitchenProcess&& other) noexcept = default;
    ~KitchenProcess() noexcept = default;
    NamedPipe& getPipe();
    Process& getProcess();

  private:
    std::unique_ptr<Process> process_;
    std::unique_ptr<NamedPipe> pipe_;
};