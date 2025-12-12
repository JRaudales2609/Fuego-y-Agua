#include <SFML/Graphics.hpp>
#include "../include/Game.hpp"
#include <iostream>

Game::Game(int startingLevel) :
    window(sf::VideoMode(1200, 800), "Fuego y Agua - 2 Jugadores"),
    currentLevel(startingLevel),
    speed(7.0f),
    gravity(0.5f),
    jumpForce(-9.5f),
    player1VelocityY(0.0f),
    player2VelocityY(0.0f),
    player1OnGround(false),
    player2OnGround(false),
    player1DoubleJumpAvailable(false),
    player2DoubleJumpAvailable(false),
    player1Diamonds(0),
    player2Diamonds(0),
    diamond1Visible(true),
    diamond2Visible(true),
    diamond3Visible(true),  // NUEVO
    diamond4Visible(true),  // NUEVO
    currentFrame1(0),
    currentFrame2(0),
    frameTime(0.1f),
    baseScale1(0.0f),
    baseScale2(0.0f),
    isPaused(false)
{
    std::cout << "Iniciando juego en nivel " << startingLevel << std::endl;
    window.setFramerateLimit(60);

    // Cargar el nivel
    currentLevel.loadLevel();

    // Cargar fuente
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Advertencia: No se pudo cargar la fuente" << std::endl;
        }
    }
    mouseCoordText.setFont(font);
    mouseCoordText.setCharacterSize(20);
    mouseCoordText.setFillColor(sf::Color::White);
    mouseCoordText.setPosition(10.0f, 10.0f);

    // Cargar texturas de diamantes
    if (!fireDiamondTexture.loadFromFile("assets/imagenes/diamantes/fire_diamond.png")) {
        std::cerr << "Error: No se pudo cargar fire_diamond.png" << std::endl;
    }
    if (!waterDiamondTexture.loadFromFile("assets/imagenes/diamantes/water_diamond.png")) {
        std::cerr << "Error: No se pudo cargar water_diamond.png" << std::endl;
    }
    if (!fireDoorTexture.loadFromFile("assets/imagenes/puertas/fire_door.png")) {
        std::cerr << "Error: No se pudo cargar fire_door.png" << std::endl;
    }
    if (!waterDoorTexture.loadFromFile("assets/imagenes/puertas/water_door.png")) {
        std::cerr << "Error: No se pudo cargar water_door.png" << std::endl;
    }
    if (!fireboyTexture.loadFromFile("assets/imagenes/personajes/fireboy_spritesheet.png")) {
        std::cerr << "Error: No se pudo cargar fireboy_spritesheet.png" << std::endl;
    }
    if (!watergirlTexture.loadFromFile("assets/imagenes/personajes/watergirl_spritesheet.png")) {
        std::cerr << "Error: No se pudo cargar watergirl_spritesheet.png" << std::endl;
    }
    // Cargar texturas de obstáculos
    if (!lavaTexture.loadFromFile("assets/imagenes/obstaculos/lava.png")) {
        std::cerr << "Error: No se pudo cargar lava.png" << std::endl;
    }
    if (!waterTexture.loadFromFile("assets/imagenes/obstaculos/water.png")) {
        std::cerr << "Error: No se pudo cargar water.png" << std::endl;
    }
    if (!mudTexture.loadFromFile("assets/imagenes/obstaculos/mud.png")) {
        std::cerr << "Error: No se pudo cargar mud.png" << std::endl;
    }
    
    // Cargar textura del botón de pausa
    if (!pauseButtonTexture.loadFromFile("assets/imagenes/ui/pause_button.png")) {
        std::cerr << "Advertencia: No se pudo cargar pause_button.png, usando color sólido" << std::endl;
        // Si no carga, el botón será solo el rectángulo
    } else {
        std::cout << "pause_button.png cargado correctamente" << std::endl;
        pauseButtonSprite.setTexture(pauseButtonTexture);
    }

    // Configurar Jugador 1 - Fireboy
    player1.setTexture(fireboyTexture);
    int frameWidth1 = fireboyTexture.getSize().x / 4;
    int frameHeight1 = fireboyTexture.getSize().y;
    player1.setTextureRect(sf::IntRect(0, 0, frameWidth1, frameHeight1));
    player1.setOrigin(frameWidth1 / 2.0f, frameHeight1 / 2.0f);
    player1.setPosition(currentLevel.getPlayer1StartPos());
    float player1Scale = 50.0f / frameWidth1;
    player1.setScale(player1Scale, player1Scale);
    baseScale1 = player1Scale;

    // Configurar Jugador 2 - Watergirl
    player2.setTexture(watergirlTexture);
    int frameWidth2 = watergirlTexture.getSize().x / 4;
    int frameHeight2 = watergirlTexture.getSize().y;
    player2.setTextureRect(sf::IntRect(0, 0, frameWidth2, frameHeight2));
    player2.setOrigin(frameWidth2 / 2.0f, frameHeight2 / 2.0f);
    player2.setPosition(currentLevel.getPlayer2StartPos());
    float player2Scale = 50.0f / frameWidth2;
    player2.setScale(player2Scale, player2Scale);
    baseScale2 = player2Scale;

    // Configurar diamante 1 (fuego)
    diamond1.setTexture(fireDiamondTexture);
    diamond1.setPosition(currentLevel.getDiamond1Pos());
    float scale1 = 50.0f / fireDiamondTexture.getSize().x;
    diamond1.setScale(scale1, scale1);
    
    // Configurar diamante 2 (agua)
    diamond2.setTexture(waterDiamondTexture);
    diamond2.setPosition(currentLevel.getDiamond2Pos());
    float scale2 = 50.0f / waterDiamondTexture.getSize().x;
    diamond2.setScale(scale2, scale2);
    
    // Configurar diamante 3 (fuego 2) - NUEVO
    diamond3.setTexture(fireDiamondTexture);
    diamond3.setPosition(currentLevel.getDiamond3Pos());
    diamond3.setScale(scale1, scale1);
    
    // Configurar diamante 4 (agua 2) - NUEVO
    diamond4.setTexture(waterDiamondTexture);
    diamond4.setPosition(currentLevel.getDiamond4Pos());
    diamond4.setScale(scale2, scale2);

    // Configurar obstáculos
    lava.setTexture(lavaTexture);
    float lavaScale = 150.0f / lavaTexture.getSize().x;
    lava.setScale(lavaScale, lavaScale);
    lava.setOrigin(lavaTexture.getSize().x / 2.0f, lavaTexture.getSize().y / 2.0f);
    
    water.setTexture(waterTexture);
    float waterScale = 150.0f / waterTexture.getSize().x;
    water.setScale(waterScale, waterScale);
    water.setOrigin(waterTexture.getSize().x / 2.0f, waterTexture.getSize().y / 2.0f);
    
    mud.setTexture(mudTexture);
    float mudScale = 150.0f / mudTexture.getSize().x;
    mud.setScale(mudScale, mudScale);
    mud.setOrigin(mudTexture.getSize().x / 2.0f, mudTexture.getSize().y / 2.0f);

    // Configurar puertas
    door1.setTexture(fireDoorTexture);
    door1.setPosition(currentLevel.getDoor1Pos());
    float doorScale1 = 80.0f / fireDoorTexture.getSize().x;
    door1.setScale(doorScale1, doorScale1);
    sf::Vector2f door1Pos = currentLevel.getDoor1Pos();
    door1Hitbox = sf::FloatRect(door1Pos.x + 25.0f, door1Pos.y + 20.0f, 30.0f, 40.0f);

    door2.setTexture(waterDoorTexture);
    door2.setPosition(currentLevel.getDoor2Pos());
    float doorScale2 = 80.0f / waterDoorTexture.getSize().x;
    door2.setScale(doorScale2, doorScale2);
    sf::Vector2f door2Pos = currentLevel.getDoor2Pos();
    door2Hitbox = sf::FloatRect(door2Pos.x + 25.0f, door2Pos.y + 20.0f, 30.0f, 40.0f);
    
    // Configurar botón de pausa (esquina superior derecha)
    pauseButton.setSize(sf::Vector2f(50, 50));
    pauseButton.setPosition(1130, 10);
    pauseButton.setFillColor(sf::Color(50, 50, 50, 200));
    pauseButton.setOutlineColor(sf::Color::White);
    pauseButton.setOutlineThickness(2);
    
    // Configurar sprite del botón de pausa
    if (pauseButtonTexture.getSize().x > 0) {
        // Escalar la imagen al tamaño del botón
        float scaleX = 50.0f / pauseButtonTexture.getSize().x;
        float scaleY = 50.0f / pauseButtonTexture.getSize().y;
        pauseButtonSprite.setScale(scaleX, scaleY);
        pauseButtonSprite.setPosition(1130, 10);
    }
    
    std::cout << "Juego inicializado con menu de pausa" << std::endl;
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    // Actualizar posiciones del menú de pausa si está pausado
    if (isPaused) {
        pauseMenu.updatePositions(window.getSize());
    }
    
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        
        if (isPaused) {
            // Si está en pausa, solo manejar eventos del menú de pausa
            pauseMenu.handleInput(event);
        } else {
            // Juego no pausado
            if (event.type == sf::Event::KeyPressed) {
                // Tecla ESC para pausar
                if (event.key.code == sf::Keyboard::Escape) {
                    isPaused = true;
                    pauseMenu.resetSelection();
                    std::cout << "Juego pausado (ESC)" << std::endl;
                }
                // Salto Jugador 1 (W)
                else if (event.key.code == sf::Keyboard::W) {
                    if (player1OnGround) {
                        player1VelocityY = jumpForce;
                        player1OnGround = false;
                        player1DoubleJumpAvailable = true;
                    } else if (player1DoubleJumpAvailable) {
                        player1VelocityY = jumpForce;
                        player1DoubleJumpAvailable = false;
                    }
                }
                // Salto Jugador 2 (Up)
                else if (event.key.code == sf::Keyboard::Up) {
                    if (player2OnGround) {
                        player2VelocityY = jumpForce;
                        player2OnGround = false;
                        player2DoubleJumpAvailable = true;
                    } else if (player2DoubleJumpAvailable) {
                        player2VelocityY = jumpForce;
                        player2DoubleJumpAvailable = false;
                    }
                }
            }
            // Click en botón de pausa
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                         static_cast<float>(event.mouseButton.y));
                    if (pauseButton.getGlobalBounds().contains(mousePos)) {
                        isPaused = true;
                        pauseMenu.resetSelection();
                        std::cout << "Juego pausado (boton)" << std::endl;
                    }
                }
            }
        }
    }
}

