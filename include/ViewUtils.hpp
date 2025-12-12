#ifndef VIEWUTILS_HPP
#define VIEWUTILS_HPP

#include <SFML/Graphics.hpp>

// Función para calcular la vista con letterboxing (barras negras)
inline sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}

// Función para convertir coordenadas del mouse a coordenadas del juego
inline sf::Vector2i getMousePositionInView(const sf::RenderWindow& window) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    return sf::Vector2i(static_cast<int>(worldPos.x), static_cast<int>(worldPos.y));
}

#endif // VIEWUTILS_HPP
