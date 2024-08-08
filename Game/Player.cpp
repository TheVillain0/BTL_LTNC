#include "Player.h"

Player::Player() : speed(200.0f), heldIngredient(nullptr)
{
    defaultTexture.loadFromFile("assets/player.png");
    currentTexture = defaultTexture;
    sprite.setTexture(currentTexture);
    sprite.setPosition(400, 300);

    loadIngredientTextures();
}

void Player::handleInput(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        sprite.move(-speed * deltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        sprite.move(speed * deltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        sprite.move(0, -speed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        sprite.move(0, speed * deltaTime);
}

void Player::update(float deltaTime)
{
    if (heldIngredient)
    {
        heldIngredient->getSprite().setPosition(sprite.getPosition());
    }
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(sprite);
    if (heldIngredient)
    {
        window.draw(heldIngredient->getSprite());
    }
}

void Player::pickUpIngredient(Ingredient& ingredient)
{
    heldIngredient = &ingredient;
    auto textureIt = ingredientTextures.find(ingredient.getName());
    if (textureIt != ingredientTextures.end())
    {
        currentTexture = textureIt->second;
    }
    else
    {
        currentTexture = defaultTexture;
    }
    sprite.setTexture(currentTexture);
}

void Player::deliverIngredient()
{
    heldIngredient = nullptr;
    currentTexture = defaultTexture;
    sprite.setTexture(currentTexture);
}

sf::Sprite& Player::getSprite()
{
    return sprite;
}

Ingredient* Player::getHeldIngredient()
{
    return heldIngredient;
}

void Player::loadIngredientTextures()
{
    sf::Texture tomatoTexture;
    tomatoTexture.loadFromFile("assets/TomatoPlayer.png");
    ingredientTextures["Tomato"] = tomatoTexture;

    sf::Texture meatTexture;
    meatTexture.loadFromFile("assets/MeatPlayer.png");
    ingredientTextures["Meat"] = meatTexture;

    sf::Texture lettuceTexture;
    lettuceTexture.loadFromFile("assets/LettucePlayer.png");
    ingredientTextures["Lettuce"] = lettuceTexture;

    sf::Texture cheeseTexture;
    cheeseTexture.loadFromFile("assets/CheesePlayer.png");
    ingredientTextures["Cheese"] = cheeseTexture;
}
