#include "../include/LevelSelector.hpp"
#include <iostream>

LevelSelector::LevelSelector() : selectedLevel(-1) {
    // Cargar fuente
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Error: No se pudo cargar ninguna fuente" << std::endl;
        }
    }
    
    // Cargar fondo
    if (backgroundTexture.loadFromFile("assets/imagenes/niveles/background.png")) {
        backgroundSprite.setTexture(backgroundTexture);
    }
    
    // Título
    title.setFont(font);
    title.setString("SELECCIONA UN NIVEL");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color(255, 140, 0));
    title.setOutlineThickness(3);
    
    // Cargar textura del botón de salir
    if (exitButtonTexture.loadFromFile("assets/imagenes/ui/exit_button.png")) {
        std::cout << "✓ Textura del botón de salir cargada" << std::endl;
        exitButtonSprite.setTexture(exitButtonTexture);
    }
    
    // Crear botones de niveles (se posicionarán en render)
    for (int i = 0; i < 2; i++) {
        sf::RectangleShape button(sf::Vector2f(350, 400));
        button.setFillColor(sf::Color(50, 50, 50, 200));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(3);
        levelButtons.push_back(button);
        
        sf::Text text;
        text.setFont(font);
        text.setString("NIVEL " + std::to_string(i + 1));
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        levelTexts.push_back(text);
        
        // Preview del nivel
        sf::Texture previewTex;
        if (previewTex.loadFromFile("assets/imagenes/niveles/background.png")) {
            previewTextures.push_back(previewTex);
            sf::Sprite preview;
            preview.setTexture(previewTextures[i]);
            levelPreviews.push_back(preview);
        }
    }
    
    // Botón "ATRÁS" (mantenemos el rectángulo para fallback)
    sf::RectangleShape backButton(sf::Vector2f(200, 60));
    backButton.setFillColor(sf::Color(80, 80, 80, 200));
    backButton.setOutlineColor(sf::Color::White);
    backButton.setOutlineThickness(3);
    levelButtons.push_back(backButton);
    
    sf::Text backText;
    backText.setFont(font);
    backText.setString("< ATRAS");
    backText.setCharacterSize(30);
    backText.setFillColor(sf::Color::White);
    levelTexts.push_back(backText);
    
    std::cout << "LevelSelector inicializado correctamente" << std::endl;
}

void LevelSelector::updatePositions(const sf::Vector2u& windowSize) {
    float centerX = windowSize.x / 2.0f;
    float buttonWidth = 350;
    float buttonHeight = 400;
    float spacing = 100;
    float totalWidth = (buttonWidth * 2) + spacing;
    float startX = centerX - (totalWidth / 2);
    float yPos = windowSize.y * 0.25f;
    
    // Actualizar fondo
    if (backgroundTexture.getSize().x > 0) {
        sf::Vector2u texSize = backgroundTexture.getSize();
        float scaleX = static_cast<float>(windowSize.x) / texSize.x;
        float scaleY = static_cast<float>(windowSize.y) / texSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
        backgroundSprite.setPosition(0, 0);
    }
    
    // Actualizar título
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(centerX, windowSize.y * 0.12f);
    
    // Actualizar botones de niveles
    for (int i = 0; i < 2; i++) {
        float xPos = startX + i * (buttonWidth + spacing);
        levelButtons[i].setPosition(xPos, yPos);
        
        if (i < levelPreviews.size()) {
            sf::Vector2u texSize = previewTextures[i].getSize();
            float scale = std::min((buttonWidth - 20) / texSize.x, (buttonHeight - 100) / texSize.y);
            levelPreviews[i].setScale(scale, scale);
            
            sf::FloatRect previewBounds = levelPreviews[i].getLocalBounds();
            levelPreviews[i].setOrigin(previewBounds.width / 2, previewBounds.height / 2);
            levelPreviews[i].setPosition(xPos + buttonWidth / 2, yPos + (buttonHeight - 100) / 2);
        }
        
        sf::FloatRect textBounds = levelTexts[i].getLocalBounds();
        levelTexts[i].setOrigin(textBounds.width / 2, textBounds.height / 2);
        levelTexts[i].setPosition(xPos + buttonWidth / 2, yPos + buttonHeight - 50);
    }
    
    // Actualizar sprite del botón de salir - MÁS GRANDE
    if (exitButtonTexture.getSize().x > 0) {
        float scale = 120.0f / exitButtonTexture.getSize().x; // Aumentado de 80 a 120
        exitButtonSprite.setScale(scale, scale);
        exitButtonSprite.setPosition(50, windowSize.y - 130); // Ajustar posición
    }
    
    // Actualizar botón ATRÁS
    levelButtons[2].setPosition(50, windowSize.y - 130); // Ajustar posición
    sf::FloatRect backTextBounds = levelTexts[2].getLocalBounds();
    levelTexts[2].setOrigin(backTextBounds.width / 2, backTextBounds.height / 2);
    levelTexts[2].setPosition(170, windowSize.y - 65); // Ajustar posición
}

