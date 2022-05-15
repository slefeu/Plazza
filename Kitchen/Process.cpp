/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Process
*/

#include "Process.hpp"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <memory>

namespace plazza
{
Process::Process() noexcept
{
    pid_ = ::fork();
}

Process::~Process() noexcept
{
    if (isRunning()) {
        ::kill(pid_, SIGKILL);
    }
}

void Process::wait() const noexcept
{
    if (!isChild()) {
        ::wait(nullptr);
    }
}

bool Process::isChild() const
{
    return pid_ == 0;
}

bool Process::isRunning() const
{
    int status = 0;
    int ret = ::waitpid(pid_, &status, WNOHANG);
    if (ret == -1) {
        return false;
    }
    return ret == 0;
}

void Process::kill() const
{
    if (!isChild()) {
        ::kill(pid_, SIGKILL);
    } else {
        ::exit(0);
    }
}

pid_t Process::getPid() const
{
    return isChild() ? ::getpid() : pid_;
}
}