void Game::update()
{
    if (isPaused) {
        // Actualizar menú de pausa
        pauseMenu.update(sf::Mouse::getPosition(window));
        
        int selectedOption = pauseMenu.getSelectedOption();
        if (selectedOption == 0) { // Reanudar
            isPaused = false;
            pauseMenu.resetSelection();
            std::cout << "Reanudando juego..." << std::endl;
        } else if (selectedOption == 1) { // Reiniciar
            resetGame();
            isPaused = false;
            pauseMenu.resetSelection();
            std::cout << "Reiniciando nivel..." << std::endl;
        } else if (selectedOption == 2) { // Salir
            std::cout << "Saliendo al menu principal..." << std::endl;
            window.close();
        }
        return; // No actualizar el juego si está pausado
    }
    
    // Obtener posición del mouse y mostrarla en pantalla
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    mouseCoordText.setString("Mouse: X=" + std::to_string(mousePos.x) + " Y=" + std::to_string(mousePos.y));

    // === FÍSICA: Aplicar gravedad ===
    player1VelocityY += gravity;
    player2VelocityY += gravity;

    std::vector<sf::FloatRect> platforms = currentLevel.getPlatforms();

    // Movimiento y colisiones Jugador 1
    sf::Vector2f player1OldPos = player1.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player1.move(-speed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player1.move(speed, 0.0f);

    for(const auto& platform : platforms) {
        if (player1.getGlobalBounds().intersects(platform)) {
            player1.setPosition(player1OldPos);
            break;
        }
    }

    player1OldPos = player1.getPosition();
    player1.move(0.0f, player1VelocityY);
    player1OnGround = false;
    
    for(const auto& platform : platforms) {
        if (player1.getGlobalBounds().intersects(platform)) {
            if (player1VelocityY > 0) {
                player1.setPosition(player1OldPos);
                player1VelocityY = 0.0f;
                player1OnGround = true;
                player1DoubleJumpAvailable = false;
            } else if (player1VelocityY < 0) {
                player1.setPosition(player1OldPos);
                player1VelocityY = 0.0f;
            }
            break;
        }
    }

    // Movimiento y colisiones Jugador 2
    sf::Vector2f player2OldPos = player2.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player2.move(-speed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player2.move(speed, 0.0f);

    for(const auto& platform : platforms) {
        if (player2.getGlobalBounds().intersects(platform)) {
            player2.setPosition(player2OldPos);
            break;
        }
    }

    player2OldPos = player2.getPosition();
    player2.move(0.0f, player2VelocityY);
    player2OnGround = false;
    
    for(const auto& platform : platforms) {
        if (player2.getGlobalBounds().intersects(platform)) {
            if (player2VelocityY > 0) {
                player2.setPosition(player2OldPos);
                player2VelocityY = 0.0f;
                player2OnGround = true;
                player2DoubleJumpAvailable = false;
            } else if (player2VelocityY < 0) {
                player2.setPosition(player2OldPos);
                player2VelocityY = 0.0f;
            }
            break;
        }
    }

    // Colisiones con diamantes - ACTUALIZADO
    if (diamond1Visible && player1.getGlobalBounds().intersects(diamond1.getGlobalBounds())) {
        diamond1Visible = false;
        player1Diamonds++;
        std::cout << "Fireboy recogió diamante 1!" << std::endl;
    }
    if (diamond2Visible && player2.getGlobalBounds().intersects(diamond2.getGlobalBounds())) {
        diamond2Visible = false;
        player2Diamonds++;
        std::cout << "Watergirl recogió diamante 1!" << std::endl;
    }
    if (diamond3Visible && player1.getGlobalBounds().intersects(diamond3.getGlobalBounds())) {
        diamond3Visible = false;
        player1Diamonds++;
        std::cout << "Fireboy recogió diamante 2!" << std::endl;
    }
    if (diamond4Visible && player2.getGlobalBounds().intersects(diamond4.getGlobalBounds())) {
        diamond4Visible = false;
        player2Diamonds++;
        std::cout << "Watergirl recogió diamante 2!" << std::endl;
    }

    // Colisiones con puertas - Ahora necesitan 2 diamantes cada uno
    if (player1.getGlobalBounds().intersects(door1Hitbox) && player1Diamonds >= 2) {
        std::cout << "Fireboy ha completado el nivel!" << std::endl;
        window.close();
    }
    if (player2.getGlobalBounds().intersects(door2Hitbox) && player2Diamonds >= 2) {
        std::cout << "Watergirl ha completado el nivel!" << std::endl;
        window.close();
    }

    // Colisiones con obstáculos
    std::vector<sf::Vector2f> lavaPos = currentLevel.getLavaPositions();
    std::vector<sf::Vector2f> waterPos = currentLevel.getWaterPositions();
    std::vector<sf::Vector2f> mudPos = currentLevel.getMudPositions();
    
    for(const auto& pos : lavaPos) {
        sf::FloatRect hitbox(pos.x - 65.0f, pos.y - 15.0f, 130.0f, 30.0f);
        if (player2.getGlobalBounds().intersects(hitbox)) {
            player2.setPosition(currentLevel.getPlayer2StartPos());
        }
    }
    
    for(const auto& pos : waterPos) {
        sf::FloatRect hitbox(pos.x - 65.0f, pos.y - 15.0f, 130.0f, 30.0f);
        if (player1.getGlobalBounds().intersects(hitbox)) {
            player1.setPosition(currentLevel.getPlayer1StartPos());
        }
    }
    
    for(const auto& pos : mudPos) {
        sf::FloatRect hitbox(pos.x - 65.0f, pos.y - 15.0f, 130.0f, 30.0f);
        if (player1.getGlobalBounds().intersects(hitbox)) {
            player1.setPosition(currentLevel.getPlayer1StartPos());
        }
        if (player2.getGlobalBounds().intersects(hitbox)) {
            player2.setPosition(currentLevel.getPlayer2StartPos());
        }
    }

    updateAnimation();
}

void Game::updateAnimation()
{
    // Actualizar animación si ha pasado suficiente tiempo
    if (animationClock.getElapsedTime().asSeconds() > frameTime) {
        // Determinar si los jugadores están en movimiento y dirección
        bool player1Moving = sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        bool player2Moving = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        // Dimensiones de frames para cada jugador
        int frameWidth1 = fireboyTexture.getSize().x / 4;
        int frameHeight1 = fireboyTexture.getSize().y;
        int frameWidth2 = watergirlTexture.getSize().x / 4;
        int frameHeight2 = watergirlTexture.getSize().y;

        // Animar jugador 1 si se está moviendo
        if (player1Moving) {
            currentFrame1 = (currentFrame1 + 1) % 4; // Ciclar entre 0-3
            player1.setTextureRect(sf::IntRect(currentFrame1 * frameWidth1, 0, frameWidth1, frameHeight1));
            
            // Voltear sprite según la dirección horizontal
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                // Moviendo a la izquierda - voltear sprite
                player1.setScale(-baseScale1, baseScale1);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                // Moviendo a la derecha - orientación normal
                player1.setScale(baseScale1, baseScale1);
            }
        } else {
            currentFrame1 = 0; // Volver al primer frame cuando está quieto
            player1.setTextureRect(sf::IntRect(0, 0, frameWidth1, frameHeight1));
        }

        // Animar jugador 2 si se está moviendo
        if (player2Moving) {
            currentFrame2 = (currentFrame2 + 1) % 4; // Ciclar entre 0-3
            player2.setTextureRect(sf::IntRect(currentFrame2 * frameWidth2, 0, frameWidth2, frameHeight2));
            
            // Voltear sprite según la dirección horizontal
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                // Moviendo a la izquierda - voltear sprite
                player2.setScale(-baseScale2, baseScale2);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                // Moviendo a la derecha - orientación normal
                player2.setScale(baseScale2, baseScale2);
            }
        } else {
            currentFrame2 = 0; // Volver al primer frame cuando está quieto
            player2.setTextureRect(sf::IntRect(0, 0, frameWidth2, frameHeight2));
        }

        animationClock.restart();
    }
}

