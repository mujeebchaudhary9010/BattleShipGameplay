#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"FourthWindow.h"
#include "PArt1.h"




int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1020), "Battle Ship Game");
    sf::Image logoImage;
    if (!logoImage.loadFromFile("assets/FirstLogo.png")) {
        return -1;
    }
    int i = 7;
    window.setIcon(logoImage.getSize().x, logoImage.getSize().y, logoImage.getPixelsPtr());
    sf::Music click;
if (!click.openFromFile("assets/Buttons/clickbutton.mp3")) {
    std::cerr << "Failed to load click sound!" << std::endl;
}
click.setVolume(1000);

sf::Music hover;
if (!hover.openFromFile("assets/hoversound.mp3")) {
    std::cerr << "Failed to load click sound!" << std::endl;
}
hover.setVolume(4);
hover.setPitch(1);
sf::Texture minilogo;
minilogo.loadFromFile("assets/secondlogo.png");
sf::Sprite smalllogo(minilogo);
smalllogo.setPosition(810, 10);
    sf::Music temp;
    temp.openFromFile("assets/gameintro.mp3");
    temp.setVolume(25);
    temp.setLoop(true);
    bool playershipsplaced = false;

    sf::Music temp2;
    temp2.openFromFile("assets/waterwaves.mp3");
    temp2.setVolume(40);
    temp2.setLoop(true);
    sf::Music missilesound;
    missilesound.openFromFile("assets/Missile/missileincoming.mp3");
    missilesound.setVolume(40);

    sf::Music explosionsound;
    explosionsound.openFromFile("assets/Explosions/explosion.mp3");
    explosionsound.setVolume(40);
    sf::Music waterexplosionsound;
    waterexplosionsound.openFromFile("assets/WaterSplash/watersplash.mp3");
    waterexplosionsound.setVolume(40);

    sf::Texture backgroundTexture1;
    backgroundTexture1.loadFromFile("assets/background.jpeg");
    sf::Sprite background2(backgroundTexture1);
    sf::Texture backgroundTexture4;
    backgroundTexture4.loadFromFile("assets/BlurBackground.png");
    sf::Sprite background4(backgroundTexture4);

    sf::Texture backgroundTexture2;
    backgroundTexture2.loadFromFile("assets/ThirdBackground.png");
    sf::Sprite background3(backgroundTexture2);
    sf::Texture backgroundTexture3;
    backgroundTexture3.loadFromFile("assets/gameOver.jpeg");
    sf::Sprite gameoverbackground(backgroundTexture3);
    temp.play();

    AppState currentState = LoadingScreen;
    sf::Font texts;
    texts.loadFromFile("simplenote.ttf");
    sf::Text text1;
    text1.setFont(texts);
    text1.setString("-    /45");      
    text1.setCharacterSize(30);           
    text1.setFillColor(sf::Color::Black); 
    text1.setPosition(1567.f, 5.f);
    sf::Text text2;
    text2.setFont(texts);
    text2.setString("-    /17");
    text2.setCharacterSize(30);
    text2.setFillColor(sf::Color::Black);
    text2.setPosition(1760.f, 5.f);
    sf::Text text3;
    text3.setFont(texts);
    text3.setCharacterSize(30);
    text3.setFillColor(sf::Color::Black);
    text3.setPosition(1775.f, 5.f);
    sf::Text text4;
    text4.setFont(texts);
    text4.setCharacterSize(30);
    text4.setFillColor(sf::Color::Black);
    text4.setPosition(1575.f, 5.f);
    int noofblocks = 0;
    int noofmissile = 45;
    std::vector<sf::Sprite*> ships;

    sf::Texture point1;
    point1.loadFromFile("assets/Missile/rmissile.png");
    sf::Sprite rmissile(point1);
    rmissile.setPosition(1500.0f, 5.0f);

    sf::Texture point2;
    point2.loadFromFile("assets/GridBlocks/rshiphit.png");
    sf::Sprite tshiphit(point2);
    tshiphit.setPosition(1703.0f, 8.0f);
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/SecondBackground.png");
    sf::Sprite background(backgroundTexture);
    sf::Texture GridBlocks;
    GridBlocks.loadFromFile("assets/GridBlocks/water.png");

    sf::Texture GridBlocks2;
    GridBlocks2.loadFromFile("assets/GridBlocks/blockhitted.png");
    sf::Sprite gblock(GridBlocks2);

    sf::Texture GridBlocks3;
    GridBlocks3.loadFromFile("assets/GridBlocks/shiphit.png");

    sf::Texture texture1, texture2, texture3, texture4, texture5;

    texture1.loadFromFile("assets/Ships/AircraftCarrier.png");
    sf::Sprite AircraftCarrier(texture1);
    AircraftCarrier.setPosition(150, 334);
    
    texture2.loadFromFile("assets/Ships/BattleShip.png");
    sf::Sprite BattleShip(texture2);
    BattleShip.setPosition(150, 448);

    texture3.loadFromFile("assets/Ships/Crusier.png");
    sf::Sprite Crusier(texture3);
    Crusier.setPosition(150, 562);

    texture4.loadFromFile("assets/Ships/Submarine.png");
    sf::Sprite Submarine(texture4);
    Submarine.setPosition(150, 676);

    texture5.loadFromFile("assets/Ships/Destroyer.png");
    sf::Sprite Destroyer(texture5);
    Destroyer.setPosition(154, 790);
    sf::Texture Tframe1, Tframe2;

    Tframe1.loadFromFile("assets/PointingTarget/frame1.png");
    Tframe2.loadFromFile("assets/PointingTarget/frame2.png");
    sf::Sprite Target(Tframe1);
    Target.setPosition(1224, 280);
    ships.push_back(&AircraftCarrier);
    ships.push_back(&BattleShip);
    ships.push_back(&Crusier);
    ships.push_back(&Submarine);
    ships.push_back(&Destroyer);

    Ships::ships = ships;
    ////////////////////////////
  

    int points = 100;
    sf::Vector2f startposition1(550, 280);
    sf::Vector2f startposition2(1224, 280);
    bool drag = false;
    bool a = false, b = false, c = false, d = false, e = false;

    bool statetemp = true;

    sf::Vector2f blockPosition;
    sf::Texture mtext;
    mtext.loadFromFile("assets/Missile/MissilePlayer.png");
    sf::Sprite missile(mtext);
    missile.setPosition(0, window.getSize().y / 2.f); 

    bool missileActive = false; // Missile movement state

    float deltaTime=0;
    sf::Clock clock;
    Missile missileobj;
    missileobj.sprite = missile; 
    missileobj.active = false;

    sf::Texture emtext;
    emtext.loadFromFile("assets/Missile/MissileEnemy.png");
    sf::Sprite emissile(emtext);
    emissile.setPosition(1810, 150);

    bool emissileActive = false; // Missile movement state
    Missile2 emissileobj;
    emissileobj.sprite = emissile;
    emissileobj.active = false;

    std::vector<std::vector<sf::Sprite>> gridSprites(10, std::vector<sf::Sprite>(10));

    std::vector<sf::Texture> textureFiles_1(4); 
    if (!textureFiles_1[0].loadFromFile("assets/WaterSplash/frame1.png") ||
        !textureFiles_1[1].loadFromFile("assets/WaterSplash/frame2.png") ||
        !textureFiles_1[2].loadFromFile("assets/WaterSplash/frame3.png") ||
        !textureFiles_1[3].loadFromFile("assets/WaterSplash/frame4.png")) {
        std::cerr << "Error loading impact textures!" << std::endl;
    }
   
    std::vector<sf::Texture> textureFiles_2(4);
    if (!textureFiles_2[0].loadFromFile("assets/Explosions/frame1.png") ||
        !textureFiles_2[1].loadFromFile("assets/Explosions/frame2.png") ||
        !textureFiles_2[2].loadFromFile("assets/Explosions/frame3.png") ||
        !textureFiles_2[3].loadFromFile("assets/Explosions/frame4.png")) {
        std::cerr << "Error loading impact textures!" << std::endl;
    }
    sf::Sprite splash;
   /* sf::Sprite explosion;
    explosion.setPosition(500, 500);*/
    float deltaTime2 = 2;
    std::vector<sf::Sprite> aiShips;
    aiShips.push_back(AircraftCarrier);
    aiShips.push_back(BattleShip);
    aiShips.push_back(Crusier);
    aiShips.push_back(Submarine);
    aiShips.push_back(Destroyer);
 

    // AI grid initialization (false means unoccupied)
    int gridSize = 10;
    std::vector<std::vector<bool>> shipPresence(gridSize, std::vector<bool>(gridSize, false));

    std::vector<std::vector<bool>> gridOccupied(gridSize, std::vector<bool>(gridSize, false));
    sf::Vector2f aiGridStart = { 1224, 280 };  // Starting position of AI's grid
    float blockSize = 65.0f;
    bool canPlace = true;

    aiPlaceShips(aiShips, aiGridStart, gridSize, blockSize, gridOccupied,shipPresence,noofblocks,canPlace);
   

    bool placerandom = true;
    std::vector<std::vector<bool>> hitBlocks(gridSize, std::vector<bool>(gridSize, false));
    std::vector<std::vector<bool>> pshipPresence(gridSize, std::vector<bool>(gridSize, false));

    std::vector<std::vector<bool>> EhitBlocks(gridSize, std::vector<bool>(gridSize, false));
    
    //////////////////////////////

    sf::Font font;
    if (!font.loadFromFile("FIGHTBACK.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Font font5;
    if (!font5.loadFromFile("TeachersStudent-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Font font2;
    if (!font2.loadFromFile("simplenote.ttf")) {
        std::cerr << "Error loading font2" << std::endl;
    }

    sf::Text texta;
    texta.setFont(font);
    texta.setString("BattleShip GamePlay");
    texta.setCharacterSize(150);
    texta.setFillColor(sf::Color::White);
    texta.setPosition(500.f, 150.f);

    sf::Text textb;
    textb.setFont(font);
    textb.setString("-Please Enter Your Name-");
    textb.setCharacterSize(80);
    textb.setFillColor(sf::Color::Red);
    textb.setPosition(650.f, 350.f);

    sf::Text textc;
    textc.setFont(font2);
    textc.setString("Name:");
    textc.setCharacterSize(60);
    textc.setFillColor(sf::Color::White);
    textc.setPosition(550.f, 550.f);

    sf::Text inputText("", font2, 60);
    inputText.setPosition(780, 550);
    inputText.setFillColor(sf::Color::Red);
    std::string userName = "Player 1";
    inputText.setString(userName);
    sf::Text cursorText("-", font, 50);
    cursorText.setPosition(780 + inputText.getLocalBounds().width, 580);
    cursorText.setFillColor(sf::Color::White);

    bool playershipsset = true;
    bool playerturn = false;
    bool enemyturn = false;
  
    std::ofstream fileOut("leaderboard.txt");
    std::ifstream fileIn("leaderboard.txt");

    while (window.isOpen())
    {
        

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {

                window.close();
            }
        }

        window.clear();
       
        switch (currentState) {
        case LoadingScreen: {
            displayLoadingScreen(window);
            currentState = SecondWindow;
            break;

        }
        case SecondWindow: {
            State2working(window, currentState, background2, click, hover, event,font);
            break;

        }
        case ThirdWindow: {
            temp2.pause();
            State3working(window, currentState, background3, click, hover, event,font);
            break;

        }
        case FourthWindow: {
            temp.pause();
           
            shipsfunction(window, currentState, click, hover, event, background, smalllogo, AircraftCarrier, BattleShip,
                Crusier, Submarine, Destroyer, GridBlocks, GridBlocks2, GridBlocks3, startposition1, startposition2,
                drag, a, b, c, d, e, Tframe1, Target, Tframe2, missile, blockPosition, deltaTime, clock, missileActive,
                mtext, missileobj,mtext,emissileobj, gridSprites, splash, textureFiles_1, textureFiles_2, deltaTime2, missilesound, explosionsound,
                waterexplosionsound, aiShips, gridSize, gridOccupied, placerandom, shipPresence, pshipPresence, points, rmissile, tshiphit, text1, text2, text3, text4,
                noofblocks, hitBlocks, canPlace, noofmissile, playershipsplaced,EhitBlocks,inputText,font2,playershipsset,playerturn,enemyturn,
                fileOut

          
            );
           /* currentState = TenthWindow;*/
            if ( noofmissile == 0)
            {
                currentState = SixthWindow;
                noofblocks = 0;
                noofmissile = 45;
            }
            if (noofblocks == 17)
            {
                currentState = EighthWindow;
                noofblocks = 0;
                noofmissile = 45;
            }
          
            break;

        }

        case FifthWindow: {
            temp.play();
            State4working(window, currentState, background4, click, hover, event, noofblocks, hitBlocks, shipPresence);
            break;

        }
        case SixthWindow: {

            gameOver(window, currentState, gameoverbackground, click, hover, event, noofblocks, hitBlocks, shipPresence);

            break;

        }
        case SeventhWindow: {
            playersname(window,event,userName,currentState,click,font,font2,texta,textb,textc,inputText,cursorText,background2);
            break;
        }
        case EighthWindow: {
            gamewon(window, event, userName, currentState, click, font, font2, texta,gameoverbackground);
            break;
        }
        case NinthWindow: {
            leaderboard(window,currentState, click,event,userName, points,background2,font);
            break;
        }
        case TenthWindow: {
            showStoryWindow(currentState, font5);
            break;
        }
             default: {
                break;
             }
              
        }
        if (statetemp == true && (currentState == FourthWindow || currentState == SixthWindow))
        {
            temp2.play();
            statetemp = false;
        }
      
        window.display();
    }
    return 0;
}