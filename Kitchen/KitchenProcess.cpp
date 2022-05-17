/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** KitchenProcess
*/

#include "KitchenProcess.hpp"

#include <utility>

#include "NamedPipe.hpp"
#include "Process.hpp"

KitchenProcess::KitchenProcess(
    std::unique_ptr<Process> process, std::unique_ptr<NamedPipe> pipe) noexcept
    : process_(std::move(process))
    , pipe_(std::move(pipe))
{
}

NamedPipe& KitchenProcess::getPipe()
{
    return (*pipe_);
}

Process& KitchenProcess::getProcess()
{
    return (*process_);
}