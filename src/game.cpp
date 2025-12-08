#include <SFML/Graphics.hpp>

int main()
{
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fuego y Agua - 2 Jugadores");
    window.setFramerateLimit(60);

    // Crear jugadores (cubos)
    // Jugador 1 - Rojo (WASD)
    sf::RectangleShape player1(sf::Vector2f(50.0f, 50.0f));
    player1.setFillColor(sf::Color::Red);
    player1.setPosition(150.0f, 375.0f);

    // Jugador 2 - Azul (Flechas)
    sf::RectangleShape player2(sf::Vector2f(50.0f, 50.0f));
    player2.setFillColor(sf::Color::Blue);
    player2.setPosition(1000.0f, 375.0f);

    // Velocidad de movimiento
    float speed = 5.0f;

    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento Jugador 1 (WASD)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player1.move(0.0f, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player1.move(0.0f, speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player1.move(-speed, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player1.move(speed, 0.0f);

        // Movimiento Jugador 2 (Flechas)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player2.move(0.0f, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player2.move(0.0f, speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player2.move(-speed, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player2.move(speed, 0.0f);

        // Limitar los jugadores dentro de la pantalla
        // Jugador 1
        if (player1.getPosition().x < 0)
            player1.setPosition(0, player1.getPosition().y);
        if (player1.getPosition().x + 50 > 1200)
            player1.setPosition(1150, player1.getPosition().y);
        if (player1.getPosition().y < 0)
            player1.setPosition(player1.getPosition().x, 0);
        if (player1.getPosition().y + 50 > 800)
            player1.setPosition(player1.getPosition().x, 750);

        // Jugador 2
        if (player2.getPosition().x < 0)
            player2.setPosition(0, player2.getPosition().y);
        if (player2.getPosition().x + 50 > 1200)
            player2.setPosition(1150, player2.getPosition().y);
        if (player2.getPosition().y < 0)
            player2.setPosition(player2.getPosition().x, 0);
        if (player2.getPosition().y + 50 > 800)
            player2.setPosition(player2.getPosition().x, 750);

        // Dibujar
        window.clear(sf::Color::Black);
        window.draw(player1);
        window.draw(player2);
        window.display();
    }

    return 0;
}
