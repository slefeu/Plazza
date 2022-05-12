/*
** EPITECH PROJECT, 2022
** Plazza
** File description: hpp file
** Process
*/

#pragma once

#include <unistd.h>

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

  private:
    pid_t pid_;
};
