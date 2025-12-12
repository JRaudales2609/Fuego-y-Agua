#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    int selectedButton;
    
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    sf::Texture startButtonTexture;
    sf::Sprite startButtonSprite;
    
    sf::Texture exitButtonTexture;  // NUEVO - Textura del botón salir
    sf::Sprite exitButtonSprite;    // NUEVO - Sprite del botón salir
    
public:
    Menu();
    void updatePositions(const sf::Vector2u& windowSize); // NUEVO
    void handleInput(sf::Event& event);
    void handleClick(const sf::Vector2f& mousePos); // NUEVO - Para clicks con coordenadas transformadas
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderWindow& window);
    int getSelectedOption() const; // 0 = Comenzar, 1 = Salir, -1 = ninguno
    void resetSelection(); // Para resetear la selección
};

#endif
