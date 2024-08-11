#include "Player.h"

Player::Player() : speed(200.0f), heldIngredient(nullptr)
{
    defaultTexture = loadTextureWithMask("assets/player.png", sf::Color::White); // Màu trắng
    currentTexture = defaultTexture;
    sprite.setTexture(currentTexture);

    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    sprite.setPosition(400, 300);

    // Load textures for different ingredients
    loadIngredientTextures();
}

void Player::handleInput(float deltaTime, std::vector<Ingredient*>& ingredients)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y += speed * deltaTime;

    if (movement.x != 0.0f || movement.y != 0.0f)
    {
        float angle = atan2(movement.y, movement.x) * 180 / 3.14159f;
        sprite.setRotation(angle + 90); // Adjust rotation

        // Calculate potential new position
        sf::Vector2f newPosition = sprite.getPosition() + movement;

        // Check for collisions at the new position
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        playerBounds.left = newPosition.x - sprite.getOrigin().x;
        playerBounds.top = newPosition.y - sprite.getOrigin().y;

        bool canMove = true;
        for (auto& ingredient : ingredients)
        {
            sf::FloatRect ingredientBounds = ingredient->getSprite().getGlobalBounds();
            if (playerBounds.intersects(ingredientBounds))
            {
                canMove = false; // Prevent movement if collision occurs
                break;
            }
        }

        // Only move if no collision
        if (canMove)
        {
            sprite.move(movement);
        }
    }

    // Calculate potential new position
    sf::Vector2f newPosition = sprite.getPosition() + movement;

    // Handle collision and adjust movement if necessary
    sf::FloatRect futureBounds = sprite.getGlobalBounds();
    futureBounds.left += movement.x;
    futureBounds.top += movement.y;

    for (auto& ingredient : ingredients)
    {
        sf::FloatRect ingredientBounds = ingredient->getSprite().getGlobalBounds();

        if (futureBounds.intersects(ingredientBounds))
        {
            // Adjust movement to prevent overlap with ingredient
            if (movement.x > 0 && futureBounds.left + futureBounds.width > ingredientBounds.left)
                movement.x = 0;
            if (movement.x < 0 && futureBounds.left < ingredientBounds.left + ingredientBounds.width)
                movement.x = 0;
            if (movement.y > 0 && futureBounds.top + futureBounds.height > ingredientBounds.top)
                movement.y = 0;
            if (movement.y < 0 && futureBounds.top < ingredientBounds.top + ingredientBounds.height)
                movement.y = 0;

            // Change player model to match the ingredient
            pickUpIngredient(*ingredient);
        }
    }

    // Move the player sprite according to adjusted movement
    sprite.move(movement);
}









void Player::update(float deltaTime)
{
    // Ensure the player's sprite is up to date
    sprite.setTexture(currentTexture);

    // The held ingredient should not move; we just change the player's model
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

    // Change player model based on the ingredient's name
    auto textureIt = ingredientTextures.find(ingredient.getName());
    if (textureIt != ingredientTextures.end())
    {
        currentTexture = textureIt->second;
    }
    else
    {
        currentTexture = defaultTexture;
    }

    // Set the player's texture to the new model
    sprite.setTexture(currentTexture);

    // Ensure the ingredient stays in place (if needed, set the ingredient's position here)
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
    ingredientTextures["Tomato"] = loadTextureWithMask("assets/TomatoPlayer.png", sf::Color::White);
    ingredientTextures["Meat"] = loadTextureWithMask("assets/MeatPlayer.png", sf::Color::White);
    ingredientTextures["Lettuce"] = loadTextureWithMask("assets/LettucePlayer.png", sf::Color::White);
    ingredientTextures["Cheese"] = loadTextureWithMask("assets/CheesePlayer.png", sf::Color::White);
}

sf::Texture Player::loadTextureWithMask(const std::string& filePath, const sf::Color& maskColor)
{
    sf::Image image;
    if (!image.loadFromFile(filePath))
    {
        // Xử lý lỗi nếu không tải được ảnh
        throw std::runtime_error("Failed to load image from file: " + filePath);
    }
    image.createMaskFromColor(maskColor); // Tạo mask từ màu nền
    sf::Texture texture;
    texture.loadFromImage(image);
    return texture;
}

sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}
