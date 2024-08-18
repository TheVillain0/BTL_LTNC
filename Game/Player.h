#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Ingredient.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Chef.h"

class Chef;

class Player
{
public:
    Player();
    void handleInput(float deltaTime, std::vector<Ingredient*>& ingredients, Chef& chef);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void pickUpIngredient(Ingredient& ingredient);
    void deliverIngredient();
    sf::Sprite& getSprite();
    Ingredient* getHeldIngredient();
    sf::FloatRect getBounds() const;  
    void handleCollisionWithChef(Chef& chef);

private:
    sf::Texture defaultTexture;
    sf::Texture currentTexture;
    sf::Sprite sprite;
    float speed;
    Ingredient* heldIngredient;
    std::unordered_map<std::string, sf::Texture> ingredientTextures;

    void loadIngredientTextures();
    sf::Texture loadTextureWithMask(const std::string& filePath, const sf::Color& maskColor);
};

#endif
