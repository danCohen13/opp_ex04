#include "Exceptions.h"
#include "Logger.h"
#include <iostream>
#include <exception>

 #include "Game.h"

int main() {
    try {
           //This is my branch.
           Game game;
           game.run();
        

        return 0;
    }
    catch (const GameException& e) {
        std::cerr << "Error appear, please check log.txt for more details." << std::endl;
        Logger::logError(e.what());
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Error system happened." << std::endl;
        Logger::logError(std::string("Standard Exception: ") + e.what());
        return 1;
    }
    catch (...) {
        std::cerr << "An unknown error appeared." << std::endl;
        Logger::logError("Unknown critical exception caught in main.");
        return 1;
    }
}