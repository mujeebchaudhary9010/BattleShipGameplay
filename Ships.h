#include <SFML/Graphics.hpp>
#include<vector>
#include<iostream>

namespace Ships {
    std::vector<sf::Sprite*> ships;
}

static void menue(sf::RenderWindow& window, AppState& currentState,sf::Music& click, sf::Music& hover,sf::Event& event)
{

    static sf::Texture button1Normal, button1Hover;
    static bool isInitialized = false;
    if (!isInitialized) {
        if (!button1Normal.loadFromFile("assets/Buttons/ReturnMenue/ReturnButton.png") ||
            !button1Hover.loadFromFile("assets/Buttons/ReturnMenue/ReturnButtonOn.png"))
        {
            std::cerr << "Error loading button textures!" << std::endl;
            return;
        }
        isInitialized = true;
    }
    sf::Sprite menueB(button1Normal);
    menueB.setPosition(5.f, 5.f);
    handleButton(window, menueB, button1Normal, button1Hover, click,hover, event,[&]() {
        currentState = FifthWindow;
        });

    window.draw(menueB);


}

void snapToFirstT(sf::Sprite& ship,
    const sf::Vector2f& gridStartPosition,
    sf::Sprite& Submarine,
    sf::Sprite& Crusier
) {
    const int BLOCK_SIZE = 65;
    const int GRID_ROWS = 10;
    const int GRID_COLS = 10;
    const float GRID_WIDTH = GRID_COLS * BLOCK_SIZE;
    const float GRID_HEIGHT = GRID_ROWS * BLOCK_SIZE;
    sf::Vector2f position = ship.getPosition();

    int shipWidth = ship.getGlobalBounds().getSize().x;
    int shipHeight = ship.getGlobalBounds().getSize().y;
    int shipEndY = position.y + shipHeight;
    int shipEndX = position.x + shipWidth;


    for (int i = 0; i < Ships::ships.size(); i++) {
        auto currentShipRect = Ships::ships[i]->getGlobalBounds();

        if (currentShipRect.intersects(ship.getGlobalBounds()) && ship.getGlobalBounds() != currentShipRect) {
            ship.setRotation(0);
            if (ship.getPosition() == Submarine.getPosition())
                ship.setPosition(150, 676);
            else if (ship.getPosition() == Crusier.getPosition())
                ship.setPosition(150, 562);
            return;
        }
    }


    if (ship.getRotation() == 90) {
        if (position.x <= gridStartPosition.x || shipEndX > gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y || shipEndY >= gridStartPosition.y + GRID_HEIGHT ) {

            ship.setRotation(0);
            if (ship.getPosition() == Submarine.getPosition())
                ship.setPosition(150, 676);
            else if (ship.getPosition() == Crusier.getPosition())
                ship.setPosition(150, 562);
            return;
        }
    }

    if (ship.getRotation() == 0) {
        if (position.x < gridStartPosition.x || shipEndX > gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y || shipEndY >= gridStartPosition.y + GRID_HEIGHT) {
            ship.setRotation(0);
            
            if (ship.getPosition() == Submarine.getPosition())
                ship.setPosition(150, 676);
            else if (ship.getPosition() == Crusier.getPosition())
                ship.setPosition(150, 562);
            return;
        }
    }

   

   

    
}

