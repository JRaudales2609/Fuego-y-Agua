#include "../include/Level.hpp"
#include <iostream>

Level::Level(int levelNumber) : levelNumber(levelNumber) {
    loadLevel();
}

void Level::loadLevel() {
    // Cargar imagen de fondo decorativa
    std::string backgroundPath = "assets/imagenes/niveles/background.png";
    
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Advertencia: No se pudo cargar fondo decorativo, usando color sólido" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        
        // Escalar la imagen para que cubra toda la ventana (1200x800)
        sf::Vector2u textureSize = backgroundTexture.getSize();
        float scaleX = 1200.0f / textureSize.x;
        float scaleY = 800.0f / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    }
    
    // Cargar texturas de bloques
    if (!borderBlockTexture.loadFromFile("assets/imagenes/bloques/border_block.png")) {
        std::cerr << "Error: No se pudo cargar border_block.png" << std::endl;
    } else {
        std::cout << "Textura de bloque de borde (horizontal) cargada" << std::endl;
    }
    
    // Intentar cargar bloque vertical, si no existe usar el horizontal
    if (!borderBlockVerticalTexture.loadFromFile("assets/imagenes/bloques/border_block_vertical.png")) {
        std::cerr << "Advertencia: No se pudo cargar border_block_vertical.png, usando border_block.png" << std::endl;
        borderBlockVerticalTexture = borderBlockTexture; // Usar la horizontal como fallback
    } else {
        std::cout << "Textura de bloque de borde (vertical) cargada" << std::endl;
    }
    
    if (!platformBlockTexture.loadFromFile("assets/imagenes/bloques/platform_block.png")) {
        std::cerr << "Error: No se pudo cargar platform_block.png" << std::endl;
    } else {
        std::cout << "Textura de bloque de plataforma cargada" << std::endl;
    }
    
    // Configurar datos específicos del nivel
    switch(levelNumber) {
        case 1:
            setupLevel1();
            break;
        case 2:
            setupLevel2();
            break;
        case 3:
            setupLevel3();
            break;
        default:
            setupLevel1();
            break;
    }
}

void Level::changeLevel(int newLevelNumber) {
    levelNumber = newLevelNumber;
    // Recargar el nivel con el nuevo número
    switch(levelNumber) {
        case 1:
            setupLevel1();
            break;
        case 2:
            setupLevel2();
            break;
        case 3:
            setupLevel3();
            break;
        default:
            setupLevel1();
            break;
    }
    std::cout << "Cambiado a nivel " << levelNumber << std::endl;
}

