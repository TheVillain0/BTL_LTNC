#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background
{
public:
    Background(const std::string& textureFile, const sf::Vector2u& windowSize);
    void render(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::Sprite> tiles;
};

#endif

