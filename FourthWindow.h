#include"Window_Handling.h"
#include"Ships.h"
#include"Ai.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>  
#include"Grid_Handling.h"
#include <ctime>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include<Windows.h>
#include<vector>
#include<sstream>

void handleMissileImpact(
    sf::RenderWindow& window,
    sf::Sprite& missile,
    std::vector<std::vector<sf::Sprite>>& gridSprites,
    std::vector<std::vector<bool>>& gridOccupied,
    std::vector<std::vector<bool>>& shipPresence,
    sf::Texture& GridBlocks2,
    sf::Texture& GridBlocks3,
    std::vector<sf::Texture>& textureFiles_2,
    std::vector<std::vector<bool>>& hitBlocks,
    sf::Music& explosionsound,
    sf::Music& waterexplosionsond,
    sf::Text& text3,
    sf::Text& text4,

    int& noofblocks,
    int& noofmissile,
    int& points,
    bool& enemyturn,
    bool&playerturn
) {
   
    for (size_t i = 0; i < gridSprites.size(); ++i) {
        for (size_t j = 0; j < gridSprites[i].size(); ++j) {
            
            if (missile.getGlobalBounds().intersects(gridSprites[i][j].getGlobalBounds())) {
               

                if (!hitBlocks[i][j]) {
                    noofmissile--;
                    hitBlocks[i][j] = true;
                    enemyturn = true;
                    playerturn = false;
                    if (shipPresence[i][j]) {
                        gridSprites[i][j].setTexture(GridBlocks3);
                        waterexplosionsond.pause();
                        explosionsound.play();
                        noofblocks++;
                    }
                    else {
                        gridSprites[i][j].setTexture(GridBlocks2);
                        explosionsound.pause();
                        waterexplosionsond.play();
                        points -= 5;

                    }

                    return;
                }
            }
        }
    }
}




void aiPlaceShips(
    std::vector<sf::Sprite>& aiShips,
    sf::Vector2f gridStart,
    int gridSize,
    float blockSize,
    std::vector<std::vector<bool>>& gridOccupied,
    std::vector<std::vector<bool>>& shipPresence,
    int& noofblocks,
    bool& canPlace
) {
    std::vector<int> shipSizes = { 5, 4, 3, 3, 2 };

    srand(static_cast<unsigned int>(time(0)));

   
    for (size_t shipIndex = 0; shipIndex < aiShips.size(); ++shipIndex) {
        bool placed = false;

        while (!placed) {
            int startX = rand() % gridSize;   
            int startY = rand() % gridSize;   
            bool horizontal = rand() % 2 == 0; 

            
            if (horizontal && (startX + shipSizes[shipIndex]) > gridSize) {
                startX = gridSize - shipSizes[shipIndex];
            }
            if (!horizontal && (startY + shipSizes[shipIndex]) > gridSize) {
                startY = gridSize - shipSizes[shipIndex];
            }

            canPlace = true; 
           
            for (int i = 0; i < shipSizes[shipIndex]; ++i) {
                int x = startX + (horizontal ? i : 0);
                int y = startY + (horizontal ? 0 : i);

                
                if (x >= gridSize || y >= gridSize || gridOccupied[x][y]) {
                    canPlace = false;
                    break;
                }
            }

           
            if (canPlace) {
                for (int i = 0; i < shipSizes[shipIndex]; ++i) {
                    int x = startX + (horizontal ? i : 0);
                    int y = startY + (horizontal ? 0 : i);

                    gridOccupied[x][y] = true;
                    shipPresence[x][y] = true;
                   
                }

                sf::Vector2f startPosition = gridStart + sf::Vector2f(startX * blockSize, startY * blockSize);
                aiShips[shipIndex].setPosition(startPosition.x, startPosition.y);

                if (!horizontal) {
                    aiShips[shipIndex].setPosition(startPosition.x+65, startPosition.y);

                    aiShips[shipIndex].setRotation(90);
                }

                placed = true;
            }
        }
    }
}


