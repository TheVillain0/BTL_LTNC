#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Ingredient.h"
#include <unordered_map>
#include <string>

class Player
{
public:
    Player();
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void pickUpIngredient(Ingredient& ingredient);
    void deliverIngredient();
    sf::Sprite& getSprite();
    Ingredient* getHeldIngredient();  

private:
    sf::Texture defaultTexture;
    sf::Texture currentTexture;
    sf::Sprite sprite;
    float speed;
    Ingredient* heldIngredient;
    std::unordered_map<std::string, sf::Texture> ingredientTextures;

    void loadIngredientTextures();
};

#endif
