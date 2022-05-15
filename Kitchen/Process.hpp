/*
** EPITECH PROJECT, 2022
** Plazza
** File description: hpp file
** Process
*/

#pragma once

#include <unistd.h>

namespace plazza
{
class Process
{
  public:
    Process() noexcept;
    Process(Process const& other) noexcept = default;
    Process(Process&& other) noexcept = default;
    Process& operator=(Process const& other) noexcept = default;
    Process& operator=(Process&& other) noexcept = default;
    ~Process() noexcept;
    void wait() const noexcept;
    bool isChild() const;
    bool isRunning() const;
    void kill() const;
    pid_t getPid() const;

  private:
    pid_t pid_;
};
}