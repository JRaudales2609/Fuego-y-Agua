#include "../include/Menu.hpp"
#include <iostream>

Menu::Menu() : selectedButton(-1) {
    std::cout << "=== Inicializando Menu ===" << std::endl;
    
    // Cargar fuente
    bool fontLoaded = false;
    
    if (font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        std::cout << "✓ Fuente cargada: assets/fonts/ThaleahFat.ttf" << std::endl;
        fontLoaded = true;
    }
    else if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "✓ Fuente cargada: C:/Windows/Fonts/arial.ttf" << std::endl;
        fontLoaded = true;
    }
    else {
        std::cerr << "✗ ERROR CRÍTICO: No se pudo cargar ninguna fuente" << std::endl;
    }
    
    // Cargar fondo del menú principal
    if (backgroundTexture.loadFromFile("assets/imagenes/ui/menu_background.png")) {
        std::cout << "✓ Fondo del menú cargado" << std::endl;
        backgroundSprite.setTexture(backgroundTexture);
    } else {
        std::cerr << "Advertencia: No se pudo cargar menu_background.png, usando fondo del nivel" << std::endl;
        // Fallback al fondo del nivel
        if (backgroundTexture.loadFromFile("assets/imagenes/niveles/background.png")) {
            backgroundSprite.setTexture(backgroundTexture);
        }
    }
    
    // Cargar textura del botón de inicio
    if (startButtonTexture.loadFromFile("assets/imagenes/ui/start_button.png")) {
        std::cout << "✓ Textura del botón de inicio cargada" << std::endl;
        startButtonSprite.setTexture(startButtonTexture);
    } else {
        std::cerr << "Advertencia: No se pudo cargar start_button.png" << std::endl;
    }
    
    // Cargar textura del botón de salir
    if (exitButtonTexture.loadFromFile("assets/imagenes/ui/exit_button.png")) {
        std::cout << "✓ Textura del botón de salir cargada" << std::endl;
        exitButtonSprite.setTexture(exitButtonTexture);
    } else {
        std::cerr << "Advertencia: No se pudo cargar exit_button.png" << std::endl;
    }
    
    if (fontLoaded) {
        // Título del juego - COMENTADO para no mostrarlo
        title.setFont(font);
        title.setString("FUEGO Y AGUA");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::White);
        title.setOutlineColor(sf::Color(255, 140, 0));
        title.setOutlineThickness(4);
        
        // Solo crear el botón de SALIR (rectángulo para fallback)
        sf::RectangleShape exitButton(sf::Vector2f(200, 60));
        exitButton.setFillColor(sf::Color(80, 80, 80, 200));
        exitButton.setOutlineColor(sf::Color::White);
        exitButton.setOutlineThickness(3);
        buttons.push_back(exitButton);
        
        sf::Text exitText;
        exitText.setFont(font);
        exitText.setString("< SALIR");
        exitText.setCharacterSize(30);
        exitText.setFillColor(sf::Color::White);
        buttonTexts.push_back(exitText);
        
        std::cout << "✓ Menu inicializado correctamente" << std::endl;
    }
}

void Menu::updatePositions(const sf::Vector2u& windowSize) {
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;
    
    // Actualizar fondo
    if (backgroundTexture.getSize().x > 0) {
        sf::Vector2u texSize = backgroundTexture.getSize();
        float scaleX = static_cast<float>(windowSize.x) / texSize.x;
        float scaleY = static_cast<float>(windowSize.y) / texSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
        backgroundSprite.setPosition(0, 0);
    }
    
    // NO actualizar título (no se dibujará)
    
    // Actualizar sprite del botón de inicio circular (centro, más grande)
    if (startButtonTexture.getSize().x > 0) {
        float scale = 250.0f / startButtonTexture.getSize().x;
        startButtonSprite.setScale(scale, scale);
        
        sf::FloatRect spriteBounds = startButtonSprite.getGlobalBounds();
        startButtonSprite.setPosition(
            centerX - spriteBounds.width / 2,
            centerY - spriteBounds.height / 2
        );
    }
    
    // Actualizar sprite del botón de salir - MÁS GRANDE
    if (exitButtonTexture.getSize().x > 0) {
        float scale = 120.0f / exitButtonTexture.getSize().x; // Aumentado de 80 a 120
        exitButtonSprite.setScale(scale, scale);
        exitButtonSprite.setPosition(50, windowSize.y - 130); // Ajustar posición
    }
    
    // Actualizar botón SALIR (esquina inferior izquierda)
    buttons[0].setPosition(50, windowSize.y - 130); // Ajustar posición
    
    sf::FloatRect exitTextBounds = buttonTexts[0].getLocalBounds();
    buttonTexts[0].setOrigin(exitTextBounds.width / 2, exitTextBounds.height / 2);
    buttonTexts[0].setPosition(170, windowSize.y - 65); // Ajustar posición
}

