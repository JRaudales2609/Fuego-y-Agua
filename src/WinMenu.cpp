#include "../include/WinMenu.hpp"
#include <iostream>

WinMenu::WinMenu() : selectedOption(-1), winner(0) {
    // Cargar fuente
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Error: No se pudo cargar ninguna fuente" << std::endl;
        }
    }
    
    // Overlay oscuro semi-transparente
    overlay.setSize(sf::Vector2f(1200, 800));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    
    // Cargar imágenes de victoria
    if (player1WinTexture.loadFromFile("assets/imagenes/ui/player1_win.png")) {
        std::cout << "✓ Imagen de Player 1 Win cargada" << std::endl;
    } else {
        std::cerr << "Advertencia: No se pudo cargar player1_win.png" << std::endl;
    }
    
    if (player2WinTexture.loadFromFile("assets/imagenes/ui/player2_win.png")) {
        std::cout << "✓ Imagen de Player 2 Win cargada" << std::endl;
    } else {
        std::cerr << "Advertencia: No se pudo cargar player2_win.png" << std::endl;
    }
    
    // Cargar texturas de botones
    if (restartButtonTexture.loadFromFile("assets/imagenes/ui/restart_button.png")) {
        std::cout << "✓ Textura del botón reiniciar cargada (WinMenu)" << std::endl;
        restartButtonSprite.setTexture(restartButtonTexture);
    }
    
    if (exitButtonTexture.loadFromFile("assets/imagenes/ui/exit_button.png")) {
        std::cout << "✓ Textura del botón de salir cargada (WinMenu)" << std::endl;
        exitButtonSprite.setTexture(exitButtonTexture);
    }
    
    // Crear solo 2 botones: REINICIAR y SALIR
    std::vector<std::string> buttonLabels = {"REINICIAR", "SALIR"};
    float buttonWidth = 300;
    float buttonHeight = 70;
    
    for (size_t i = 0; i < buttonLabels.size(); i++) {
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setFillColor(sf::Color(50, 50, 50, 220));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(3);
        buttons.push_back(button);
        
        sf::Text text;
        text.setFont(font);
        text.setString(buttonLabels[i]);
        text.setCharacterSize(35);
        text.setFillColor(sf::Color::White);
        buttonTexts.push_back(text);
    }
    
    // Configurar texto del tiempo
    timeText.setFont(font);
    timeText.setCharacterSize(50);
    timeText.setFillColor(sf::Color::White);
    timeText.setOutlineColor(sf::Color::Black);
    timeText.setOutlineThickness(2);
    
    std::cout << "WinMenu inicializado correctamente" << std::endl;
}

void WinMenu::setWinner(int playerNumber, const std::string& timeStr) {
    winner = playerNumber;
    
    // Establecer la textura correcta según el ganador
    if (winner == 1 && player1WinTexture.getSize().x > 0) {
        winTitleSprite.setTexture(player1WinTexture);
    } else if (winner == 2 && player2WinTexture.getSize().x > 0) {
        winTitleSprite.setTexture(player2WinTexture);
    }
    
    // Establecer el tiempo
    timeText.setString("Tiempo: " + timeStr);
    
    std::cout << "Ganador: Player " << winner << " - Tiempo: " << timeStr << std::endl;
}

void WinMenu::handleClick(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].getGlobalBounds().contains(mousePos)) {
            selectedOption = static_cast<int>(i);
            std::cout << "Opción de victoria seleccionada: " << i << std::endl;
            return;
        }
    }
}

