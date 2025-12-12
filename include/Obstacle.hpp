#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::RectangleShape shape;

public:
    Obstacle(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position);

    sf::FloatRect getBounds() const;
    void setFillColor(const sf::Color& color);
    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
};

#endif