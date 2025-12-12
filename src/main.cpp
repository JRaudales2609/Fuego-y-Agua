#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/LevelSelector.hpp"
#include "../include/GameState.hpp"

int main() {
    std::cout << "=== Iniciando Fuego y Agua ===" << std::endl;
    
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fuego y Agua");
    window.setFramerateLimit(60);

    // Estado del juego
    GameState currentState = GameState::MENU_PRINCIPAL;
    Menu menu;
    LevelSelector levelSelector;
    Game* game = nullptr;
    int selectedLevel = 1;
    
    bool isFullscreen = false;

    // Game loop
    while (window.isOpen()) {
        // ACTUALIZAR POSICIONES ANTES DE EVENTOS
        if (currentState == GameState::MENU_PRINCIPAL) {
            menu.updatePositions(window.getSize());
        } else if (currentState == GameState::SELECTOR_NIVEL) {
            levelSelector.updatePositions(window.getSize());
        }
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // F11 para alternar pantalla completa
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {
                isFullscreen = !isFullscreen;
                window.close();
                if (isFullscreen) {
                    window.create(sf::VideoMode::getDesktopMode(), "Fuego y Agua", sf::Style::Fullscreen);
                } else {
                    window.create(sf::VideoMode(1200, 800), "Fuego y Agua");
                }
                window.setFramerateLimit(60);
                std::cout << "Modo: " << (isFullscreen ? "Pantalla completa" : "Ventana") << std::endl;
            }

            if (currentState == GameState::MENU_PRINCIPAL) {
                menu.handleInput(event);
            } else if (currentState == GameState::SELECTOR_NIVEL) {
                levelSelector.handleInput(event);
            }
        }

        // UPDATE
        if (currentState == GameState::MENU_PRINCIPAL) {
            menu.update(sf::Mouse::getPosition(window));
            
            int selectedOption = menu.getSelectedOption();
            if (selectedOption == 0) {
                std::cout << ">>> COMENZAR presionado <<<" << std::endl;
                currentState = GameState::SELECTOR_NIVEL;
                menu.resetSelection();
            } else if (selectedOption == 1) {
                std::cout << ">>> SALIR presionado <<<" << std::endl;
                window.close();
            }
        } 
        else if (currentState == GameState::SELECTOR_NIVEL) {
            levelSelector.update(sf::Mouse::getPosition(window));
            
            selectedLevel = levelSelector.getSelectedLevel();
            if (selectedLevel == -2) {
                std::cout << ">>> Volviendo al menú principal <<<" << std::endl;
                currentState = GameState::MENU_PRINCIPAL;
                levelSelector.resetSelection();
            } else if (selectedLevel > 0) {
                std::cout << ">>> Iniciando nivel " << selectedLevel << " <<<" << std::endl;
                window.close();
                
                game = new Game(selectedLevel);
                game->run();
                
                delete game;
                game = nullptr;
                
                if (isFullscreen) {
                    window.create(sf::VideoMode::getDesktopMode(), "Fuego y Agua", sf::Style::Fullscreen);
                } else {
                    window.create(sf::VideoMode(1200, 800), "Fuego y Agua");
                }
                window.setFramerateLimit(60);
                currentState = GameState::MENU_PRINCIPAL;
                levelSelector.resetSelection();
            }
        }

        // RENDER
        if (window.isOpen()) {
            window.clear(sf::Color::Black);
            
            if (currentState == GameState::MENU_PRINCIPAL) {
                menu.render(window);
            } else if (currentState == GameState::SELECTOR_NIVEL) {
                levelSelector.render(window);
            }
            
            window.display();
        }
    }

    if (game != nullptr) {
        delete game;
    }

    std::cout << "Juego cerrado correctamente" << std::endl;
    return 0;
}