void WinMenu::update(const sf::Vector2i& mousePos) {
    float spriteWidth = 200.0f;
    float hoverWidth = 220.0f;
    
    for (size_t i = 0; i < buttons.size(); i++) {
        bool hover = buttons[i].getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y));
        
        // Efecto hover en sprites
        if (hover) {
            if (i == 0 && restartButtonTexture.getSize().x > 0) {
                restartButtonSprite.setScale(hoverWidth / restartButtonTexture.getSize().x, 
                                           hoverWidth / restartButtonTexture.getSize().x);
            } else if (i == 1 && exitButtonTexture.getSize().x > 0) {
                exitButtonSprite.setScale(hoverWidth / exitButtonTexture.getSize().x, 
                                        hoverWidth / exitButtonTexture.getSize().x);
            }
            
            buttons[i].setFillColor(sf::Color(100, 100, 100, 220));
            buttons[i].setOutlineColor(sf::Color(255, 140, 0));
            buttons[i].setOutlineThickness(5);
            buttonTexts[i].setFillColor(sf::Color(255, 140, 0));
        } else {
            if (i == 0 && restartButtonTexture.getSize().x > 0) {
                restartButtonSprite.setScale(spriteWidth / restartButtonTexture.getSize().x, 
                                           spriteWidth / restartButtonTexture.getSize().x);
            } else if (i == 1 && exitButtonTexture.getSize().x > 0) {
                exitButtonSprite.setScale(spriteWidth / exitButtonTexture.getSize().x, 
                                        spriteWidth / exitButtonTexture.getSize().x);
            }
            
            buttons[i].setFillColor(sf::Color(50, 50, 50, 220));
            buttonTexts[i].setFillColor(sf::Color::White);
        }
    }
}

void WinMenu::updatePositions(const sf::Vector2u& windowSize) {
    const float gameWidth = 1200.0f;
    const float gameHeight = 800.0f;
    float centerX = gameWidth / 2.0f;
    float buttonWidth = 300;
    float buttonHeight = 70;
    float startY = gameHeight * 0.55f; // Más abajo para dejar espacio al tiempo
    float spacing = 100;
    
    overlay.setSize(sf::Vector2f(gameWidth, gameHeight));
    
    // Actualizar imagen del ganador
    if (winTitleSprite.getTexture()) {
        float scale = 400.0f / winTitleSprite.getTexture()->getSize().x;
        winTitleSprite.setScale(scale, scale);
        
        sf::FloatRect winBounds = winTitleSprite.getGlobalBounds();
        winTitleSprite.setOrigin(winBounds.width / (2 * scale), winBounds.height / (2 * scale));
        winTitleSprite.setPosition(centerX, gameHeight * 0.20f);
    }
    
    // Actualizar texto del tiempo
    sf::FloatRect timeBounds = timeText.getLocalBounds();
    timeText.setOrigin(timeBounds.width / 2, timeBounds.height / 2);
    timeText.setPosition(centerX, gameHeight * 0.40f);
    
    // Actualizar botones
    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i].setPosition(centerX - buttonWidth / 2, startY + i * spacing);
        
        sf::FloatRect textBounds = buttonTexts[i].getLocalBounds();
        buttonTexts[i].setOrigin(textBounds.width / 2, textBounds.height / 2);
        buttonTexts[i].setPosition(centerX, startY + i * spacing + buttonHeight / 2);
    }
    
    // Actualizar sprites de botones
    float spriteWidth = 200.0f;
    
    if (restartButtonTexture.getSize().x > 0) {
        float scale = spriteWidth / restartButtonTexture.getSize().x;
        restartButtonSprite.setScale(scale, scale);
        sf::FloatRect bounds = restartButtonSprite.getGlobalBounds();
        restartButtonSprite.setPosition(centerX - bounds.width / 2, startY + 15);
    }
    
    if (exitButtonTexture.getSize().x > 0) {
        float scale = spriteWidth / exitButtonTexture.getSize().x;
        exitButtonSprite.setScale(scale, scale);
        sf::FloatRect bounds = exitButtonSprite.getGlobalBounds();
        exitButtonSprite.setPosition(centerX - bounds.width / 2, startY + spacing + 15);
    }
}

void WinMenu::render(sf::RenderWindow& window) {
    window.draw(overlay);
    
    // Dibujar imagen del ganador
    if (winTitleSprite.getTexture()) {
        window.draw(winTitleSprite);
    }
    
    // Dibujar tiempo
    window.draw(timeText);
    
    // Dibujar botones
    for (size_t i = 0; i < buttons.size(); i++) {
        if (i == 0 && restartButtonTexture.getSize().x > 0) {
            window.draw(restartButtonSprite);
        } else if (i == 1 && exitButtonTexture.getSize().x > 0) {
            window.draw(exitButtonSprite);
        } else {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
    }
}

int WinMenu::getSelectedOption() const {
    return selectedOption;
}

void WinMenu::resetSelection() {
    selectedOption = -1;
}
