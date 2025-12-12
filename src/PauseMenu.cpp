#include "../include/PauseMenu.hpp"
#include <iostream>

PauseMenu::PauseMenu() : selectedOption(-1) {
    // Cargar fuente
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Error: No se pudo cargar ninguna fuente" << std::endl;
        }
    }
    
    // Overlay oscuro semi-transparente
    overlay.setSize(sf::Vector2f(1200, 800));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    
    // Cargar imagen del título PAUSA
    if (pauseTitleTexture.loadFromFile("assets/imagenes/ui/pause_title.png")) {
        std::cout << "✓ Imagen de título PAUSA cargada" << std::endl;
        pauseTitleSprite.setTexture(pauseTitleTexture);
    } else {
        std::cerr << "Advertencia: No se pudo cargar pause_title.png, usando texto" << std::endl;
    }
    
    // Título (fallback si no hay imagen)
    title.setFont(font);
    title.setString("PAUSA");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color(255, 140, 0));
    title.setOutlineThickness(4);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(600, 200);
    
    // Cargar texturas de los botones
    if (resumeButtonTexture.loadFromFile("assets/imagenes/ui/resume_button.png")) {
        std::cout << "✓ Textura del botón reanudar cargada" << std::endl;
        resumeButtonSprite.setTexture(resumeButtonTexture);
    }
    
    if (restartButtonTexture.loadFromFile("assets/imagenes/ui/restart_button.png")) {
        std::cout << "✓ Textura del botón reiniciar cargada" << std::endl;
        restartButtonSprite.setTexture(restartButtonTexture);
    }
    
    if (exitButtonTexture.loadFromFile("assets/imagenes/ui/exit_button.png")) {
        std::cout << "✓ Textura del botón de salir cargada" << std::endl;
        exitButtonSprite.setTexture(exitButtonTexture);
    }
    
    // Crear botones
    std::vector<std::string> buttonLabels = {"REANUDAR", "REINICIAR", "SALIR"};
    float buttonWidth = 300;
    float buttonHeight = 70;
    float startY = 350;
    float spacing = 100;
    
    for (size_t i = 0; i < buttonLabels.size(); i++) {
        // Botón
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setPosition(450, startY + i * spacing);
        button.setFillColor(sf::Color(50, 50, 50, 220));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(3);
        buttons.push_back(button);
        
        // Texto
        sf::Text text;
        text.setFont(font);
        text.setString(buttonLabels[i]);
        text.setCharacterSize(35);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(600, startY + i * spacing + buttonHeight / 2);
        buttonTexts.push_back(text);
    }
}

void PauseMenu::handleInput(sf::Event& event) {
    // Este método ya no debería usarse directamente con eventos
    // Las coordenadas del mouse deben ser transformadas antes de llegar aquí
}

void PauseMenu::handleClick(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].getGlobalBounds().contains(mousePos)) {
            selectedOption = static_cast<int>(i);
            std::cout << "Opción de pausa seleccionada: " << i << std::endl;
            return;
        }
    }
}

void PauseMenu::update(const sf::Vector2i& mousePos) {
    float spriteWidth = 200.0f;
    float hoverWidth = 220.0f;
    
    for (size_t i = 0; i < buttons.size(); i++) {
        bool hover = buttons[i].getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y));
        
        // Efecto hover en sprites
        if (hover) {
            if (i == 0 && resumeButtonTexture.getSize().x > 0) {
                resumeButtonSprite.setScale(hoverWidth / resumeButtonTexture.getSize().x, 
                                           hoverWidth / resumeButtonTexture.getSize().x);
            } else if (i == 1 && restartButtonTexture.getSize().x > 0) {
                restartButtonSprite.setScale(hoverWidth / restartButtonTexture.getSize().x, 
                                            hoverWidth / restartButtonTexture.getSize().x);
            } else if (i == 2 && exitButtonTexture.getSize().x > 0) {
                exitButtonSprite.setScale(hoverWidth / exitButtonTexture.getSize().x, 
                                         hoverWidth / exitButtonTexture.getSize().x);
            }
            
            buttons[i].setFillColor(sf::Color(100, 100, 100, 240));
            buttonTexts[i].setFillColor(sf::Color(255, 140, 0));
        } else {
            if (i == 0 && resumeButtonTexture.getSize().x > 0) {
                resumeButtonSprite.setScale(spriteWidth / resumeButtonTexture.getSize().x, 
                                           spriteWidth / resumeButtonTexture.getSize().x);
            } else if (i == 1 && restartButtonTexture.getSize().x > 0) {
                restartButtonSprite.setScale(spriteWidth / restartButtonTexture.getSize().x, 
                                            spriteWidth / restartButtonTexture.getSize().x);
            } else if (i == 2 && exitButtonTexture.getSize().x > 0) {
                exitButtonSprite.setScale(spriteWidth / exitButtonTexture.getSize().x, 
                                         spriteWidth / exitButtonTexture.getSize().x);
            }
            
            buttons[i].setFillColor(sf::Color(50, 50, 50, 220));
            buttonTexts[i].setFillColor(sf::Color::White);
        }
    }
}

