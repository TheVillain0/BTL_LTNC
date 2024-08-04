#include "Player.h"

Player::Player() : speed(200.0f)
{
    texture.loadFromFile("assets/player.png");
    sprite.setTexture(texture);
    sprite.setPosition(400, 300);
}

void Player::handleInput()
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

void Player::update()
{

}

void Player::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}
