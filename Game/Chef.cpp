#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Chef.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kitchen Chaos");

    Player player;
    Chef chef("assets/chef.png", sf::Vector2f(200, 150));

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = clock.restart();

        player.handleInput();
        player.update();

        window.clear();
        player.render(window);
        chef.render(window);
        window.display();
    }

    return 0;
}
