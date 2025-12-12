#include "../include/Player.hpp"

Player::Player(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position, float speed)
    : shape(size), speed(speed) {
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Player::move(const sf::Vector2f& direction) {
    shape.move(direction * speed);
}

void Player::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

void Player::setFillColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}