#include "../include/Obstacle.hpp"

Obstacle::Obstacle(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position)
    : shape(size) {
    shape.setFillColor(color);
    shape.setPosition(position);
}

sf::FloatRect Obstacle::getBounds() const {
    return shape.getGlobalBounds();
}

void Obstacle::setFillColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void Obstacle::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}