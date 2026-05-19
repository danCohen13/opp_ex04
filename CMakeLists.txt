cmake_minimum_required (VERSION 3.26)

project (oop2_ex04)
set (MY_AUTHORS "chaim-Gur-Arie_Dan-Cohen")

include (cmake/CompilerSettings.cmake)

# CORRECTION : On alimente l'exécutable avec l'intégralité de nos fichiers sources .cpp
add_executable (${CMAKE_PROJECT_NAME}
    src/main.cpp 
    src/Board.cpp 
    src/Level.cpp 
    src/LevelLoader.cpp 
    src/ConnectionValidator.cpp 
    src/LightPropagationSystem.cpp 
    src/Logger.cpp 
    src/BulbRenderer.cpp 
    src/BoardRenderer.cpp 
    src/RenderSystem.cpp 
    src/GameController.cpp 
    src/Game.cpp
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
if (NOT MSVC)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endif()

# CORRECTION : Ajout du répertoire d'inclusion général pour trouver nos fichiers d'en-tête (.h)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)

# On conserve tes inclusions universitaires
add_subdirectory (include)
add_subdirectory (src)

include (cmake/Zip.cmake)

# Ta configuration explicite de localisation pour SFML 3.0.0
set (SFML_LOCATION "C:/SFML/SFML-3.0.0")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

# Chargement moderne de SFML 3.0 via les composants Graphics et Main (requis pour Windows/MSVC)
find_package (SFML 3.0 COMPONENTS Graphics Main REQUIRED)

# Liaison des cibles importées modernes (SFML::) à ton projet
target_link_libraries (${CMAKE_PROJECT_NAME} PRIVATE SFML::Graphics SFML::Main)

# CORRECTION : Retrait de "add_subdirectory (resources)" et "include (cmake/SFML.cmake)" qui n'existent pas.