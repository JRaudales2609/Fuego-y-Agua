#ifndef WINMENU_HPP
#define WINMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class WinMenu {
private:
    sf::Font font;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    int selectedOption;
    
    sf::RectangleShape overlay;
    
    // Texturas para títulos de victoria
    sf::Texture player1WinTexture;
    sf::Texture player2WinTexture;
    sf::Sprite winTitleSprite;
    
    // Texturas de botones
    sf::Texture restartButtonTexture;
    sf::Texture exitButtonTexture;
    
    sf::Sprite restartButtonSprite;
    sf::Sprite exitButtonSprite;
    
    // Texto del tiempo
    sf::Text timeText;
    
    int winner; // 1 = Player 1, 2 = Player 2
    
public:
    WinMenu();
    void setWinner(int playerNumber, const std::string& timeStr);
    void updatePositions(const sf::Vector2u& windowSize);
    void handleClick(const sf::Vector2f& mousePos);
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderWindow& window);
    int getSelectedOption() const; // 0 = Reiniciar, 1 = Salir, -1 = ninguno
    void resetSelection();
};

#endif // WINMENU_HPP
