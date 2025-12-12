#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PauseMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    int selectedOption;
    
    sf::RectangleShape overlay;
    
    sf::Texture pauseTitleTexture;     // NUEVO - Imagen del título PAUSA
    sf::Sprite pauseTitleSprite;       // NUEVO
    
    sf::Texture resumeButtonTexture;   // NUEVO
    sf::Texture restartButtonTexture;  // NUEVO
    sf::Texture exitButtonTexture;
    
    sf::Sprite resumeButtonSprite;     // NUEVO
    sf::Sprite restartButtonSprite;    // NUEVO
    sf::Sprite exitButtonSprite;
    
public:
    PauseMenu();
    void updatePositions(const sf::Vector2u& windowSize); // NUEVO
    void handleInput(sf::Event& event);
    void handleClick(const sf::Vector2f& mousePos); // NUEVO - Para clicks con coordenadas transformadas
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderWindow& window);
    int getSelectedOption() const; // 0 = Reanudar, 1 = Reiniciar, 2 = Salir, -1 = ninguno
    void resetSelection();
};

#endif