void PauseMenu::updatePositions(const sf::Vector2u& windowSize) {
    // SIEMPRE usar coordenadas del juego 1200x800, NO el tamaño físico de ventana
    const float gameWidth = 1200.0f;
    const float gameHeight = 800.0f;
    float centerX = gameWidth / 2.0f;
    float buttonWidth = 300;
    float buttonHeight = 70;
    float startY = gameHeight * 0.45f;
    float spacing = 100;
    
    // Actualizar overlay (tamaño del juego)
    overlay.setSize(sf::Vector2f(gameWidth, gameHeight));
    
    // Actualizar imagen del título PAUSA
    if (pauseTitleTexture.getSize().x > 0) {
        // Escalar la imagen a un tamaño apropiado (por ejemplo, 300px de ancho)
        float scale = 300.0f / pauseTitleTexture.getSize().x;
        pauseTitleSprite.setScale(scale, scale);
        
        sf::FloatRect pauseBounds = pauseTitleSprite.getGlobalBounds();
        pauseTitleSprite.setOrigin(pauseBounds.width / (2 * scale), pauseBounds.height / (2 * scale));
        pauseTitleSprite.setPosition(centerX, gameHeight * 0.25f);
    }
    
    // Actualizar título de texto (fallback)
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(centerX, gameHeight * 0.25f);
    
    // Actualizar botones
    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i].setPosition(centerX - buttonWidth / 2, startY + i * spacing);
        
        sf::FloatRect textBounds = buttonTexts[i].getLocalBounds();
        buttonTexts[i].setOrigin(textBounds.width / 2, textBounds.height / 2);
        buttonTexts[i].setPosition(centerX, startY + i * spacing + buttonHeight / 2);
    }
    
    // Actualizar sprites de botones - Tamaño 200x70 para que se vean completos
    float spriteWidth = 200.0f;
    
    // Botón REANUDAR (índice 0)
    if (resumeButtonTexture.getSize().x > 0) {
        float scale = spriteWidth / resumeButtonTexture.getSize().x;
        resumeButtonSprite.setScale(scale, scale);
        sf::FloatRect bounds = resumeButtonSprite.getGlobalBounds();
        resumeButtonSprite.setPosition(centerX - bounds.width / 2, startY + 15);
    }
    
    // Botón REINICIAR (índice 1)
    if (restartButtonTexture.getSize().x > 0) {
        float scale = spriteWidth / restartButtonTexture.getSize().x;
        restartButtonSprite.setScale(scale, scale);
        sf::FloatRect bounds = restartButtonSprite.getGlobalBounds();
        restartButtonSprite.setPosition(centerX - bounds.width / 2, startY + spacing + 15);
    }
    
    // Botón SALIR (índice 2)
    if (exitButtonTexture.getSize().x > 0) {
        float scale = spriteWidth / exitButtonTexture.getSize().x;
        exitButtonSprite.setScale(scale, scale);
        sf::FloatRect bounds = exitButtonSprite.getGlobalBounds();
        exitButtonSprite.setPosition(centerX - bounds.width / 2, startY + 2 * spacing + 15);
    }
}

void PauseMenu::render(sf::RenderWindow& window) {
    window.draw(overlay);
    
    // Dibujar imagen del título PAUSA si existe, sino el texto
    if (pauseTitleTexture.getSize().x > 0) {
        window.draw(pauseTitleSprite);
    } else {
        window.draw(title);
    }
    
    for (size_t i = 0; i < buttons.size(); i++) {
        // Si existe la textura, solo dibujar el sprite (sin rectángulo ni texto)
        if (i == 0 && resumeButtonTexture.getSize().x > 0) {
            window.draw(resumeButtonSprite);
        } else if (i == 1 && restartButtonTexture.getSize().x > 0) {
            window.draw(restartButtonSprite);
        } else if (i == 2 && exitButtonTexture.getSize().x > 0) {
            window.draw(exitButtonSprite);
        } else {
            // Fallback: dibujar botón rectangular con texto
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
    }
}

int PauseMenu::getSelectedOption() const {
    return selectedOption;
}

void PauseMenu::resetSelection() {
    selectedOption = -1;
}
