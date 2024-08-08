#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Chef.h"
#include "Ingredient.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cook Time");

    Player player;
    Chef chef("assets/chef.png", sf::Vector2f(200, 150));

    // Tạo các nguyên liệu
    Ingredient tomato("assets/tomato.png", sf::Vector2f(100, 100), "Tomato");
    Ingredient meat("assets/meat.png", sf::Vector2f(200, 100), "Meat");
    Ingredient lettuce("assets/lettuce.png", sf::Vector2f(300, 100), "Lettuce");
    Ingredient cheese("assets/cheese.png", sf::Vector2f(400, 100), "Cheese");

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
        float dt = deltaTime.asSeconds();

        player.handleInput(dt);
        player.update(dt);
        chef.update(dt);

        // Kiểm tra xem người chơi có lấy nguyên liệu không
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (player.getSprite().getGlobalBounds().intersects(tomato.getSprite().getGlobalBounds()))
            {
                player.pickUpIngredient(tomato);
            }
            else if (player.getSprite().getGlobalBounds().intersects(meat.getSprite().getGlobalBounds()))
            {
                player.pickUpIngredient(meat);
            }
            else if (player.getSprite().getGlobalBounds().intersects(lettuce.getSprite().getGlobalBounds()))
            {
                player.pickUpIngredient(lettuce);
            }
            else if (player.getSprite().getGlobalBounds().intersects(cheese.getSprite().getGlobalBounds()))
            {
                player.pickUpIngredient(cheese);
            }
        }

        // Kiểm tra xem người chơi có giao nguyên liệu cho đầu bếp không
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if (player.getSprite().getGlobalBounds().intersects(chef.getSprite().getGlobalBounds()) && player.getHeldIngredient())
            {
                chef.receiveIngredient(player.getHeldIngredient());
                player.deliverIngredient();
            }
        }

        window.clear();
        player.render(window);
        chef.render(window);
        tomato.render(window);
        meat.render(window);
        lettuce.render(window);
        cheese.render(window);
        window.display();
    }

    return 0;
}
