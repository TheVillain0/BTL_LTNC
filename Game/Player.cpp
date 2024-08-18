#include "Player.h"


Player::Player() : speed(200.0f), heldIngredient(nullptr)
{
    defaultTexture = loadTextureWithMask("assets/player.png", sf::Color::White);
    currentTexture = defaultTexture;
    sprite.setTexture(currentTexture);

    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    sprite.setPosition(400, 300);

    // Tải textures cho các nguyên liệu khác nhau
    loadIngredientTextures();
}

void Player::handleInput(float deltaTime, std::vector<Ingredient*>& ingredients, Chef& chef)
{
    sf::Vector2f movement(0.0f, 0.0f);

    // Xử lý di chuyển của người chơi
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
        // Tính toán góc quay của người chơi
        float angle = atan2(movement.y, movement.x) * 180 / 3.14159f;
        sprite.setRotation(angle + 90); // Điều chỉnh góc quay

        // Tính toán vị trí mới dự kiến
        sf::Vector2f newPosition = sprite.getPosition() + movement;

        // Kiểm tra va chạm tại vị trí mới
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        playerBounds.left = newPosition.x - sprite.getOrigin().x;
        playerBounds.top = newPosition.y - sprite.getOrigin().y;

        bool canMove = true;
        for (auto& ingredient : ingredients)
        {
            sf::FloatRect ingredientBounds = ingredient->getSprite().getGlobalBounds();
            if (playerBounds.intersects(ingredientBounds))
            {
                canMove = false; 
                break;
            }
        }

        // Kiểm tra va chạm với chef
        sf::FloatRect chefBounds = chef.getSprite().getGlobalBounds();
        if (playerBounds.intersects(chefBounds))
        {
          
            canMove = false;

            // Giao nguyên liệu cho chef nếu người chơi đang cầm một nguyên liệu
            if (heldIngredient != nullptr)
            {
                deliverIngredient();
               
            }
        }

        // Chỉ di chuyển nếu không có va chạm
        if (canMove)
        {
            sprite.move(movement);
        }
    }

    // Tính toán vị trí mới dự kiến
    sf::Vector2f newPosition = sprite.getPosition() + movement;

    // Xử lý va chạm và điều chỉnh di chuyển nếu cần
    sf::FloatRect futureBounds = sprite.getGlobalBounds();
    futureBounds.left += movement.x;
    futureBounds.top += movement.y;

    for (auto& ingredient : ingredients)
    {
        sf::FloatRect ingredientBounds = ingredient->getSprite().getGlobalBounds();

        if (futureBounds.intersects(ingredientBounds))
        {
            // Điều chỉnh di chuyển để ngăn chặn chồng lấp với nguyên liệu
            if (movement.x > 0 && futureBounds.left + futureBounds.width > ingredientBounds.left)
                movement.x = 0;
            if (movement.x < 0 && futureBounds.left < ingredientBounds.left + ingredientBounds.width)
                movement.x = 0;
            if (movement.y > 0 && futureBounds.top + futureBounds.height > ingredientBounds.top)
                movement.y = 0;
            if (movement.y < 0 && futureBounds.top < ingredientBounds.top + ingredientBounds.height)
                movement.y = 0;

            // Thay đổi mô hình của người chơi để khớp với nguyên liệu
            pickUpIngredient(*ingredient);
        }
    }

    // Kiểm tra va chạm với chef
    sf::FloatRect chefBounds = chef.getSprite().getGlobalBounds();
    if (futureBounds.intersects(chefBounds))
    {
        // Điều chỉnh di chuyển để ngăn chặn chồng lấp với chef
        if (movement.x > 0 && futureBounds.left + futureBounds.width > chefBounds.left)
            movement.x = 0;
        if (movement.x < 0 && futureBounds.left < chefBounds.left + chefBounds.width)
            movement.x = 0;
        if (movement.y > 0 && futureBounds.top + futureBounds.height > chefBounds.top)
            movement.y = 0;
        if (movement.y < 0 && futureBounds.top < chefBounds.top + chefBounds.height)
            movement.y = 0;

        // Giao nguyên liệu cho chef nếu người chơi đang cầm một nguyên liệu
        if (heldIngredient != nullptr)
        {
            deliverIngredient();
        }
    }

    // Di chuyển sprite của người chơi theo chuyển động đã điều chỉnh
    sprite.move(movement);
}










void Player::update(float deltaTime)
{
    
    sprite.setTexture(currentTexture);

    
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

    // Đổi model player dựa trên nguyên liệu tương ứng
    auto textureIt = ingredientTextures.find(ingredient.getName());
    if (textureIt != ingredientTextures.end())
    {
        currentTexture = textureIt->second;
    }
    else
    {
        currentTexture = defaultTexture;
    }

    // Đổi model mới
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

void Player::handleCollisionWithChef(Chef& chef)
{
    if (heldIngredient != nullptr)
    {
        chef.handleCollisionWithPlayer(*this); // Gọi phương thức handleCollisionWithPlayer của Chef để xử lý giao tiếp

        // Sau khi giao nguyên liệu, reset state của player
        deliverIngredient();
    }
}
