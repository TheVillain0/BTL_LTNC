#include "Chef.h"


Chef::Chef(const sf::Vector2f& position, const std::string& initialTexturePath) : state(ChefState::Initial)
{
    // Danh sách chef
    modelFiles = {
        "assets/MeatLettuceChef.png",
        "assets/TomatoCheeseChef.png",
        "assets/LettuceTomatoChef.png",
        "assets/MeatTomatoChef.png",
        "assets/CheeseLettuceChef.png",
        "assets/CheeseMeatChef.png"
    };

    // Chọn ngẫu nhiên chef
    this->selectedModel = selectRandomModel();


    if (!textureInitial.loadFromFile(selectedModel))
        throw std::runtime_error("Failed to load initial texture" + selectedModel);

    // Cập nhật texture tương ứng cho các trạng thái
    updateTexturesBasedOnModel();

    sprite.setTexture(textureInitial);
    sprite.setPosition(position);
}

std::string Chef::selectRandomModel()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, modelFiles.size() - 1);

    
    return modelFiles[dis(gen)];
}

void Chef::updateTexturesBasedOnModel()
{
    if (selectedModel == "assets/MeatLettuceChef.png") {
        textureFirstIngredient.loadFromFile("assets/MMeatLettuceChef.png");
        textureComplete.loadFromFile("assets/CompMeatLettuceChef.png");
    }
    else if (selectedModel == "assets/TomatoCheeseChef.png") {
        textureFirstIngredient.loadFromFile("assets/TTomatoCheeseChef.png");
        textureComplete.loadFromFile("assets/CompTomatoCheeseChef.png");
    }
    else if (selectedModel == "assets/LettuceTomatoChef.png") {
        textureFirstIngredient.loadFromFile("assets/LLettuceTomatoChef.png");
        textureComplete.loadFromFile("assets/CompLettuceTomatoChef.png");
    }
    else if (selectedModel == "assets/MeatTomatoChef.png") {
        textureFirstIngredient.loadFromFile("assets/MMeatTomatoChef.png");
        textureComplete.loadFromFile("assets/CompMeatTomatoChef.png");
    }
    else if (selectedModel == "assets/CheeseLettuceChef.png") {
        textureFirstIngredient.loadFromFile("assets/CCheeseLettuceChef.png");
        textureComplete.loadFromFile("assets/CompCheeseLettuceChef.png");
    }
    else if (selectedModel == "assets/CheeseMeatChef.png") {
        textureFirstIngredient.loadFromFile("assets/MCheeseMeatChef.png");
        textureComplete.loadFromFile("assets/CompCheeseMeatChef.png");
    }
}