void shipsfunction(sf::RenderWindow& window,
    AppState& currentState,
    sf::Music& click,
    sf::Music& hover,
    sf::Event& event,
    sf::Sprite& background,
    sf::Sprite& smalllogo,

    sf::Sprite& AircraftCarrier,
    sf::Sprite& BattleShip,
    sf::Sprite& Crusier,
    sf::Sprite& Submarine,
    sf::Sprite& Destroyer,
    sf::Texture& GridBlocks,
    sf::Texture& GridBlocks2,
    sf::Texture& GridBlocks3,
    sf::Vector2f& startposition1,
    sf::Vector2f& startposition2,
    bool& drag, bool& a, bool& b, bool& c, bool& d, bool& e,
    sf::Texture& Tframe1,
    sf::Sprite& Target,

    sf::Texture& Tframe2,
    sf::Sprite& missile,
    sf::Vector2f& blockPosition,
    float& deltaTime,
    sf::Clock& clock,
    bool& missileActive,
    sf::Texture missileTexture,
    Missile& missileobj,
    sf::Texture emissileTexture,
    Missile2& emissileobj,
    std::vector<std::vector<sf::Sprite>>& gridSprites,
    sf::Sprite& splash,
    std::vector<sf::Texture>& textureFiles_1,
    std::vector<sf::Texture>& textureFiles_2,
    float& deltaTime2,
    sf::Music& missilesound,
    sf::Music& explosionsound,
    sf::Music& waterexplosionsound,
    std::vector<sf::Sprite>& aiShips,
    int& gridSize,
    std::vector<std::vector<bool>>& gridOccupied,
    bool& placerandom,
    std::vector<std::vector<bool>>& shipPresence,
    std::vector<std::vector<bool>>& pshipPresence,

    int& points,
    sf::Sprite& rmissile,
    sf::Sprite& tshiphit,
    sf::Text& text1,
    sf::Text& text2,
    sf::Text& text3,
    sf::Text& text4,
    int& noofblocks,
    std::vector<std::vector<bool>>& hitBlocks,
    bool& canPlace,
    int& noofmissile,
    bool& playershipsplaced,
    std::vector<std::vector<bool>>& EhitBlocks,
    sf::Text& inputText,
    sf::Font& font2,
    bool& playershipsset,
    bool& playerturn,
    bool& enemyturn,
    std::ofstream& fileOut

)
{
    std::vector<sf::Sprite> blocks;

    sf::Vector2f ship1originalposition(Submarine.getPosition());
    sf::Vector2f shiporiginalposition(Submarine.getPosition());

    sf::Vector2i dragOffset;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    const int GRID_ROWS = 10;
    const int GRID_COLS = 10;
    int grid[GRID_ROWS][GRID_COLS] = { 0 };
    bool useFrame1 = true;
    bool temp = false;


    sf::Texture enemissile;
    enemissile.loadFromFile("assets/Missile/MissileEnemy.png");
    sf::Sprite enemymissile;
    enemymissile.setTexture(enemissile);

    window.draw(background);
    

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            sf::Sprite Grid(GridBlocks);
            Grid.move((i * 65) + startposition1.x, (j * 65) + startposition1.y);
            blocks.push_back(Grid);
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            sf::Sprite Grid(GridBlocks);
            Grid.move((i * 65) + startposition2.x, (j * 65) + startposition2.y);
            blocks.push_back(Grid);
        }
    }
    for (int i = 0; i < blocks.size(); i++) {
        window.draw(blocks[i]);

    }

    if (playershipsset) {
        if (event.type == sf::Event::MouseButtonPressed) {


            if (event.mouseButton.button == sf::Mouse::Left) {
                if (Submarine.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {

                    drag = true;
                    a = true;
                    b = false;
                    c = false;
                    d = false;
                    e = false;
                    dragOffset = sf::Vector2i(event.mouseButton.x, event.mouseButton.y) -
                        sf::Vector2i(Submarine.getPosition());

                }
                else if (AircraftCarrier.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    drag = true;
                    b = true;
                    a = false;
                    c = false;
                    d = false;
                    e = false;
                    dragOffset = sf::Vector2i(event.mouseButton.x, event.mouseButton.y) -
                        sf::Vector2i(AircraftCarrier.getPosition());
                }
                else if (Crusier.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    drag = true;
                    d = true;
                    b = false;
                    e = false;
                    a = false;
                    c = false;
                    dragOffset = sf::Vector2i(event.mouseButton.x, event.mouseButton.y) -
                        sf::Vector2i(Crusier.getPosition());
                }
                else if (BattleShip.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    drag = true;
                    c = true;
                    d = false;
                    b = false;
                    e = false;
                    a = false;
                    dragOffset = sf::Vector2i(event.mouseButton.x, event.mouseButton.y) -
                        sf::Vector2i(BattleShip.getPosition());
                }
                else if (Destroyer.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    drag = true;
                    e = true;
                    c = false;
                    d = false;
                    b = false;
                    a = false;
                    dragOffset = sf::Vector2i(event.mouseButton.x, event.mouseButton.y) -
                        sf::Vector2i(Destroyer.getPosition());
                }
            }
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {


            if (event.mouseButton.button == sf::Mouse::Left) {
                drag = false;
            }
            if (a) {
                snapToThreeBlocks(Submarine, startposition1, pshipPresence);
                snapToFirstT(Submarine, startposition1, Submarine, Crusier);
            }

            if (d) {
                snapToThreeBlocks(Crusier, startposition1, pshipPresence);
                snapToFirstT(Crusier, startposition1, Submarine, Crusier);
            }
            if (b) {
                snapToFiveBlocks(AircraftCarrier, startposition1, pshipPresence);
                snapToFirstA(AircraftCarrier, startposition1, AircraftCarrier);
            }
            if (c) {
                snapToFourBlocks(BattleShip, startposition1, pshipPresence);
                snapToFirstB(BattleShip, startposition1, BattleShip);
            }
            if (e) {
                snapToTwoBlocks(Destroyer, startposition1, pshipPresence);
                snapToFirstD(Destroyer, startposition1, Destroyer);
            }
        }
        if (drag) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            if (a) {
                Submarine.setPosition(static_cast<float>(mousePosition.x - dragOffset.x),
                    static_cast<float>(mousePosition.y - dragOffset.y));
            }
            if (b) {
                AircraftCarrier.setPosition(static_cast<float>(mousePosition.x - dragOffset.x),
                    static_cast<float>(mousePosition.y - dragOffset.y));
            }
            if (c) {
                BattleShip.setPosition(static_cast<float>(mousePosition.x - dragOffset.x),
                    static_cast<float>(mousePosition.y - dragOffset.y));
            }
            if (d) {
                Crusier.setPosition(static_cast<float>(mousePosition.x - dragOffset.x),
                    static_cast<float>(mousePosition.y - dragOffset.y));
            }
            if (e) {
                Destroyer.setPosition(static_cast<float>(mousePosition.x - dragOffset.x),
                    static_cast<float>(mousePosition.y - dragOffset.y));
            }
        }

    }
    //std::this_thread::sleep_for(std::chrono::seconds(1));


    sf::RectangleShape border1(sf::Vector2f(170.f, 46.f));
    border1.setPosition(1500.f, 5.f);
    border1.setFillColor(sf::Color::Transparent);
    border1.setOutlineThickness(1.f);
    border1.setOutlineColor(sf::Color::Black);
    sf::RectangleShape border2(sf::Vector2f(170.f, 46.f));
    border2.setPosition(1695.f, 5.f);
    border2.setFillColor(sf::Color::Transparent);
    border2.setOutlineThickness(1.f);
    border2.setOutlineColor(sf::Color::Black);
    text3.setString(std::to_string(noofblocks));
    text4.setString(std::to_string(noofmissile));


   
    sf::Font font;
    font.loadFromFile("FIGHTBACK.ttf");
    sf::Text texta;
    texta.setFont(font);
    sf::Text textb;
    textb.setFont(font);
    textb.setString("-Start-");
    textb.setCharacterSize(60);
    textb.setFillColor(sf::Color::White);
    textb.setPosition(1125.f, 200.f);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(textb, window)) {
            click.play();
            playershipsset = false;
            playerturn = true;
        }
    }


    if (isMouseOverText(textb, window)) {
        textb.setFillColor(sf::Color::Red);
    }
    else {
        textb.setFillColor(sf::Color::White);
    }
    sf::Text compname;
    compname.setFont(font2);
    compname.setString("Computer");
    compname.setCharacterSize(40);
    compname.setFillColor(sf::Color::White);
    compname.setPosition(1700.f, 225.f);
    window.draw(textb);

    window.draw(smalllogo);
    window.draw(border1);
    window.draw(border2);

    window.draw(rmissile);
    //window.draw(emissileobj.sprite);
    window.draw(text4);
    window.draw(text1);
    window.draw(tshiphit);
    window.draw(text2);
    window.draw(text3);
    window.draw(AircraftCarrier);
    window.draw(BattleShip);
    window.draw(Crusier);
    window.draw(Submarine);
    window.draw(Destroyer);
    menue(window, currentState, click, hover, event);
   
    
    inputText.setCharacterSize(40);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(550, 225);
    window.draw(inputText);
    window.draw(compname);
    // 
    ///////////////////////
    float splashTimer = 0.0f;
    bool isSplashVisible = false;
      /*for (const auto& ship : aiShips) {
          window.draw(ship);
      }*/

   

      std::vector<sf::Sprite> playerShips;
      playerShips.push_back(AircraftCarrier);
      playerShips.push_back(BattleShip);
      playerShips.push_back(Crusier);
      playerShips.push_back(Submarine);
      playerShips.push_back(Destroyer);
      if (playerturn) {
          for (int i = 0; i < 10; i++) {
              for (int j = 0; j < 10; j++) {
                  sf::Sprite Grid(GridBlocks2);
                  Grid.setPosition((i * 65) + startposition2.x, (j * 65) + startposition2.y);


                  if (Grid.getGlobalBounds().contains(mousePosF)) {
                      Target.setPosition(Grid.getPosition());

                      if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                          blockPosition = Grid.getPosition();
                          deltaTime = clock.restart().asSeconds();
                         
                          initializeMissile(window, missileobj, missileTexture, blockPosition, i, j, missilesound);

                      }
                  }

                  window.draw(Target);
                  window.draw(gridSprites[i][j]);
              }
          }

         
        
          if (missileobj.active) {
              updateAndDrawMissile(window, missileobj, deltaTime, gridSprites, GridBlocks2, Target, splash, textureFiles_1, missilesound, explosionsound, waterexplosionsound);

              handleMissileImpact(window, missileobj.sprite, gridSprites, gridOccupied, shipPresence, GridBlocks2, GridBlocks3, textureFiles_2, hitBlocks, explosionsound,
                  waterexplosionsound, text3, text4, noofblocks, noofmissile,points,enemyturn,playerturn);
             
          }
      }

    
      if (enemyturn) {
          handleAI(
              window, gridSprites, gridOccupied, pshipPresence, EhitBlocks,
              emissileobj, missilesound, explosionsound, waterexplosionsound,
              GridBlocks2, GridBlocks3, emissileTexture, splash,Target, clock,
              noofblocks, noofmissile, enemyturn, playerturn, fileOut,startposition2
          );

        
      }
    
       
    

}