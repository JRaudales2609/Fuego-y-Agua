#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

// Estructura para representar un bloque del nivel
struct Block {
    sf::Sprite sprite;
    sf::FloatRect hitbox;
    std::string type; // "border", "platform", "lava", "water", "mud"
};

class Level {
public:
    Level(int levelNumber);
    
    void loadLevel();
    void changeLevel(int newLevelNumber); // Cambiar a otro nivel
    void render(sf::RenderWindow& window);
    
    // Getters para posiciones iniciales
    sf::Vector2f getPlayer1StartPos() const;
    sf::Vector2f getPlayer2StartPos() const;
    sf::Vector2f getDiamond1Pos() const;
    sf::Vector2f getDiamond2Pos() const;
    sf::Vector2f getDiamond3Pos() const;  // NUEVO
    sf::Vector2f getDiamond4Pos() const;  // NUEVO
    sf::Vector2f getDoor1Pos() const;
    sf::Vector2f getDoor2Pos() const;
    
    // Obtener obstáculos del nivel
    std::vector<sf::FloatRect> getPlatforms() const;
    std::vector<sf::ConvexShape> getTriangles() const; // Para formas triangulares
    std::vector<sf::Vector2f> getLavaPositions() const;
    std::vector<sf::Vector2f> getWaterPositions() const;
    std::vector<sf::Vector2f> getMudPositions() const;
    
private:
    int levelNumber;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    // Texturas de bloques
    sf::Texture borderBlockTexture;          // Para suelo y techo (horizontal)
    sf::Texture borderBlockVerticalTexture;  // Para paredes laterales (vertical)
    sf::Texture platformBlockTexture;
    
    // Bloques del nivel
    std::vector<Block> blocks;
    const float blockSize = 50.0f; // Tamaño de cada bloque
    
    // Posiciones iniciales
    sf::Vector2f player1Start;
    sf::Vector2f player2Start;
    sf::Vector2f diamond1Pos;
    sf::Vector2f diamond2Pos;
    sf::Vector2f diamond3Pos;  // NUEVO
    sf::Vector2f diamond4Pos;  // NUEVO
    sf::Vector2f door1Pos;
    sf::Vector2f door2Pos;
    
    // Colisiones y obstáculos
    std::vector<sf::FloatRect> platforms;
    std::vector<sf::ConvexShape> triangles; // Para formas triangulares/puntiagudas
    std::vector<sf::Vector2f> lavaPositions;
    std::vector<sf::Vector2f> waterPositions;
    std::vector<sf::Vector2f> mudPositions;
    
    // Método auxiliar para agregar bloques
    void addBlock(const std::string& type, float x, float y, float rotation = 0.0f);
    
    void setupLevel1();
    void setupLevel2();
    void setupLevel3();
};

#endif // LEVEL_HPP