void Menu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Verificar click en botón de inicio (sprite circular)
            if (startButtonTexture.getSize().x > 0) {
                if (startButtonSprite.getGlobalBounds().contains(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y))) {
                    selectedButton = 0; // COMENZAR
                    std::cout << "Botón de inicio clickeado" << std::endl;
                    return;
                }
            }
            
            // Verificar click en botón SALIR (sprite o rectángulo)
            if (exitButtonTexture.getSize().x > 0) {
                if (exitButtonSprite.getGlobalBounds().contains(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y))) {
                    selectedButton = 1; // SALIR
                    std::cout << "Botón SALIR clickeado" << std::endl;
                    return;
                }
            } else if (buttons[0].getGlobalBounds().contains(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y))) {
                selectedButton = 1; // SALIR
                std::cout << "Botón SALIR clickeado" << std::endl;
                return;
            }
        }
    }
}

void Menu::update(const sf::Vector2i& mousePos) {
    // Hover en botón de inicio (sprite circular)
    if (startButtonTexture.getSize().x > 0) {
        if (startButtonSprite.getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y))) {
            float scale = 270.0f / startButtonTexture.getSize().x;
            startButtonSprite.setScale(scale, scale);
        } else {
            float scale = 250.0f / startButtonTexture.getSize().x;
            startButtonSprite.setScale(scale, scale);
        }
    }
    
    // Hover en botón SALIR - Ajustado para tamaño más grande
    bool hoverExit = false;
    if (exitButtonTexture.getSize().x > 0) {
        hoverExit = exitButtonSprite.getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y));
        
        if (hoverExit) {
            float scale = 135.0f / exitButtonTexture.getSize().x; // Aumentado
            exitButtonSprite.setScale(scale, scale);
        } else {
            float scale = 120.0f / exitButtonTexture.getSize().x; // Aumentado
            exitButtonSprite.setScale(scale, scale);
        }
    } else {
        hoverExit = buttons[0].getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y));
    }
    
    if (hoverExit) {
        buttons[0].setFillColor(sf::Color(100, 100, 100, 220));
        buttons[0].setOutlineColor(sf::Color(255, 140, 0));
        buttons[0].setOutlineThickness(5);
        buttonTexts[0].setFillColor(sf::Color(255, 140, 0));
    } else {
        buttons[0].setFillColor(sf::Color(80, 80, 80, 200));
        buttons[0].setOutlineColor(sf::Color::White);
        buttons[0].setOutlineThickness(3);
        buttonTexts[0].setFillColor(sf::Color::White);
    }
}

void Menu::render(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    
    // Dibujar fondo
    window.draw(backgroundSprite);
    
    // Overlay completamente transparente para ver el brillo original
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 0)); // Transparencia en 0 - sin oscurecer
    window.draw(overlay);
    
    // NO dibujar título
    
    // Dibujar botón de inicio circular
    if (startButtonTexture.getSize().x > 0) {
        window.draw(startButtonSprite);
    } else {
        // Fallback
        sf::RectangleShape fallbackButton(sf::Vector2f(300, 80));
        fallbackButton.setPosition(windowSize.x / 2 - 150, windowSize.y / 2 - 40);
        fallbackButton.setFillColor(sf::Color(50, 50, 50, 200));
        fallbackButton.setOutlineColor(sf::Color::White);
        fallbackButton.setOutlineThickness(3);
        window.draw(fallbackButton);
        
        sf::Text fallbackText;
        fallbackText.setFont(font);
        fallbackText.setString("COMENZAR");
        fallbackText.setCharacterSize(40);
        fallbackText.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = fallbackText.getLocalBounds();
        fallbackText.setOrigin(textBounds.width / 2, textBounds.height / 2);
        fallbackText.setPosition(windowSize.x / 2, windowSize.y / 2);
        window.draw(fallbackText);
    }
    
    // Dibujar botón SALIR
    if (exitButtonTexture.getSize().x > 0) {
        window.draw(exitButtonSprite);
    } else {
        window.draw(buttons[0]);
        window.draw(buttonTexts[0]);
    }
}

int Menu::getSelectedOption() const {
    return selectedButton;
}

void Menu::resetSelection() {
    selectedButton = -1;
}
