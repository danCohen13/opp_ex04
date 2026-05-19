#include "Exceptions.h"
#include "Logger.h"
#include <iostream>
#include <exception>

// Plus tard, nous inclurons l'orchestrateur :
 #include "Game.h"

int main() {
    try {
        std::cout << "Initialisation du moteur de jeu 'Lights'..." << std::endl;

        
           
           Game game;
           game.run();
        

        std::cout << "Fermeture normale de l'application." << std::endl;
        return 0;
    }
    catch (const GameException& e) {
        // Capture de nos exceptions personnalisées (Fichier corrompu ou introuvable)
        std::cerr << "Une erreur de jeu est survenue. Consultez log.txt pour plus de details." << std::endl;
        Logger::logError(e.what());
        return 1;
    }
    catch (const std::exception& e) {
        // Capture des exceptions standards de la STL (ex: std::bad_alloc)
        std::cerr << "Une erreur systeme imprevue est survenue." << std::endl;
        Logger::logError(std::string("Standard Exception: ") + e.what());
        return 1;
    }
    catch (...) {
        // Sécurité absolue contre les lancers de types primitifs inconnus
        std::cerr << "Une erreur inconnue et critique est survenue." << std::endl;
        Logger::logError("Unknown critical exception caught in main.");
        return 1;
    }
}