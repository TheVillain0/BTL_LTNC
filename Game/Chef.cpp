#include "Chef.h"
#include <algorithm>
#include <random>

Chef::Chef(const std::string& textureFile, const sf::Vector2f& position)
    : isWalkingOut(false), speed(100.0f), score(0)
{
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Chef::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Chef::requestIngredients(const std::vector<std::string>& availableIngredients)
{
    // Chọn 2 nguyên liệu ngẫu nhiên từ danh sách availableIngredients
    requestedIngredients.clear();
    receivedIngredients.clear();

    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<std::string> shuffledIngredients = availableIngredients;
    std::shuffle(shuffledIngredients.begin(), shuffledIngredients.end(), g);

    requestedIngredients.push_back(shuffledIngredients[0]);
    requestedIngredients.push_back(shuffledIngredients[1]);

    for (const auto& ingredient : requestedIngredients)
    {
        receivedIngredients[ingredient] = false;
    }

    std::cout << "Chef requests: ";
    for (const auto& ingredient : requestedIngredients)
    {
        std::cout << ingredient << " ";
    }
    std::cout << std::endl;
}

void Chef::receiveIngredient(Ingredient* ingredient)
{
    if (ingredient)
    {
        auto it = receivedIngredients.find(ingredient->getName());
        if (it != receivedIngredients.end())
        {
            it->second = true;
        }
    }
}

void Chef::update(float deltaTime)
{
    // Cập nhật logic cho Chef, ví dụ như di chuyển hoặc hành động khác
}

sf::Sprite& Chef::getSprite()
{
    return sprite;
}

bool Chef::hasAllIngredients() const
{
    return std::all_of(receivedIngredients.begin(), receivedIngredients.end(),
        [](const auto& pair) { return pair.second; });
}

void Chef::resetIngredients()
{
    requestedIngredients.clear();
    receivedIngredients.clear();
}

void Chef::setAvailableIngredients(const std::vector<std::string>& ingredients)
{
    availableIngredients = ingredients;
}

int Chef::getScore() const
{
    return score;
}

void Chef::addScore(int value)
{
    score += value;
}
