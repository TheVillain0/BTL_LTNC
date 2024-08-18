#include "Background.h"

Background::Background(const std::string& textureFile, const sf::Vector2u& windowSize)
{
    if (!texture.loadFromFile(textureFile))
    {
        throw std::runtime_error("Failed to load texture from file: " + textureFile);
    }

    sprite.setTexture(texture);
    sf::Vector2u tileSize = texture.getSize();

    unsigned int tilesX = windowSize.x / tileSize.x + 1;
    unsigned int tilesY = windowSize.y / tileSize.y + 1;

    for (unsigned int x = 0; x < tilesX; ++x)
    {
        for (unsigned int y = 0; y < tilesY; ++y)
        {
            sf::Sprite tileSprite = sprite;
            tileSprite.setPosition(x * tileSize.x, y * tileSize.y);
            tiles.push_back(tileSprite);
        }
    }
}

void Background::render(sf::RenderWindow& window)
{
    for (const auto& tile : tiles)
    {
        window.draw(tile);
    }
}
