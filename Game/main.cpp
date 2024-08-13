﻿#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Chef.h"
#include "Ingredient.h"
#include "Background.h"
#include <iostream>  // Thêm thư viện để hiển thị điểm số
#include <vector>    // Đảm bảo rằng thư viện vector đã được thêm vào

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cook Time");

    Background background("assets/floor.png", window.getSize());

    Player player;
    Chef chef("assets/chef.png", sf::Vector2f(250, 300));

    // Tạo các nguyên liệu
    Ingredient tomato("assets/TomatoDish.png", sf::Vector2f(100, 100), "Tomato");
    Ingredient meat("assets/MeatDish.png", sf::Vector2f(200, 100), "Meat");
    Ingredient lettuce("assets/LettuceDish.png", sf::Vector2f(300, 100), "Lettuce");
    Ingredient cheese("assets/CheeseDish.png", sf::Vector2f(400, 100), "Cheese");

    // Danh sách các nguyên liệu
    std::vector<Ingredient*> ingredients = { &tomato, &meat, &lettuce, &cheese };

    // Tên của các nguyên liệu
    std::vector<std::string> ingredientNames = { "Tomato", "Meat", "Lettuce", "Cheese" };

    chef.setAvailableIngredients(ingredientNames);
    chef.requestIngredients(ingredientNames);

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

        player.handleInput(dt, ingredients);
        player.update(dt);
        chef.update(dt);

        // Kiểm tra xem người chơi có lấy nguyên liệu không
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            for (auto& ingredient : ingredients)
            {
                if (player.getSprite().getGlobalBounds().intersects(ingredient->getSprite().getGlobalBounds()))
                {
                    player.pickUpIngredient(*ingredient);
                    break;
                }
            }
        }

        // Kiểm tra xem người chơi có giao nguyên liệu cho đầu bếp không
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if (player.getSprite().getGlobalBounds().intersects(chef.getSprite().getGlobalBounds()) && player.getHeldIngredient())
            {
                chef.receiveIngredient(player.getHeldIngredient());
                player.deliverIngredient();

                if (chef.hasAllIngredients())
                {
                    chef.resetIngredients();
                    chef.requestIngredients(ingredientNames);
                    chef.addScore(1);  // Cộng điểm
                    std::cout << "Score: " << chef.getScore() << std::endl;  // Hiển thị điểm số
                }
            }
        }

        window.clear();
        background.render(window);

        player.render(window);
        chef.render(window);
        for (auto& ingredient : ingredients)
        {
            ingredient->render(window);
        }
        window.display();
    }

    return 0;
}
