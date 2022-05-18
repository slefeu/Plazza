/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Process hpp file
*/

#pragma once

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <memory>

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
    pid_t getPid() const;

  private:
    pid_t pid_;
};