sf::FloatRect Game::getPlayer1Bounds()
{
    return player1.getGlobalBounds();
}

sf::FloatRect Game::getPlayer2Bounds()
{
    return player2.getGlobalBounds();
}

void Game::resetGame()
{
    player1.setPosition(currentLevel.getPlayer1StartPos());
    player2.setPosition(currentLevel.getPlayer2StartPos());
    
    // Reiniciar todos los diamantes
    diamond1.setPosition(currentLevel.getDiamond1Pos());
    diamond2.setPosition(currentLevel.getDiamond2Pos());
    diamond3.setPosition(currentLevel.getDiamond3Pos());
    diamond4.setPosition(currentLevel.getDiamond4Pos());
    diamond1Visible = true;
    diamond2Visible = true;
    diamond3Visible = true;
    diamond4Visible = true;
    player1Diamonds = 0;
    player2Diamonds = 0;
    
    door1.setPosition(currentLevel.getDoor1Pos());
    door2.setPosition(currentLevel.getDoor2Pos());
    door1Hitbox = sf::FloatRect(currentLevel.getDoor1Pos().x + 25.0f, currentLevel.getDoor1Pos().y + 20.0f, 30.0f, 40.0f);
    door2Hitbox = sf::FloatRect(currentLevel.getDoor2Pos().x + 25.0f, currentLevel.getDoor2Pos().y + 20.0f, 30.0f, 40.0f);
    
    player1VelocityY = 0.0f;
    player2VelocityY = 0.0f;
    
    std::cout << "Juego reiniciado" << std::endl;
}

