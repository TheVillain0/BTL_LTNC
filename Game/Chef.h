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
    Initial,        // Chưa nhận nguyên liệu
    FirstIngredient, // Đã nhận một nguyên liệu
    Complete        // Đã nhận đủ hai nguyên liệu
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

    // Đường dẫn model đã chọn
    std::string selectedModel;

    // Phương thức để cập nhật texture dựa trên model đã chọn
    void updateTexturesBasedOnModel();
};

#endif