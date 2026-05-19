#pragma once

#include <stdexcept>
#include <string>

// Exception de base pour notre projet
class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message)
        : std::runtime_error(message) {}
};

// Levée si le fichier de niveau est introuvable
class FileNotFoundException : public GameException {
public:
    explicit FileNotFoundException(const std::string& filepath)
        : GameException("Erreur : Le fichier de niveau suivant est introuvable : " + filepath) {
    }
};

// Levée si le format ou le contenu du fichier est corrompu
class CorruptedLevelException : public GameException {
public:
    explicit CorruptedLevelException(const std::string& details)
        : GameException("Erreur de syntaxe / Niveau corrompu : " + details) {
    }
};