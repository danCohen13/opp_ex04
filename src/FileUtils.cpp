#include "FileUtils.h"
#include "Direction.h"
#include <fstream>
#include <map>

bool FileUtils::fileExists(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);

    return file.good();
}

bool FileUtils::hasExtension(const std::string& filepath, const std::string& extension) {
    if (filepath.length() >= extension.length()) {
        return (0 == filepath.compare(filepath.length() - extension.length(), extension.length(), extension));
    }
    return false;
}

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