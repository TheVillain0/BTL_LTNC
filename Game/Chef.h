#ifndef CHEF_H
#define CHEF_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Ingredient.h"
#include <vector>
#include <unordered_map>
#include <iostream> 

class Chef
{
public:
    Chef(const std::string& textureFile, const sf::Vector2f& position);
    void render(sf::RenderWindow& window);
    void requestIngredients(const std::vector<std::string>& availableIngredients);
    void receiveIngredient(Ingredient* ingredient);
    void update(float deltaTime);
    sf::Sprite& getSprite();
    bool hasAllIngredients() const;
    void resetIngredients();
    void setAvailableIngredients(const std::vector<std::string>& ingredients);
    int getScore() const;  
    void addScore(int score);  

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<std::string> requestedIngredients;
    std::unordered_map<std::string, bool> receivedIngredients;
    bool isWalkingOut;
    float speed;
    int score;
    std::vector<std::string> availableIngredients;
};

#endif
