#pragma once
#ifndef CHEF_H
#define CHEF_H

#include <SFML/Graphics.hpp>
#include <string>

class Chef
{
public:
    Chef(const std::string& textureFile, const sf::Vector2f& position);
    void render(sf::RenderWindow& window);
    void requestIngredient(const std::string& ingredient);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string currentRequest;
};

#endif

