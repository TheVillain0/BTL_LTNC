#include "Ingredient.h"

Ingredient::Ingredient(const std::string& textureFile, const sf::Vector2f& position, const std::string& name) : name(name)
{
    texture = loadTextureWithMask(textureFile, sf::Color::White); 
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

sf::Texture Ingredient::loadTextureWithMask(const std::string& filePath, const sf::Color& maskColor)
{
    sf::Image image;
    if (!image.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load image from file: " + filePath);
    }
    image.createMaskFromColor(maskColor); // Tạo mask từ màu nền
    sf::Texture texture;
    texture.loadFromImage(image);
    return texture;
}
