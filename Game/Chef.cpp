#include "Chef.h"

Chef::Chef(const std::string& textureFile, const sf::Vector2f& position)
    : isWalkingOut(false), speed(100.0f), receivedIngredient(nullptr)
{
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Chef::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Chef::requestIngredient(const std::string& ingredient)
{
    currentRequest = ingredient;
    isWalkingOut = true; // Khi yêu cầu nguyên liệu, Chef sẽ đi ra
}

void Chef::receiveIngredient(Ingredient* ingredient)
{
    if (ingredient)
    {
        receivedIngredient = ingredient;
        isWalkingOut = false;
        // Thực hiện các hành động khác khi nhận được nguyên liệu
    }
}

void Chef::update(float deltaTime)
{
    if (isWalkingOut)
    {
        sprite.move(0, speed * deltaTime); // Di chuyển Chef xuống dưới
        if (sprite.getPosition().y > 600)  
        {
            isWalkingOut = false;
            sprite.setPosition(sprite.getPosition().x, -sprite.getGlobalBounds().height); // Reset vị trí để đi ra từ trên
        }
    }
}

sf::Sprite& Chef::getSprite()
{
    return sprite;
}