void Game::render()
{
    window.clear(sf::Color::Black);
    
    // Obtener tamaño de ventana
    sf::Vector2u windowSize = window.getSize();
    
    currentLevel.render(window);
    
    window.draw(door1);
    window.draw(door2);
    
    // Dibujar diamantes ANTES de los jugadores
    if (diamond1Visible) window.draw(diamond1);
    if (diamond2Visible) window.draw(diamond2);
    if (diamond3Visible) window.draw(diamond3);
    if (diamond4Visible) window.draw(diamond4);
    
    // Dibujar jugadores DESPUÉS (por encima de los diamantes)
    window.draw(player1);
    window.draw(player2);
    
    std::vector<sf::Vector2f> lavaPos = currentLevel.getLavaPositions();
    std::vector<sf::Vector2f> waterPos = currentLevel.getWaterPositions();
    std::vector<sf::Vector2f> mudPos = currentLevel.getMudPositions();
    
    for(const auto& pos : lavaPos) {
        lava.setPosition(pos);
        window.draw(lava);
    }
    for(const auto& pos : waterPos) {
        water.setPosition(pos);
        window.draw(water);
    }
    for(const auto& pos : mudPos) {
        mud.setPosition(pos);
        window.draw(mud);
    }
    
    // Actualizar posición del texto de coordenadas
    mouseCoordText.setPosition(10.0f, 10.0f);
    window.draw(mouseCoordText);
    
    // Actualizar posición del botón de pausa (siempre en esquina superior derecha)
    pauseButton.setPosition(windowSize.x - 60.0f, 10.0f);
    
    // Si hay textura, dibujar el sprite; si no, solo el botón
    if (pauseButtonTexture.getSize().x > 0) {
        pauseButtonSprite.setPosition(windowSize.x - 60.0f, 10.0f);
        window.draw(pauseButtonSprite);
    } else {
        // Fallback: dibujar botón con fondo y texto "| |"
        window.draw(pauseButton);
        sf::Text fallbackIcon;
        fallbackIcon.setFont(font);
        fallbackIcon.setString("| |");
        fallbackIcon.setCharacterSize(30);
        fallbackIcon.setFillColor(sf::Color::White);
        fallbackIcon.setPosition(windowSize.x - 48.0f, 18.0f);
        window.draw(fallbackIcon);
    }
    
    // Si está pausado, dibujar menú de pausa encima
    if (isPaused) {
        pauseMenu.render(window);
    }
    
    window.display();
}
