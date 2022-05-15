/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Process hpp file
*/

#pragma once

#include <unistd.h>

class Process
{
  public:
    Process() noexcept;
    Process(const Process& other) noexcept = default;
    Process(Process&& other) noexcept = default;
    ~Process() noexcept;

    Process& operator=(const Process& rhs) noexcept = default;
    Process& operator=(Process&& rhs) noexcept = default;

    void wait() const noexcept;
    bool isChild() const noexcept;
    bool isRunning() const noexcept;
    void kill() const noexcept;

  private:
    pid_t pid_;
};