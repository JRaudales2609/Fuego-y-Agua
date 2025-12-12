#ifndef LEVELSELECTOR_HPP
#define LEVELSELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class LevelSelector {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::RectangleShape> levelButtons;
    std::vector<sf::Text> levelTexts;
    std::vector<sf::Sprite> levelPreviews;
    std::vector<sf::Texture> previewTextures;
    int selectedLevel;
    
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    sf::Texture exitButtonTexture;  // NUEVO
    sf::Sprite exitButtonSprite;    // NUEVO
    
public:
    LevelSelector();
    void updatePositions(const sf::Vector2u& windowSize); // NUEVO
    void handleInput(sf::Event& event);
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderWindow& window);
    int getSelectedLevel() const; // 1 = Nivel 1, 2 = Nivel 2, -1 = ninguno
    void resetSelection();
};

#endif