void Chef::handleCollisionWithPlayer(Player& player)
{
    Ingredient* heldIngredient = player.getHeldIngredient();

    if (heldIngredient != nullptr) {
        std::string ingredientName = heldIngredient->getName();

        std::cout << "Chef: " << selectedModel << " nhận nguyên liệu: " << ingredientName << std::endl;
        if (state == ChefState::Initial) {
            // Nếu đây là nguyên liệu đầu tiên
            firstIngredient = ingredientName;
            state = ChefState::FirstIngredient;

            std::cout << "Chef nhận nguyên liệu đầu tiên: " << firstIngredient << std::endl;

            // Cập nhật sprite với texture tương ứng
            if (firstIngredient == "Meat" && selectedModel == "assets/MeatLettuceChef.png") {
                sprite.setTexture(textureFirstIngredient); // MMeatLettuceChef.png
            }
            else if (firstIngredient == "Lettuce" && selectedModel == "assets/MeatLettuceChef.png") {
                sprite.setTexture(textureFirstIngredient); // LMeatLettuceChef.png
            }
            else if (firstIngredient == "Tomato" && selectedModel == "assets/TomatoCheeseChef.png") {
                sprite.setTexture(textureFirstIngredient); // MTomatoCheeseChef.png
            }
            else if (firstIngredient == "Cheese" && selectedModel == "assets/TomatoCheeseChef.png") {
                sprite.setTexture(textureFirstIngredient); // CTomatoCheeseChef.png
            }
            else if (firstIngredient == "Lettuce" && selectedModel == "assets/LettuceTomatoChef.png") {
                sprite.setTexture(textureFirstIngredient); // MLettuceTomatoChef.png
            }
            else if (firstIngredient == "Tomato" && selectedModel == "assets/LettuceTomatoChef.png") {
                sprite.setTexture(textureFirstIngredient); // TTomatoLettuceChef.png
            }
            else if (firstIngredient == "Meat" && selectedModel == "assets/MeatTomatoChef.png") {
                sprite.setTexture(textureFirstIngredient); // MMeatTomatoChef.png
            }
            else if (firstIngredient == "Tomato" && selectedModel == "assets/MeatTomatoChef.png") {
                sprite.setTexture(textureFirstIngredient); // TMeatTomatoChef.png
            }
            else if (firstIngredient == "Cheese" && selectedModel == "assets/CheeseLettuceChef.png") {
                sprite.setTexture(textureFirstIngredient); // MCheeseLettuceChef.png
            }
            else if (firstIngredient == "Lettuce" && selectedModel == "assets/CheeseLettuceChef.png") {
                sprite.setTexture(textureFirstIngredient); // LCheeseLettuceChef.png
            }
            else if (firstIngredient == "Cheese" && selectedModel == "assets/CheeseMeatChef.png") {
                sprite.setTexture(textureFirstIngredient); // MCheeseMeatChef.png
            }
            else if (firstIngredient == "Meat" && selectedModel == "assets/CheeseMeatChef.png") {
                sprite.setTexture(textureFirstIngredient); // MMeatCheeseChef.png
            }


        }
        else if (state == ChefState::FirstIngredient) {
            // Nếu đã nhận nguyên liệu đầu tiên, kiểm tra xem nguyên liệu thứ hai có khớp không
            if ((selectedModel == "assets/MeatLettuceChef.png" &&
                ((firstIngredient == "Meat" && ingredientName == "Lettuce") ||
                    (firstIngredient == "Lettuce" && ingredientName == "Meat")))) {
                sprite.setTexture(textureComplete);
            }
            else if ((selectedModel == "assets/TomatoCheeseChef.png" &&
                ((firstIngredient == "Tomato" && ingredientName == "Cheese") ||
                    (firstIngredient == "Cheese" && ingredientName == "Tomato")))) {
                sprite.setTexture(textureComplete);
            }
            else if ((selectedModel == "assets/LettuceTomatoChef.png" &&
                ((firstIngredient == "Lettuce" && ingredientName == "Tomato") ||
                    (firstIngredient == "Tomato" && ingredientName == "Lettuce")))) {
                sprite.setTexture(textureComplete);
            }
            else if ((selectedModel == "assets/MeatTomatoChef.png" &&
                ((firstIngredient == "Meat" && ingredientName == "Tomato") ||
                    (firstIngredient == "Tomato" && ingredientName == "Meat")))) {
                sprite.setTexture(textureComplete);
            }
            else if ((selectedModel == "assets/CheeseLettuceChef.png" &&
                ((firstIngredient == "Cheese" && ingredientName == "Lettuce") ||
                    (firstIngredient == "Lettuce" && ingredientName == "Cheese")))) {
                sprite.setTexture(textureComplete);
            }
            else if ((selectedModel == "assets/CheeseMeatChef.png" &&
                ((firstIngredient == "Cheese" && ingredientName == "Meat") ||
                    (firstIngredient == "Meat" && ingredientName == "Cheese")))) {
                sprite.setTexture(textureComplete);
            }

            state = ChefState::Complete;
        }

        // Giao nguyên liệu và reset Player
        player.deliverIngredient();
    }
}


void Chef::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::Sprite& Chef::getSprite()
{
    return sprite;
}