void LevelSelector::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (size_t i = 0; i < levelButtons.size(); i++) {
                bool clicked = false;
                
                // Si es el botón de atrás y tiene textura
                if (i == 2 && exitButtonTexture.getSize().x > 0) {
                    clicked = exitButtonSprite.getGlobalBounds().contains(
                        static_cast<float>(event.mouseButton.x),
                        static_cast<float>(event.mouseButton.y));
                } else {
                    clicked = levelButtons[i].getGlobalBounds().contains(
                        static_cast<float>(event.mouseButton.x),
                        static_cast<float>(event.mouseButton.y));
                }
                
                if (clicked) {
                    if (i < 2) {
                        selectedLevel = i + 1;
                        std::cout << "Nivel " << selectedLevel << " seleccionado" << std::endl;
                    } else {
                        selectedLevel = -2; // Atrás
                        std::cout << "Volver al menú principal" << std::endl;
                    }
                    return;
                }
            }
        }
    }
}

void LevelSelector::update(const sf::Vector2i& mousePos) {
    for (size_t i = 0; i < levelButtons.size(); i++) {
        bool hover = false;
        
        // Si es el botón de atrás y tiene textura
        if (i == 2 && exitButtonTexture.getSize().x > 0) {
            hover = exitButtonSprite.getGlobalBounds().contains(
                static_cast<float>(mousePos.x),
                static_cast<float>(mousePos.y));
            
            if (hover) {
                float scale = 135.0f / exitButtonTexture.getSize().x; // Aumentado de 90 a 135
                exitButtonSprite.setScale(scale, scale);
            } else {
                float scale = 120.0f / exitButtonTexture.getSize().x; // Aumentado de 80 a 120
                exitButtonSprite.setScale(scale, scale);
            }
        } else {
            hover = levelButtons[i].getGlobalBounds().contains(
                static_cast<float>(mousePos.x),
                static_cast<float>(mousePos.y));
        }
        
        if (hover) {
            levelButtons[i].setFillColor(sf::Color(100, 100, 100, 220));
            levelButtons[i].setOutlineColor(sf::Color(255, 140, 0));
            levelButtons[i].setOutlineThickness(5);
            levelTexts[i].setFillColor(sf::Color(255, 140, 0));
        } else {
            if (i < 2) {
                levelButtons[i].setFillColor(sf::Color(50, 50, 50, 200));
            } else {
                levelButtons[i].setFillColor(sf::Color(80, 80, 80, 200));
            }
            levelButtons[i].setOutlineColor(sf::Color::White);
            levelButtons[i].setOutlineThickness(3);
            levelTexts[i].setFillColor(sf::Color::White);
        }
    }
}

void LevelSelector::render(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    
    // Dibujar fondo
    window.draw(backgroundSprite);
    
    // Overlay completamente transparente
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 0)); // Transparencia en 0
    window.draw(overlay);
    
    // Dibujar título
    window.draw(title);
    
    // Dibujar botones de niveles
    for (int i = 0; i < 2; i++) {
        window.draw(levelButtons[i]);
        if (i < levelPreviews.size()) {
            window.draw(levelPreviews[i]);
        }
        window.draw(levelTexts[i]);
    }
    
    // Dibujar botón ATRÁS (sprite si existe, sino rectángulo con texto)
    if (exitButtonTexture.getSize().x > 0) {
        window.draw(exitButtonSprite);
    } else {
        window.draw(levelButtons[2]);
        window.draw(levelTexts[2]);
    }
}

int LevelSelector::getSelectedLevel() const {
    return selectedLevel;
}

void LevelSelector::resetSelection() {
    selectedLevel = -1;
}
