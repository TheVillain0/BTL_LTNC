#pragma once

#ifndef CHEF_H
#define CHEF_H

#include <SFML/Graphics.hpp>
#include "Ingredient.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <random>

class Player;

enum class ChefState {
    Initial,        // Ch?a nh?n nguy�n li?u
    FirstIngredient, // ?� nh?n m?t nguy�n li?u
    Complete        // ?� nh?n ?? hai nguy�n li?u
};

class Chef
{
public:
    Chef(const sf::Vector2f& position, const std::string& initialTexturePath);

    void handleCollisionWithPlayer(Player& player);
    void render(sf::RenderWindow& window);
    sf::Sprite& getSprite();

private:
    sf::Texture textureInitial;
    sf::Texture textureFirstIngredient;
    sf::Texture textureComplete;
    ChefState state;
    std::string firstIngredient;
    sf::Sprite sprite;
    std::vector<std::string> modelFiles;
    std::string selectRandomModel();

    // ???ng d?n model ?� ch?n
    std::string selectedModel;

    // Ph??ng th?c ?? c?p nh?t texture d?a tr�n model ?� ch?n
    void updateTexturesBasedOnModel();
};

#endif