void snapToFirstA(sf::Sprite& ship, const sf::Vector2f& gridStartPosition,sf::Sprite& AircraftCarrier) {
    const int BLOCK_SIZE = 65;
    const int GRID_ROWS = 10;
    const int GRID_COLS = 10;
    const float GRID_WIDTH = GRID_COLS * BLOCK_SIZE;
    const float GRID_HEIGHT = GRID_ROWS * BLOCK_SIZE;

    sf::Vector2f position = ship.getPosition();

    int shipWidth = ship.getGlobalBounds().getSize().x;
    int shipHeight = ship.getGlobalBounds().getSize().y;
    int shipEndY = position.y + shipHeight;
    int shipEndX = position.x + shipWidth;


    for (int i = 0; i < Ships::ships.size(); i++) {
        auto currentShipRect = Ships::ships[i]->getGlobalBounds();

        if (currentShipRect.intersects(ship.getGlobalBounds()) && ship.getGlobalBounds() != currentShipRect) {
            ship.setRotation(0);
            if (ship.getPosition() == AircraftCarrier.getPosition())
                ship.setPosition(150, 334);

            return;
        }
    }


    if (ship.getRotation() == 90) {
        if (position.x <= gridStartPosition.x || shipEndX > gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y || shipEndY >= gridStartPosition.y + GRID_HEIGHT ) {

            ship.setRotation(0);
            if (ship.getPosition() == AircraftCarrier.getPosition())
                ship.setPosition(150, 334);
            return;
        }
    }

    if (ship.getRotation() == 0) {
        if (position.x < gridStartPosition.x || shipEndX >= gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y || shipEndY >= gridStartPosition.y + GRID_HEIGHT) {
            ship.setRotation(0);
            if (ship.getPosition() == AircraftCarrier.getPosition())
                ship.setPosition(150, 334);
            return;
        }
    }



   
}
void snapToFirstB(sf::Sprite& ship, const sf::Vector2f& gridStartPosition,sf::Sprite&BattleShip) {
    const int BLOCK_SIZE = 65;
    const int GRID_ROWS = 10;
    const int GRID_COLS = 10;
    const float GRID_WIDTH = GRID_COLS * BLOCK_SIZE;
    const float GRID_HEIGHT = GRID_ROWS * BLOCK_SIZE;

    sf::Vector2f position = ship.getPosition();

    int shipWidth = ship.getGlobalBounds().getSize().x;
    int shipHeight = ship.getGlobalBounds().getSize().y;
    int shipEndY = position.y + shipHeight;
    int shipEndX = position.x + shipWidth;


    for (int i = 0; i < Ships::ships.size(); i++) {
        auto currentShipRect = Ships::ships[i]->getGlobalBounds();

        if (currentShipRect.intersects(ship.getGlobalBounds()) && ship.getGlobalBounds() != currentShipRect) {
            ship.setRotation(0);
            if (ship.getPosition() == BattleShip.getPosition())
                ship.setPosition(150, 448);
           
            return;
        }
    }


    if (ship.getRotation() == 90) {
        if (position.x <= gridStartPosition.x || shipEndX > gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y || shipEndY >= gridStartPosition.y + GRID_HEIGHT ) {

            ship.setRotation(0);
            if (ship.getPosition() == BattleShip.getPosition())
                ship.setPosition(150, 448);
            return;
        }
    }

    if (ship.getRotation() == 0) {
        if (position.x < gridStartPosition.x || shipEndX >= gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y || shipEndY >= gridStartPosition.y + GRID_HEIGHT) {
            ship.setRotation(0);
            if (ship.getPosition() == BattleShip.getPosition())
                ship.setPosition(150, 448);
            return;
        }
    }


    
}
void snapToFirstD(sf::Sprite& ship, const sf::Vector2f& gridStartPosition,sf::Sprite&Destroyer) {
    const int BLOCK_SIZE = 65;
    const int GRID_ROWS = 10;
    const int GRID_COLS = 10;
    const float GRID_WIDTH = GRID_COLS * BLOCK_SIZE;
    const float GRID_HEIGHT = GRID_ROWS * BLOCK_SIZE;
    
    sf::Vector2f position = ship.getPosition();

    int shipWidth = ship.getGlobalBounds().getSize().x;
    int shipHeight = ship.getGlobalBounds().getSize().y;
    int shipEndY = position.y + shipHeight;
    int shipEndX = position.x + shipWidth;


    for (int i = 0; i < Ships::ships.size(); i++) {
        auto currentShipRect = Ships::ships[i]->getGlobalBounds();

        if (currentShipRect.intersects(ship.getGlobalBounds()) && ship.getGlobalBounds() != currentShipRect) {
            ship.setRotation(0);
            if (ship.getPosition() == Destroyer.getPosition())
                ship.setPosition(150, 790);
            
            return;
        }
    }


    if (ship.getRotation() == 90) {
        if (position.x <= gridStartPosition.x || shipEndX > gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y || shipEndY >= gridStartPosition.y + GRID_HEIGHT ) {

            ship.setRotation(0);
            if (ship.getPosition() == Destroyer.getPosition())
                ship.setPosition(150, 790);
            return;
        }
    }

    if (ship.getRotation() == 0) {
        if (position.x < gridStartPosition.x || shipEndX >= gridStartPosition.x + GRID_WIDTH ||
            position.y < gridStartPosition.y ||shipEndY >= gridStartPosition.y + GRID_HEIGHT) {
            ship.setRotation(0);
            if (ship.getPosition() == Destroyer.getPosition())
                ship.setPosition(150, 790);
            return;
        }
    }


   
}
void snapToThreeBlocks(sf::Sprite& ship, const sf::Vector2f& gridStartPosition, std::vector<std::vector<bool>>& pshipPresence) {
    const int BLOCK_SIZE = 65;
    sf::Vector2f position = ship.getPosition();


    int col = static_cast<int>((position.x - gridStartPosition.x) / BLOCK_SIZE);
    int row = static_cast<int>((position.y - gridStartPosition.y) / BLOCK_SIZE);
    pshipPresence[row][col] = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            ship.setRotation(90);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        {
            ship.setRotation(0);
        }

    
    if (col >= 0 && col <= 7) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
    else if (row >= 0 && row <= 7) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
}
void snapToTwoBlocks(sf::Sprite& ship, const sf::Vector2f& gridStartPosition, std::vector<std::vector<bool>>& pshipPresence) {
    const int BLOCK_SIZE = 65;

    sf::Vector2f position = ship.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        ship.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    {
        ship.setRotation(0);
    }
    int col = static_cast<int>((position.x - gridStartPosition.x) / BLOCK_SIZE);
    int row = static_cast<int>((position.y - gridStartPosition.y) / BLOCK_SIZE);
    pshipPresence[row][col] = true;


    if (col >= 0 && col <= 8) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
    else if (row >= 0 && row <= 8) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
}
void snapToFourBlocks(sf::Sprite& ship, const sf::Vector2f& gridStartPosition, std::vector<std::vector<bool>>& pshipPresence) {
    const int BLOCK_SIZE = 65;
    sf::Vector2f position = ship.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        ship.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    {
        ship.setRotation(0);
    }
    int col = static_cast<int>((position.x - gridStartPosition.x) / BLOCK_SIZE);
    int row = static_cast<int>((position.y - gridStartPosition.y) / BLOCK_SIZE);

    pshipPresence[row][col] = true;

    if (col >= 0 && col <= 6) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
    else if (row >= 0 && row <= 6) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
}
void snapToFiveBlocks(sf::Sprite& ship, const sf::Vector2f& gridStartPosition, std::vector<std::vector<bool>>& pshipPresence) {
    const int BLOCK_SIZE = 65;
    sf::Vector2f position = ship.getPosition();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            ship.setRotation(90);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        {
            ship.setRotation(0);
        }

    int col = static_cast<int>((position.x - gridStartPosition.x) / BLOCK_SIZE);
    int row = static_cast<int>((position.y - gridStartPosition.y) / BLOCK_SIZE);
    pshipPresence[row][col] = true;

    if (col >= 0 && col <= 5) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
    else if (row >= 0 && row <= 5) {
        ship.setPosition(gridStartPosition.x + col * BLOCK_SIZE,
            gridStartPosition.y + row * BLOCK_SIZE);
    }
}








