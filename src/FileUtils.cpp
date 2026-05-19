#include "FileUtils.h"
#include <fstream>

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