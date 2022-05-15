/*
** EPITECH PROJECT, 2022
** B-CCP-400-BDX-4-1-theplazza-solene.lefeu
** File description:
** Errors
*/

#pragma once

#include <exception>
#include <string>

class Error : public std::exception
{
  public:
    explicit Error(std::string) noexcept;
    Error(const Error& other) noexcept = default;
    Error(Error&& other) noexcept = default;
    ~Error() noexcept override = default;

    Error& operator=(const Error&) noexcept = default;
    Error& operator=(Error&&) noexcept = default;
    const char* what() const noexcept override;

  protected:
  private:
    std::string message_;
};

class ArgumentError : public Error
{
  public:
    explicit ArgumentError(std::string) noexcept;
    ArgumentError(const ArgumentError& other) noexcept = default;
    ArgumentError(ArgumentError&& other) noexcept = default;
    ~ArgumentError() noexcept override = default;

    ArgumentError& operator=(const ArgumentError& rhs) noexcept = default;
    ArgumentError& operator=(ArgumentError&& rhs) noexcept = default;

  protected:
  private:
};

class ExecutionError : public Error
{
  public:
    explicit ExecutionError(std::string) noexcept;
    ExecutionError(const ExecutionError& other) noexcept = default;
    ExecutionError(ExecutionError&& other) noexcept = default;
    ~ExecutionError() noexcept override = default;

    ExecutionError& operator=(const ExecutionError& rhs) noexcept = default;
    ExecutionError& operator=(ExecutionError&& rhs) noexcept = default;

  protected:
  private:
};

class CommunicationError : public Error
{
  public:
    explicit CommunicationError(std::string) noexcept;
    CommunicationError(const CommunicationError& other) noexcept = default;
    CommunicationError(CommunicationError&& other) noexcept = default;
    ~CommunicationError() noexcept override = default;

    CommunicationError& operator=(
        const CommunicationError& rhs) noexcept = default;
    CommunicationError& operator=(CommunicationError&& rhs) noexcept = default;

  protected:
  private:
};