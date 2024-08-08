#include "Ingredient.h"

Ingredient::Ingredient(const std::string& textureFile, const sf::Vector2f& position, const std::string& name) : name(name)
{
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Ingredient::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::Sprite& Ingredient::getSprite()
{
    return sprite;
}

std::string Ingredient::getName() const
{
    return name;
}
