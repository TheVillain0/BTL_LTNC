#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <SFML/Graphics.hpp>
#include <string>

class Ingredient
{
public:
    Ingredient(const std::string& textureFile, const sf::Vector2f& position, const std::string& name);
    void render(sf::RenderWindow& window);
    sf::Sprite& getSprite();
    std::string getName() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;
};

#endif