void Level::setupLevel1() {
    // Limpiar todo
    blocks.clear();
    platforms.clear();
    lavaPositions.clear();
    waterPositions.clear();
    mudPositions.clear();
    
    // Crear solo bordes del nivel (paredes, suelo y techo)
    // Suelo (24 bloques de 50px = 1200px de ancho) - en Y=750
    for(int x = 0; x < 24; x++) {
        addBlock("border", x * blockSize, 750);
    }
    
    // Techo (24 bloques) - en Y=0
    for(int x = 0; x < 24; x++) {
        addBlock("border", x * blockSize, 0);
    }
    
    // Pared izquierda (16 bloques = 800px) - en X=0
    for(int y = 0; y < 16; y++) {
        addBlock("border_vertical", 0, y * blockSize);
    }
    
    // Pared derecha - en X=1150 (1200-50)
    for(int y = 0; y < 16; y++) {
        addBlock("border_vertical", 1150, y * blockSize);
    }
    
    // Posiciones iniciales de jugadores - esquina inferior izquierda
    player1Start = sf::Vector2f(75.0f, 710.0f);   // Fireboy
    player2Start = sf::Vector2f(125.0f, 710.0f);  // Watergirl
    
    // Posiciones de diamantes originales
    diamond1Pos = sf::Vector2f(350.0f, 654.0f);  // Diamante rojo (fuego) 1
    diamond2Pos = sf::Vector2f(695.0f, 654.0f);  // Diamante azul (agua) 1
    
    // Posiciones de diamantes adicionales (movidos a la izquierda y más separados)
    diamond3Pos = sf::Vector2f(165.0f, 450.0f);  // Diamante rojo (fuego) 2 - derecha
    diamond4Pos = sf::Vector2f(75.0f, 450.0f);   // Diamante azul (agua) 2 - izquierda
    
    // Posiciones de puertas
    door1Pos = sf::Vector2f(950.0f, 110.0f);
    door2Pos = sf::Vector2f(1050.0f, 110.0f);  // Puerta de agua (a la derecha)
    
    // Obstáculos del nivel 1
    lavaPositions.push_back(sf::Vector2f(380.0f, 760.0f));
    waterPositions.push_back(sf::Vector2f(725.0f, 760.0f));
    mudPositions.push_back(sf::Vector2f(550.0f, 510.0f));
    
    // Plataformas del nivel 1
    addBlock("platform", 1050, 625);
    addBlock("platform", 1100, 625);
    
    // Plataforma larga desde pared izquierda
    for(int x = 50; x <= 800; x += 50) {
        addBlock("platform", x, 500);
    }
    
    // Borde vertical - esquina inferior derecha en (341, 502), extendiéndose hasta Y=370
    for(int y = 356; y <= 456; y += 50) {
        addBlock("border_vertical", 291, y);
    }
    
    // Plataforma superior - desde pared izquierda hasta X=217
    for(int x = 50, y = 353; x <= 150; x += 50) {
        addBlock("platform", x, y);
    }
    
    // Plataforma media - desde X=198 hasta X=330
    addBlock("platform", 200, 220);
    addBlock("platform", 250, 220);
    addBlock("platform", 300, 220);
    
    // Plataforma pequeña - centro en (550, 220)
    addBlock("platform", 525, 235);
    
    // Plataforma superior derecha - desde aprox X=850 hasta pared derecha (X=1150)
    for(int x = 850; x <= 1100; x += 50) {
        addBlock("platform", x, 220);
    }
}

void Level::setupLevel2() {
    // Limpiar todo
    blocks.clear();
    platforms.clear();
    lavaPositions.clear();
    waterPositions.clear();
    mudPositions.clear();
    
    // Crear bordes del nivel
    for(int x = 0; x < 24; x++) {
        addBlock("border", x * blockSize, 750);
    }
    
    for(int x = 0; x < 24; x++) {
        addBlock("border", x * blockSize, 0);
    }
    
    for(int y = 0; y < 16; y++) {
        addBlock("border_vertical", 0, y * blockSize);
    }
    
    for(int y = 0; y < 16; y++) {
        addBlock("border_vertical", 1150, y * blockSize);
    }
    
    // Columna central
    for(int y = 50; y <= 390; y += 50) {
        addBlock("border_vertical", 575, y);
    }
    
    // Plataforma izquierda superior
    for(int x = 50; x <= 350; x += 50) {
        addBlock("platform", x, 200);
    }
    
    // Plataforma derecha superior
    for(int x = 850; x <= 1100; x += 50) {
        addBlock("platform", x, 195);
    }
    
    // Cuadrados pequeños
    addBlock("platform", 425, 435);
    addBlock("platform", 224, 373);
    addBlock("platform", 65, 591);
    addBlock("platform", 344, 678);
    addBlock("platform", 648, 546);
    addBlock("platform", 878, 449);
    addBlock("platform", 1087, 597);
    addBlock("platform", 625, 287);
    
    // Posiciones iniciales
    player1Start = sf::Vector2f(100.0f, 160.0f);
    player2Start = sf::Vector2f(150.0f, 160.0f);
    
    // Diamantes lado izquierdo
    diamond1Pos = sf::Vector2f(66.0f, 546.0f);   // Diamante fuego 1 - abajo izquierda
    diamond2Pos = sf::Vector2f(66.0f, 496.0f);   // Diamante agua 1 - arriba izquierda
    
    // Diamantes lado derecho
    diamond3Pos = sf::Vector2f(1086.0f, 554.0f); // Diamante fuego 2 - abajo derecha
    diamond4Pos = sf::Vector2f(1086.0f, 504.0f); // Diamante agua 2 - arriba derecha
    
    // Puertas
    door1Pos = sf::Vector2f(941.0f, 85.0f);
    door2Pos = sf::Vector2f(1041.0f, 85.0f);
    
    // Lodo verde - charcos principales
    for(int x = 100; x <= 1100; x += 150) {
        mudPositions.push_back(sf::Vector2f(static_cast<float>(x), 760.0f));
    }
    
    // Lodo verde - charcos intermedios
    mudPositions.push_back(sf::Vector2f(175.0f, 760.0f));
    mudPositions.push_back(sf::Vector2f(325.0f, 760.0f));
    mudPositions.push_back(sf::Vector2f(475.0f, 760.0f));
    mudPositions.push_back(sf::Vector2f(625.0f, 760.0f));
    mudPositions.push_back(sf::Vector2f(775.0f, 760.0f));
    mudPositions.push_back(sf::Vector2f(925.0f, 760.0f));
    mudPositions.push_back(sf::Vector2f(1100.0f, 760.0f));
    
    std::cout << "Nivel 2 completo cargado" << std::endl;
}

