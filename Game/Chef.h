#ifndef CHEF_H
#define CHEF_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Ingredient.h"

class Chef
{
public:
    Chef(const std::string& textureFile, const sf::Vector2f& position);
    void render(sf::RenderWindow& window);
    void requestIngredient(const std::string& ingredient);
    void receiveIngredient(Ingredient* ingredient);
    void update(float deltaTime);
    sf::Sprite& getSprite();  

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string currentRequest;
    bool isWalkingOut;
    float speed;
    Ingredient* receivedIngredient;
};

#endif
