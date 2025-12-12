#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape shape;
    float speed;

public:
    Player(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position, float speed);

    void move(const sf::Vector2f& direction);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void setFillColor(const sf::Color& color);
    void draw(sf::RenderWindow& window);
};

#endif