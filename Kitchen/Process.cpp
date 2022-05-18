/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Process
*/

#include "Process.hpp"
#include <unistd.h>

/**
 * \brief Constructor of Process class
 *
 * \return Process
 */
Process::Process() noexcept
    : pid_(::fork())
{
}

/**
 * \brief Destructor of Process class
 *
 * \return Process
 */
Process::~Process() noexcept
{
    if (isRunning())
        ::kill(pid_, SIGKILL);
}

/**
 * \brief Wait for the process to finish
 *
 * \return void
 */
void Process::wait() const noexcept
{
    if (!isChild()) {
        ::wait(nullptr);
    }
}

/**
 * \brief Check if the process is a child
 *
 * \return bool
 */
bool Process::isChild() const noexcept
{
    return (pid_ == 0);
}

/**
 * \brief Check if the process is running
 *
 * \return bool
 */
bool Process::isRunning() const noexcept
{
    int status = 0;
    int ret = ::waitpid(pid_, &status, WNOHANG);

    if (ret == -1)
        return (false);
    return (ret == 0);
}

/**
 * \brief Kill the process
 *
 * \return void
 */
void Process::kill() const noexcept
{
    if (!isChild())
        ::kill(pid_, SIGKILL);
    else
        ::exit(0);
}

/**
 * \brief Get the pid of the process
 *
 * \return pid_t
 */
pid_t Process::getPid() const
{
    return (isChild() ? ::getpid() : pid_);
}

/**
 * \brief Get the pid of the current process
 *
 * \return pid_t
 */
pid_t Process::getCurrentPid() noexcept
{
    return (::getpid());
}