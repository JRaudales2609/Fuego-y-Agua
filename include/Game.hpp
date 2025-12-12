#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "PauseMenu.hpp"
#include "WinMenu.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::View gameView;  // Vista fija de 1200x800
    Level currentLevel;
    
    // Texturas
    sf::Texture fireboyTexture, watergirlTexture;
    sf::Texture fireDiamondTexture, waterDiamondTexture;
    sf::Texture fireDoorTexture, waterDoorTexture;
    sf::Texture lavaTexture, waterTexture, mudTexture;
    sf::Texture pauseButtonTexture;  // NUEVO - Textura del botón de pausa
    
    // Sprites
    sf::Sprite player1, player2;
    sf::Sprite diamond1, diamond2;
    sf::Sprite diamond3, diamond4;  // NUEVOS diamantes
    sf::Sprite door1, door2;
    sf::Sprite lava, water, mud;
    
    // Física
    float speed;
    float gravity;
    float jumpForce;
    float player1VelocityY;
    float player2VelocityY;
    bool player1OnGround;
    bool player2OnGround;
    bool player1DoubleJumpAvailable;
    bool player2DoubleJumpAvailable;
    
    // Estado del juego
    int player1Diamonds;
    int player2Diamonds;
    bool diamond1Visible;
    bool diamond2Visible;
    bool diamond3Visible;  // NUEVO
    bool diamond4Visible;  // NUEVO
    
    // Animación
    int currentFrame1;
    int currentFrame2;
    float frameTime;
    sf::Clock animationClock;
    float baseScale1;
    float baseScale2;
    
    // Puertas
    sf::FloatRect door1Hitbox;
    sf::FloatRect door2Hitbox;
    
    // UI
    sf::Font font;
    sf::Text mouseCoordText;
    
    // Cronómetro
    sf::Clock gameClock;
    sf::Time elapsedTime;
    sf::Text timerText;
    
    // Menú de pausa
    PauseMenu pauseMenu;
    bool isPaused;
    sf::RectangleShape pauseButton;
    sf::Sprite pauseButtonSprite;  // NUEVO - Reemplaza pauseIcon
    
    // Menú de victoria
    WinMenu winMenu;
    bool hasWon;
    int winner; // 1 = Player 1, 2 = Player 2
    
public:
    Game(int startingLevel = 1, bool fullscreen = false);
    void run();
    void processEvents();
    void update();
    void render();
    void updateAnimation();
    sf::FloatRect getPlayer1Bounds();
    sf::FloatRect getPlayer2Bounds();
    void resetGame();
};

#endif