/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Process
*/

#include "Process.hpp"

#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
#include <memory>

Process::Process() noexcept
    : pid_(::fork())
{
}

Process::~Process() noexcept
{
    if (isRunning())
        ::kill(pid_, SIGKILL);
}

void Process::wait() const noexcept
{
    if (!isChild()) {
        ::wait(nullptr);
    }
}

bool Process::isChild() const noexcept
{
    return (pid_ == 0);
}

bool Process::isRunning() const noexcept
{
    int status = 0;
    int ret = ::waitpid(pid_, &status, WNOHANG);

    if (ret == -1)
        return (false);
    return (ret == 0);
}

void Process::kill() const noexcept
{
    if (!isChild())
        ::kill(pid_, SIGKILL);
    else
        ::exit(0);
}
pid_t Process::getPid() const
{
    return isChild() ? ::getpid() : pid_;
}
}