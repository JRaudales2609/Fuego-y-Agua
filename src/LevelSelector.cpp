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
    
    // Cargar imagen del título
    if (titleTexture.loadFromFile("assets/imagenes/ui/level_selector_title.png")) {
        titleSprite.setTexture(titleTexture);
        std::cout << "✓ Imagen del título 'Selecciona Nivel' cargada" << std::endl;
    } else {
        std::cerr << "Advertencia: No se pudo cargar level_selector_title.png, usando texto" << std::endl;
    }
    
    // Título (fallback si no hay imagen)
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
    // Primero reservar espacio para evitar reubicaciones
    previewTextures.reserve(2);
    levelPreviews.reserve(2);
    
    for (int i = 0; i < 2; i++) {
        sf::RectangleShape button(sf::Vector2f(450, 300)); // Cambiado a más ancho y menos alto
        button.setFillColor(sf::Color::Transparent); // Sin relleno
        button.setOutlineColor(sf::Color::Transparent); // Sin borde
        button.setOutlineThickness(0); // Sin grosor
        levelButtons.push_back(button);
        
        sf::Text text;
        text.setFont(font);
        text.setString(""); // Sin texto
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Transparent); // Texto invisible
        levelTexts.push_back(text);
        
        // Crear textura en el vector primero
        previewTextures.push_back(sf::Texture());
        
        // Cargar preview específico para cada nivel
        std::string previewPath = "assets/imagenes/niveles/level" + std::to_string(i + 1) + "_preview.png";
        std::cout << "================================================" << std::endl;
        std::cout << "Nivel " << (i + 1) << " - Intentando cargar: " << previewPath << std::endl;
        
        if (previewTextures[i].loadFromFile(previewPath)) {
            std::cout << "✓ ÉXITO: Textura de nivel " << (i + 1) << " cargada" << std::endl;
            std::cout << "  Dimensiones: " << previewTextures[i].getSize().x << "x" << previewTextures[i].getSize().y << std::endl;
        } else {
            std::cerr << "✗ ERROR: No se pudo cargar " << previewPath << std::endl;
        }
        std::cout << "================================================" << std::endl;
        
        // Crear sprite SIN asignar textura todavía
        levelPreviews.push_back(sf::Sprite());
    }
    
    // AHORA asignar las texturas a los sprites después de que el vector esté completo
    for (int i = 0; i < 2; i++) {
        if (previewTextures[i].getSize().x > 0) {
            levelPreviews[i].setTexture(previewTextures[i]);
            std::cout << "Sprite " << (i + 1) << " enlazado a textura correctamente" << std::endl;
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
    // SIEMPRE usar coordenadas del juego 1200x800, NO el tamaño físico de ventana
    const float gameWidth = 1200.0f;
    const float gameHeight = 800.0f;
    float centerX = gameWidth / 2.0f;
    float buttonWidth = 450;  // Cambiado de 350 a 450
    float buttonHeight = 300; // Cambiado de 400 a 300
    float spacing = 80;       // Reducido spacing para que quepan mejor
    float totalWidth = (buttonWidth * 2) + spacing;
    float startX = centerX - (totalWidth / 2);
    float yPos = gameHeight * 0.28f; // Ajustado para centrar mejor
    
    // Actualizar fondo
    if (backgroundTexture.getSize().x > 0) {
        sf::Vector2u texSize = backgroundTexture.getSize();
        float scaleX = gameWidth / texSize.x;
        float scaleY = gameHeight / texSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
        backgroundSprite.setPosition(0, 0);
    }
    
    // Actualizar título
    if (titleTexture.getSize().x > 0) {
        // Usar imagen del título
        sf::Vector2u texSize = titleTexture.getSize();
        float scale = 600.0f / texSize.x; // Ancho de 600px para el título
        titleSprite.setScale(scale, scale);
        sf::FloatRect titleBounds = titleSprite.getLocalBounds();
        titleSprite.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        titleSprite.setPosition(centerX, gameHeight * 0.12f);
    } else {
        // Fallback: usar texto
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        title.setPosition(centerX, gameHeight * 0.12f);
    }
    
    // Actualizar botones de niveles
    for (int i = 0; i < 2; i++) {
        float xPos = startX + i * (buttonWidth + spacing);
        levelButtons[i].setPosition(xPos, yPos);
        
        if (i < levelPreviews.size()) {
            sf::Vector2u texSize = previewTextures[i].getSize();
            // Escalar para que la imagen llene todo el botón con un pequeño margen
            float scale = std::min((buttonWidth - 10) / texSize.x, (buttonHeight - 60) / texSize.y);
            levelPreviews[i].setScale(scale, scale);
            
            sf::FloatRect previewBounds = levelPreviews[i].getLocalBounds();
            levelPreviews[i].setOrigin(previewBounds.width / 2, previewBounds.height / 2);
            levelPreviews[i].setPosition(xPos + buttonWidth / 2, yPos + (buttonHeight - 60) / 2);
        }
        
        sf::FloatRect textBounds = levelTexts[i].getLocalBounds();
        levelTexts[i].setOrigin(textBounds.width / 2, textBounds.height / 2);
        levelTexts[i].setPosition(xPos + buttonWidth / 2, yPos + buttonHeight - 50);
    }
    
    // Actualizar sprite del botón de salir - MÁS GRANDE (coordenadas fijas)
    if (exitButtonTexture.getSize().x > 0) {
        float scale = 120.0f / exitButtonTexture.getSize().x;
        exitButtonSprite.setScale(scale, scale);
        exitButtonSprite.setPosition(50, 670); // Coordenadas fijas (800 - 130)
    }
    
    // Actualizar botón ATRÁS (coordenadas fijas)
    levelButtons[2].setPosition(50, 670); // Coordenadas fijas (800 - 130)
    sf::FloatRect backTextBounds = levelTexts[2].getLocalBounds();
    levelTexts[2].setOrigin(backTextBounds.width / 2, backTextBounds.height / 2);
    levelTexts[2].setPosition(170, 735); // Coordenadas fijas (800 - 65)
}

void LevelSelector::handleInput(sf::Event& event) {
    // Método obsoleto - usar handleClick con coordenadas transformadas
}

void LevelSelector::handleClick(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < levelButtons.size(); i++) {
        bool clicked = false;
        
        // Si es el botón de atrás y tiene textura
        if (i == 2 && exitButtonTexture.getSize().x > 0) {
            clicked = exitButtonSprite.getGlobalBounds().contains(mousePos);
        } else {
            clicked = levelButtons[i].getGlobalBounds().contains(mousePos);
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
            // Efecto hover: Escalar la imagen ligeramente más grande
            if (i < levelPreviews.size() && i < previewTextures.size()) {
                sf::Vector2u texSize = previewTextures[i].getSize();
                float scale = std::min((450.0f - 10) / texSize.x, (300.0f - 60) / texSize.y);
                float hoverScale = scale * 1.05f; // 5% más grande en hover
                levelPreviews[i].setScale(hoverScale, hoverScale);
            }
        } else {
            // Estado normal: Escala normal
            if (i < levelPreviews.size() && i < previewTextures.size()) {
                sf::Vector2u texSize = previewTextures[i].getSize();
                float scale = std::min((450.0f - 10) / texSize.x, (300.0f - 60) / texSize.y);
                levelPreviews[i].setScale(scale, scale);
            }
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
    
    // Dibujar título (imagen o texto como fallback)
    if (titleTexture.getSize().x > 0) {
        window.draw(titleSprite);
    } else {
        window.draw(title);
    }
    
    // Dibujar botones de niveles
    for (int i = 0; i < 2; i++) {
        window.draw(levelButtons[i]);
        if (i < levelPreviews.size()) {
            // Debug: imprimir información del sprite solo una vez al inicio
            static bool debugPrinted = false;
            if (!debugPrinted) {
                std::cout << "\n=== DEBUG RENDER NIVEL " << (i + 1) << " ===" << std::endl;
                std::cout << "Sprite existe: SÍ" << std::endl;
                std::cout << "Posición: (" << levelPreviews[i].getPosition().x << ", " << levelPreviews[i].getPosition().y << ")" << std::endl;
                std::cout << "Escala: (" << levelPreviews[i].getScale().x << ", " << levelPreviews[i].getScale().y << ")" << std::endl;
                std::cout << "Textura válida: " << (levelPreviews[i].getTexture() != nullptr ? "SÍ" : "NO") << std::endl;
                if (levelPreviews[i].getTexture()) {
                    std::cout << "Tamaño textura: " << levelPreviews[i].getTexture()->getSize().x << "x" << levelPreviews[i].getTexture()->getSize().y << std::endl;
                }
                std::cout << "Color: R=" << (int)levelPreviews[i].getColor().r << " G=" << (int)levelPreviews[i].getColor().g 
                         << " B=" << (int)levelPreviews[i].getColor().b << " A=" << (int)levelPreviews[i].getColor().a << std::endl;
                if (i == 1) debugPrinted = true; // Imprimir solo en la primera pasada completa
            }
            
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
