#include "FileUtils.h"
#include "Direction.h"
#include <fstream>
#include <map>

bool FileUtils::fileExists(const std::string& filepath) {
    // Tentative d'ouverture du fichier en mode binaire pour ne pas altérer le curseur
    std::ifstream file(filepath, std::ios::binary);

    // La conversion implicite du flux en booléen appelle la fonction membre !fail()
    return file.good();
}

bool FileUtils::hasExtension(const std::string& filepath, const std::string& extension) {
    if (filepath.length() >= extension.length()) {
        // Recherche de la sous-chaîne à la fin du chemin fourni
        return (0 == filepath.compare(filepath.length() - extension.length(), extension.length(), extension));
    }
    return false;
}

// AJOUT OBLIGATOIRE : Traduction des nouvelles directions SFML 3 en texte pour le Logger
const std::string& FileUtils::directionToString(Direction dir) {
    static const std::map<Direction, std::string> labels = {
        {Direction::NorthEast, "North-East"},
        {Direction::East,      "East"},
        {Direction::SouthEast, "South-East"},
        {Direction::SouthWest, "South-West"},
        {Direction::West,      "West"},
        {Direction::NorthWest, "North-West"}
    };
    return labels.at(dir);
}