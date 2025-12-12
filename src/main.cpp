#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/LevelSelector.hpp"
#include "../include/GameState.hpp"
#include "../include/ViewUtils.hpp"

int main() {
    std::cout << "=== Iniciando Fuego y Agua ===" << std::endl;
    
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fuego y Agua");
    window.setFramerateLimit(60);
    
    // Vista fija de 1200x800 con letterboxing
    sf::View gameView(sf::FloatRect(0, 0, 1200, 800));
    gameView = getLetterboxView(gameView, 1200, 800);
    window.setView(gameView);

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
            
            // Manejar redimensión de ventana (maximizar, restaurar, arrastrar bordes)
            if (event.type == sf::Event::Resized) {
                gameView = sf::View(sf::FloatRect(0, 0, 1200, 800));
                gameView = getLetterboxView(gameView, event.size.width, event.size.height);
                window.setView(gameView);
                std::cout << "Ventana redimensionada: " << event.size.width << "x" << event.size.height << std::endl;
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
                
                // Reconfigurar la vista para la nueva ventana
                gameView = sf::View(sf::FloatRect(0, 0, 1200, 800));
                gameView = getLetterboxView(gameView, window.getSize().x, window.getSize().y);
                window.setView(gameView);
                
                std::cout << "Modo: " << (isFullscreen ? "Pantalla completa" : "Ventana") << std::endl;
            }

            // Manejar clicks con coordenadas transformadas
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                
                if (currentState == GameState::MENU_PRINCIPAL) {
                    menu.handleClick(worldPos);
                } else if (currentState == GameState::SELECTOR_NIVEL) {
                    levelSelector.handleClick(worldPos);
                }
            }
        }

        // UPDATE
        if (currentState == GameState::MENU_PRINCIPAL) {
            menu.update(getMousePositionInView(window));
            
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
            levelSelector.update(getMousePositionInView(window));
            
            selectedLevel = levelSelector.getSelectedLevel();
            if (selectedLevel == -2) {
                std::cout << ">>> Volviendo al menú principal <<<" << std::endl;
                currentState = GameState::MENU_PRINCIPAL;
                levelSelector.resetSelection();
            } else if (selectedLevel > 0) {
                std::cout << ">>> Iniciando nivel " << selectedLevel << " <<<" << std::endl;
                window.close();
                
                game = new Game(selectedLevel, isFullscreen);
                game->run();
                
                delete game;
                game = nullptr;
                
                if (isFullscreen) {
                    window.create(sf::VideoMode::getDesktopMode(), "Fuego y Agua", sf::Style::Fullscreen);
                } else {
                    window.create(sf::VideoMode(1200, 800), "Fuego y Agua");
                }
                window.setFramerateLimit(60);
                
                // Reconfigurar la vista después de volver del juego
                gameView = sf::View(sf::FloatRect(0, 0, 1200, 800));
                gameView = getLetterboxView(gameView, window.getSize().x, window.getSize().y);
                window.setView(gameView);
                
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