void Level::setupLevel3() {
    // Configurar nivel 3
    player1Start = sf::Vector2f(50.0f, 300.0f);
    player2Start = sf::Vector2f(1100.0f, 300.0f);
    
    diamond1Pos = sf::Vector2f(600.0f, 200.0f);
    diamond2Pos = sf::Vector2f(650.0f, 200.0f);
    
    door1Pos = sf::Vector2f(100.0f, 700.0f);
    door2Pos = sf::Vector2f(1000.0f, 700.0f);
    
    platforms.push_back(sf::FloatRect(0.0f, 750.0f, 1200.0f, 50.0f));
}

void Level::addBlock(const std::string& type, float x, float y, float rotation) {
    Block block;
    block.type = type;
    
    // Asignar textura según el tipo
    if (type == "border") {
        block.sprite.setTexture(borderBlockTexture);
    } else if (type == "border_vertical") {
        block.sprite.setTexture(borderBlockVerticalTexture);
    } else if (type == "platform") {
        block.sprite.setTexture(platformBlockTexture);
    }
    
    // Escalar sprite al tamaño del bloque (50x50)
    sf::Vector2u texSize = block.sprite.getTexture()->getSize();
    float scaleX = blockSize / texSize.x;
    float scaleY = blockSize / texSize.y;
    block.sprite.setScale(scaleX, scaleY);
    
    // Configurar posición del sprite (sin rotación)
    block.sprite.setPosition(x, y);
    
    // Crear hitbox del bloque (coincide exactamente con el sprite)
    block.hitbox = sf::FloatRect(x, y, blockSize, blockSize);
    
    // Añadir a la lista de bloques
    blocks.push_back(block);
    
    // También agregar a platforms para compatibilidad con colisiones existentes
    platforms.push_back(block.hitbox);
}

void Level::render(sf::RenderWindow& window) {
    // Dibujar fondo decorativo
    window.draw(backgroundSprite);
    
    // Dibujar todos los bloques
    for (const auto& block : blocks) {
        window.draw(block.sprite);
    }
}

// Getters
sf::Vector2f Level::getPlayer1StartPos() const { return player1Start; }
sf::Vector2f Level::getPlayer2StartPos() const { return player2Start; }
sf::Vector2f Level::getDiamond1Pos() const { return diamond1Pos; }
sf::Vector2f Level::getDiamond2Pos() const { return diamond2Pos; }
sf::Vector2f Level::getDiamond3Pos() const { return diamond3Pos; }
sf::Vector2f Level::getDiamond4Pos() const { return diamond4Pos; }
sf::Vector2f Level::getDoor1Pos() const { return door1Pos; }
sf::Vector2f Level::getDoor2Pos() const { return door2Pos; }

std::vector<sf::FloatRect> Level::getPlatforms() const { return platforms; }
std::vector<sf::ConvexShape> Level::getTriangles() const { return triangles; }
std::vector<sf::Vector2f> Level::getLavaPositions() const { return lavaPositions; }
std::vector<sf::Vector2f> Level::getWaterPositions() const { return waterPositions; }
std::vector<sf::Vector2f> Level::getMudPositions() const { return mudPositions; }
