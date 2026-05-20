#pragma once

#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message)
        : std::runtime_error(message) {}
};

class FileNotFoundException : public GameException {
public:
    explicit FileNotFoundException(const std::string& filepath)
        : GameException("Error : this file doesnt exist : " + filepath) {
    }
};

class CorruptedLevelException : public GameException {
public:
    explicit CorruptedLevelException(const std::string& details)
        : GameException("Synthax error : " + details) {
    }
};