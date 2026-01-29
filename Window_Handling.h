#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <functional>
#include<SFML/Window.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
enum AppState {
    LoadingScreen,
    SecondWindow,
    ThirdWindow,
    FourthWindow,
    FifthWindow,
    SixthWindow,
    SeventhWindow,
    EighthWindow,
    NinthWindow,
    TenthWindow
};
//bool isMouseOverText(const sf::Text& text, const sf::RenderWindow& window) {
//    sf::FloatRect bounds = text.getGlobalBounds();
//    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//    return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
//}

void displayLoadingScreen(sf::RenderWindow& window)
{

   sf::Texture logo;
    logo.loadFromFile("assets/FirstLogo.png");
    sf::Sprite  Log_o(logo);

    sf::Texture backgroundTexture1;
    backgroundTexture1.loadFromFile("assets/FirstBackground.jpeg");
    sf::Sprite background2(backgroundTexture1);

    Log_o.setPosition(590.f, 60.f);
    sf::RectangleShape progressBar(sf::Vector2f(400.f, 25.f));
    progressBar.setPosition(770.f, 850.f);
    progressBar.setFillColor(sf::Color::Green);

     sf::RectangleShape border(sf::Vector2f(400.f, 25.f));
     border.setPosition(770.f, 850.f);
     border.setFillColor(sf::Color::Transparent);
     border.setOutlineThickness(1.f);
     border.setOutlineColor(sf::Color::White);
     sf::Clock clock;
    float progress = 0.f;
    

    while (progress < 400.f) {
        progress += clock.restart().asSeconds() * 100.f;

        progressBar.setSize(sf::Vector2f(progress, 25.f));
      
        window.clear();
        window.draw(background2);
        window.draw(Log_o);
        window.draw(border);
        window.draw(progressBar);
        window.display();

    }
}
void handleButton(
    sf::RenderWindow& window,
    sf::Sprite& button,
    const sf::Texture& normalTexture,
    const sf::Texture& hoverTexture,
    sf::Music& click,
    sf::Music& hover,
    const sf::Event& event,
    std::function<void()> onClick)
{ 
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    if (button.getGlobalBounds().contains(mousePosF)) {
        button.setTexture(hoverTexture);       
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            click.play();
            onClick();
        }
    }
    else {    
        button.setTexture(normalTexture);
    }
}

void handleDoubleClickButton(
    sf::RenderWindow& window,
    sf::Sprite& button,
    const sf::Texture& normalTexture,
    const sf::Texture& hoverTexture,
    const sf::Event& event, sf::Music& click,
    std::function<void()> onSingleClick,
    std::function<void()> onDoubleClick)
{
    static sf::Clock doubleClickClock;   
    static bool firstClick = false;      
    static float doubleClickTime = 0.3f; 
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isMouseOverButton = button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (isMouseOverButton) {
        button.setTexture(hoverTexture);  

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (firstClick) {
              
                if (doubleClickClock.getElapsedTime().asSeconds() <= doubleClickTime) {
                    onDoubleClick();
                    click.play();
                    firstClick = false;
                }
                else {
                    
                    onSingleClick();
                    firstClick = false;
                }
            }
            else {
              
                firstClick = true;
                doubleClickClock.restart();
            }
        }
    }
    else {
       
        button.setTexture(normalTexture);
    }
}

bool isMouseOverText(const sf::Text& text, const sf::RenderWindow& window) {
    sf::FloatRect bounds = text.getGlobalBounds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

}

void State2working(sf::RenderWindow& window, AppState& currentState, sf::Sprite& background, sf::Music& click, sf::Music& hover, sf::Event& event ,sf::Font& font) {
  
    static sf::Texture button1Normal, button1Hover;
    static sf::Texture button2Normal, button2Hover;
    static sf::Texture button3Normal, button3Hover;
    static bool isInitialized = false;
    if (!isInitialized) {
        if (!button1Normal.loadFromFile("assets/Buttons/Play/Play.png") ||
            !button1Hover.loadFromFile("assets/Buttons/Play/PlayON.png") ||
            !button2Normal.loadFromFile("assets/Buttons/Guide/Guide.png") ||
            !button2Hover.loadFromFile("assets/Buttons/Guide/GuideOn.png") ||
            !button3Normal.loadFromFile("assets/Buttons/FirstExit/Exit.png") ||
            !button3Hover.loadFromFile("assets/Buttons/FirstExit/ExitOn.png")) {
            std::cerr << "Error loading button textures!" << std::endl;
            return ;
        }
        isInitialized = true;
    }
 
    sf::Sprite button1(button1Normal);
    sf::Sprite button2(button2Normal);
    sf::Sprite button3(button3Normal);
    button1.setPosition(500.f, 200.f); 
    button3.setPosition(1200.f, 205.f);
   
  
    handleButton(window, button1, button1Normal, button1Hover, click,hover, event, [&]() {
        currentState =  ThirdWindow; 
        });
  
    handleButton(window, button3, button3Normal, button3Hover, click, hover, event, [&]() {
        click.play();
        window.close();

        });
    sf::Text user;
    user.setFont(font);
    user.setString("   Leaderboard   ");
    user.setCharacterSize(80);
    user.setFillColor(sf::Color::White);
    user.setPosition(735.f, 320.f);
    sf::Text chere;
    chere.setFont(font);
    chere.setString("-Click Here-");
    chere.setCharacterSize(80);
    chere.setFillColor(sf::Color::White);
    chere.setPosition(800.f, 470.f);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(chere, window)) {
            click.play();
            currentState = NinthWindow;
            return;
        }
    }
    if (isMouseOverText(chere, window)) {
        chere.setFillColor(sf::Color::Red);
    }
    else if (isMouseOverText(user, window)) {
        user.setFillColor(sf::Color::Green);

    }
    else {
        chere.setFillColor(sf::Color::White);
        user.setFillColor(sf::Color::White);
    }
    window.draw(background);

    window.draw(button1);
     window.draw(button3);
     window.draw(chere);
     window.draw(user);
}


void State3working(sf::RenderWindow& window, AppState& currentState, sf::Sprite& background, sf::Music& click, sf::Music& hover, sf::Event& event,sf::Font& font ) {
    static bool isInitialized = false;

    static sf::Texture button1Normal, button1Hover;
 
    static sf::Texture button3Normal, button3Hover;

    if (!isInitialized) {
        if (!button1Normal.loadFromFile("assets/Buttons/Start/Start.png") ||
            !button1Hover.loadFromFile("assets/Buttons/Start/StartON.png") ||
           
            !button3Normal.loadFromFile("assets/Buttons/Back/Back.png") ||
            !button3Hover.loadFromFile("assets/Buttons/Back/BackOn.png")) {
            std::cerr << "Error loading button textures!" << std::endl;
            return; 
        }
        isInitialized = true;
    }

    sf::Sprite button1(button1Normal);
    sf::Sprite button3(button3Normal);

    button1.setPosition(350.f, 200.f); 
    button3.setPosition(1350.f, 205.f);

        handleButton(window,button1,button1Normal,button1Hover,click, hover, event, [&]() {
         
                currentState =TenthWindow;
            }
        );
        handleButton(window, button3, button3Normal, button3Hover, click, hover, event, [&]() {

            currentState = SecondWindow;
            });
        sf::Text user;
        user.setFont(font);
        user.setString("   Player\nRegistration   ");
        user.setCharacterSize(90);
        user.setFillColor(sf::Color::White);
        user.setPosition(820.f, 240.f);
        sf::Text chere;
        chere.setFont(font);
        chere.setString("-Click Here-");
        chere.setCharacterSize(80);
        chere.setFillColor(sf::Color::Blue);
        chere.setPosition(810.f, 610.f);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(chere, window)) {
                click.play();
                currentState = SeventhWindow;
                return;
            }
        }
        if (isMouseOverText(chere, window)) {
            chere.setFillColor(sf::Color::Red);
        }
        else {
            chere.setFillColor(sf::Color::Blue);
        }

       
        window.draw(background);
        window.draw(button1);
        window.draw(user);
        window.draw(chere);
        window.draw(button3);
    }


void State4working(sf::RenderWindow& window, AppState& currentState, sf::Sprite& background,
    sf::Music& click, sf::Music& hover, sf::Event& event, int& noofblocks,
    std::vector<std::vector<bool>>& hitBlocks, std::vector<std::vector<bool>>& shipPresence

) {
    static sf::Texture button1Normal, button1Hover;
    //static sf::Texture button2Normal, button2Hover;
    static sf::Texture button3Normal, button3Hover;
    static bool isInitialized = false;

   
    if (!isInitialized) {
        if (!button1Normal.loadFromFile("assets/Buttons/Resume/Resume.png") ||
            !button1Hover.loadFromFile("assets/Buttons/Resume/ResumeON.png") ||
           /* !button2Normal.loadFromFile("assets/Buttons/Restart/Restart.png") ||
            !button2Hover.loadFromFile("assets/Buttons/Restart/RestartOn.png") ||*/
            !button3Normal.loadFromFile("assets/Buttons/SecondExit/Exit.png") ||
            !button3Hover.loadFromFile("assets/Buttons/SecondExit/ExitOn.png")) {
            std::cerr << "Error loading button textures!" << std::endl;
            return;
        }
        isInitialized = true;
    }

    sf::Sprite button1(button1Normal);
    //sf::Sprite button2(button2Normal);
    sf::Sprite button3(button3Normal);

  
    button1.setPosition(840.f, 250.f);
    //button2.setPosition(840.f, 250.f);
    button3.setPosition(842.f, 550.f);

    
    window.draw(background);

   
    handleButton(window, button1, button1Normal, button1Hover, click, hover, event, [&]() {
        currentState = FourthWindow;  
        });

    
   /* handleButton(window, button2, button2Normal, button2Hover, click, hover, event, [&]() {
       
        currentState = ThirdWindow;  
        });*/

   
    handleButton(window, button3, button3Normal, button3Hover, click, hover, event, [&]() {
        currentState=ThirdWindow;  
        });

    // Draw buttons
    window.draw(button1);
    //window.draw(button2);
    window.draw(button3);
}

void gameOver(sf::RenderWindow& window, AppState& currentState, sf::Sprite& background,
    sf::Music& click, sf::Music& hover, sf::Event& event, int& noofblocks,
    std::vector<std::vector<bool>>& hitBlocks, std::vector<std::vector<bool>>& shipPresence

) {
    static sf::Texture button1Normal, button1Hover ;
    sf::Texture button;
    button.loadFromFile("assets/oexit.png");
  
    sf::Sprite exitbutton(button);
    exitbutton.setPosition(840.f, 700.f);
    sf::Font font;
    font.loadFromFile("FIGHTBACK.ttf");
    sf::Text texta;
    texta.setFont(font);
    
    texta.setString("Game Over");
    texta.setCharacterSize(300);
    texta.setFillColor(sf::Color::White);
    texta.setPosition(500.f, 100.f);

    sf::Text textb;
    textb.setFont(font);
    textb.setString("-Exit-");
    textb.setCharacterSize(60);
    textb.setFillColor(sf::Color::White);
    textb.setPosition(920.f, 738.f);

    window.draw(background);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(textb, window)) {           
            window.close(); 
        }
    }


if (isMouseOverText(textb, window)) {
    textb.setFillColor(sf::Color::Red);
}
else {
    textb.setFillColor(sf::Color::White);
}

    window.draw(exitbutton);

    window.draw(texta);

    window.draw(textb);

}
void playersname(sf::RenderWindow& window, sf::Event& event, std::string& userName, AppState& currentState, sf::Music& click, sf::Font& font,
    sf::Font& font2, sf::Text& texta, sf::Text& textb, sf::Text& textc, sf::Text& inputText, sf::Text& cursorText, sf::Sprite& background) {

    static sf::Clock cursorClock;
    static bool isCursorVisible = true; 
    static bool keyProcessed = false;   

    if (event.type == sf::Event::TextEntered && !keyProcessed) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8) { 
                if (!userName.empty()) {
                    userName.pop_back();
                }
            }
            else if (event.text.unicode == 13) {
              
                cursorText.setString("");
                return; 
            }
            else {
                userName += static_cast<char>(event.text.unicode);
            }

            keyProcessed = true; 
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        keyProcessed = false;
    }

  
    sf::Text textback;
    textback.setFont(font);
    textback.setString("-Back-");
    textback.setCharacterSize(70);
    textback.setFillColor(sf::Color::White);
    textback.setPosition(840.f, 810.f);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(textback, window)) {
            click.play();
            currentState = ThirdWindow; 
            return;
        }
    }

    if (isMouseOverText(textback, window)) {
        textback.setFillColor(sf::Color::Red);
    }
    else {
        textback.setFillColor(sf::Color::White);
    }
    inputText.setString(userName);
    cursorText.setPosition(780 + inputText.getLocalBounds().width, 580);

    if (cursorClock.getElapsedTime().asSeconds() > 0.5f) {
        cursorClock.restart();
        isCursorVisible = !isCursorVisible;
    }

    if (isCursorVisible) {
        cursorText.setString("-");
    }
    else {
        cursorText.setString("");
    }
    window.draw(background);
    window.draw(texta);
    window.draw(textb);
    window.draw(textc);
    window.draw(inputText);
    window.draw(cursorText);
    window.draw(textback);
}
void gamewon(sf::RenderWindow& window, sf::Event& event, std::string& userName, AppState& currentState, sf::Music& click, sf::Font& font,
    sf::Font& font2, sf::Text texta,  sf::Sprite& background) {

    static sf::Clock cursorClock;
    static bool isCursorVisible = true;
    static bool keyProcessed = false;
    texta.setString("You Have Won!");
    texta.setCharacterSize(180);
    texta.setPosition(600, 250);
    if (isMouseOverText(texta, window)) {
        texta.setFillColor(sf::Color::Blue);
    }
    else {
        texta.setFillColor(sf::Color::White);
    }
    sf::Text newgame;
    newgame.setFont(font);
    newgame.setString("-New Game-");
    newgame.setCharacterSize(90);
    newgame.setFillColor(sf::Color::White);
    newgame.setPosition(420.f, 665.f);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(newgame, window)) {
            click.play();
            currentState = SecondWindow;
            return;
        }
    }
    if (isMouseOverText(newgame, window)) {
        newgame.setFillColor(sf::Color::Red);
    }
    else {
        newgame.setFillColor(sf::Color::White);
    }
    sf::Text exit;
    exit.setFont(font);
    exit.setString("-Exit-");
    exit.setCharacterSize(90);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(1280.f, 665.f);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(exit, window)) {
            click.play();
            window.close();
            return;
        }
    }
    if (isMouseOverText(exit, window)) {
        exit.setFillColor(sf::Color::Red);
    }
    else {
        exit.setFillColor(sf::Color::White);
    }
   
    window.draw(background);
    window.draw(texta);
    window.draw(exit);
    window.draw(newgame);
}
void saveScore(const std::string& playerName, int& score
) {
    std::vector<std::pair<std::string, int>> scores;
    // Add the new score
    scores.push_back({ playerName, score });
    std::ofstream fileOut("leaderboard.txt");
    // Sort scores in descending order
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    // Write top scores back to the file
    for (const auto& entry : scores) {
        std::cout << "i am here to write data of the tops  data." << std::endl;

        fileOut << entry.first << " " << entry.second << "\n";
    }
    fileOut.close();
}

//void displayLeaderboard(sf::RenderWindow& window, std::ifstream& fileIn, sf::Font& font) {
//    std::vector<std::pair<std::string, int>> scores;
//    std::string name;
//    int score;
//    // Read scores from the file
//    while (fileIn >> name >> score) {
//        scores.push_back({ name, score });
//        std::cout << "i am here to enter data in file." << std::endl;
//
//    }
//    fileIn.close();
//
//    // Sort scores in descending order (if not already sorted)
//    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
//        return a.second > b.second;
//        });
//
//    // Display top 3 scores on the leaderboard
//    sf::Text leaderboardTitle;
//    leaderboardTitle.setFont(font);
//    leaderboardTitle.setString("Leaderboard");
//    leaderboardTitle.setCharacterSize(100);
//    leaderboardTitle.setFillColor(sf::Color::White);
//    leaderboardTitle.setPosition(400.f, 50.f);
//    window.draw(leaderboardTitle);
//
//    for (int i = 0; i < std::min(3, (int)scores.size()); ++i) {
//        sf::Text entry;
//        std::cout << "i am here to graw three positions." << std::endl;
//        entry.setFont(font);
//        // Assuming 'scores' is a vector of pairs: std::vector<std::pair<std::string, int>> scores
//        entry.setString(scores[i].first + " : " + std::to_string(scores[i].second));
//        entry.setCharacterSize(50);
//        entry.setFillColor(sf::Color::Red);
//        entry.setPosition(400.f, 200.f + i * 100);
//        window.draw(entry);
//    }
//}

bool leaderboardInitialized = false; // <- declare this globally or pass as reference
void displayLeaderboard(sf::RenderWindow& window, sf::Font& font, const std::string& filename = "leaderboard.txt") {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream fileIn(filename);
    std::string name;
    int score;

    // Read scores from the file
    while (fileIn >> name >> score) {
        scores.push_back({ name, score });
    }
    fileIn.close();

    // Sort scores in descending order
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    float startX = 400.f;
    float startY = 280.f;  // Starting vertical position
    float spacing = 80.f;  // Space between entries

    // Display up to top 10 entries
    int displayCount = std::min(10, (int)scores.size());

    for (int i = 0; i < displayCount; ++i) {
        sf::Text entry;
        entry.setFont(font);

        // Entry text: e.g., "1. Mujeeb : 120"
        entry.setString(std::to_string(i + 1) + ". " + scores[i].first + " : " + std::to_string(scores[i].second));

        if (i < 3) {
            // Top 3 highlighted
            entry.setCharacterSize(65);
            entry.setFillColor(sf::Color(173, 216, 230)); // Light Blue
        }
        else {
            entry.setCharacterSize(45);
            entry.setFillColor(sf::Color(144, 238, 144)); // Light Green
        }

        entry.setPosition(startX, startY + i * spacing);
        window.draw(entry);
    }
}
void updateLeaderboard(const std::string& playerName, int newScore, const std::string& filename = "leaderboard.txt") {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream fileIn(filename);
    std::string name;
    int score;

    // Read existing scores
    while (fileIn >> name >> score) {
        scores.emplace_back(name, score);
    }
    fileIn.close();

    // Check if player exists and update
    bool playerFound = false;
    for (auto& entry : scores) {
        if (entry.first == playerName) {
            playerFound = true;
            if (newScore > entry.second) {
                entry.second = newScore; // Update only if score is higher
            }
            break;
        }
    }

    if (!playerFound) {
        scores.emplace_back(playerName, newScore); // Add new entry
    }

    // Save back to file
    std::ofstream fileOut(filename);
    for (const auto& entry : scores) {
        fileOut << entry.first << " " << entry.second << "\n";
    }
}

void leaderboard(sf::RenderWindow& window, AppState& currentState, sf::Music& click, sf::Event& event,
    const std::string& inputText, int& points, sf::Sprite& background, sf::Font& font)
{
    // Run once to save score
    if (!leaderboardInitialized) {
        updateLeaderboard(inputText, points); // use improved function
        leaderboardInitialized = true;
    }

    sf::Text leaderboardHeader;
    leaderboardHeader.setFont(font);
    leaderboardHeader.setString("<-Leaderboard->");
    leaderboardHeader.setCharacterSize(150);
    leaderboardHeader.setFillColor(sf::Color::White);
    leaderboardHeader.setPosition(510.f, 100.f);

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("-Exit-");
    exitText.setCharacterSize(80);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(850.f, 738.f);

    // Handle Mouse Events
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverText(exitText, window)) {
            click.play();
            leaderboardInitialized = false; // reset flag for next time
            currentState = SecondWindow;
            return;
        }
    }

    if (isMouseOverText(exitText, window)) {
        exitText.setFillColor(sf::Color::Red);
    }
    else {
        exitText.setFillColor(sf::Color::White);
    }

    // Render
    window.draw(background);
    window.draw(leaderboardHeader);
    window.draw(exitText);
    displayLeaderboard(window, font);  // Now display from saved file
}
std::vector<std::string> battleComments = {
    "Captain: The enemy fleet has been spotted on the horizon.",
    "First Mate: Torpedoes locked. Awaiting your command.",
    "Captain: Brace for impact! They've returned fire!",
    "Radio: Reinforcements are on the way!",
    "First Mate: Direct hit! Enemy ship is sinking!"
};

int commentIndex = 0;
std::string displayedText = "";
float typeTimer = 0.f;
bool isTyping = true;
// Updated showStoryWindow with embedded typewriter sound per character
// Updated showStoryWindow with improved readability, slower typing, auto-close, and transparent background
// Updated showStoryWindow with rounded corners and draggable functionality
void showStoryWindow(AppState& currentState, sf::Font& font) {
    sf::RenderWindow storyWindow(sf::VideoMode(1000, 300), "", sf::Style::None);
    storyWindow.setFramerateLimit(60);

    std::vector<std::string> storyParts = {
        "Day 47 at sea. Supplies dwindling. Our resolve tested by endless waves...",
        "Radar: Unknown vessels inbound—bearing to the east. They're closing fast...",
        "Captain: All hands to battle stations! We prepare for annihilation...",
        "First Mate: Enemy destroyers in formation, armed and ready.",
        "Captain: Fire the warning shot—no turning back now.",
        "Boom! The air trembles as enemy shells find our hull. Brace for impact!",
        "Lieutenant: Torpedoes are locked and ready to deploy.",
        "Commander: Allied fleet is 10 minutes away. Hold your ground.",
        "Captain: This is our stand. For honor, for crew, for our ship!",
        "Explosion. The sea calms. We've survived—but at what cost?"
    };

    int storyIndex = 0;
    std::string displayedText = "";
    bool isTyping = true;
    const float typingSpeed = 0.05f;
    float typeTimer = 0.f;
    sf::Clock clock;

    sf::Vector2i dragOffset;
    bool dragging = false;

    sf::SoundBuffer typingBuf;
    typingBuf.loadFromFile("assets/sounds/typewriter_click.wav");
    sf::Sound typingSound(typingBuf);
    typingSound.setVolume(60);

    sf::Text storyText;
    storyText.setFont(font);
    storyText.setString("");
    storyText.setCharacterSize(28);
    storyText.setFillColor(sf::Color::White);
    storyText.setPosition(20.f, 50.f);

    sf::Text nextBtn;
    nextBtn.setFont(font);
    nextBtn.setString("Next");
    nextBtn.setCharacterSize(30);
    nextBtn.setFillColor(sf::Color::Green);
    nextBtn.setPosition(850.f, 250.f);

    sf::Text closeBtn;
    closeBtn.setFont(font);
    closeBtn.setString("X");
    closeBtn.setCharacterSize(30);
    closeBtn.setFillColor(sf::Color::Red);
    closeBtn.setPosition(960.f, 10.f);

    sf::RectangleShape backgroundBox(sf::Vector2f(1000, 300));
    backgroundBox.setFillColor(sf::Color(0, 0, 0, 128));
    backgroundBox.setOutlineColor(sf::Color::White);
    backgroundBox.setOutlineThickness(2);

    int fadeAlpha = 255;
    sf::RectangleShape fade(sf::Vector2f(1000, 300));
    fade.setFillColor(sf::Color(0, 0, 0, 255));

    while (storyWindow.isOpen()) {
        sf::Event e;
        while (storyWindow.pollEvent(e)) {
            if (e.type == sf::Event::Closed ||
                (e.type == sf::Event::MouseButtonPressed && closeBtn.getGlobalBounds().contains(storyWindow.mapPixelToCoords(sf::Mouse::getPosition(storyWindow))))) {
                storyWindow.close();
                currentState = FourthWindow;
            }

            if (e.type == sf::Event::MouseButtonPressed && nextBtn.getGlobalBounds().contains(storyWindow.mapPixelToCoords(sf::Mouse::getPosition(storyWindow)))) {
                if (storyIndex + 1 < (int)storyParts.size()) {
                    storyIndex++;
                    displayedText = "";
                    isTyping = true;
                    typeTimer = 0.f;
                }
                else {
                    storyWindow.close();
                    currentState = FourthWindow;
                }
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                dragging = true;
                dragOffset = storyWindow.getPosition() - sf::Mouse::getPosition();
            }
            else if (e.type == sf::Event::MouseButtonReleased) {
                dragging = false;
            }
        }

        if (dragging) {
            storyWindow.setPosition(sf::Mouse::getPosition() + dragOffset);
        }

        float dt = clock.restart().asSeconds();
        typeTimer += dt;
        if (isTyping) {
            if (displayedText.size() < storyParts[storyIndex].size() && typeTimer > typingSpeed) {
                displayedText += storyParts[storyIndex][displayedText.size()];
                typingSound.stop();
                typingSound.play();
                typeTimer = 0.f;
            }
            else if (displayedText.size() >= storyParts[storyIndex].size()) {
                isTyping = false;
                typingSound.stop();
            }
        }
        storyText.setString(displayedText);

        storyWindow.clear(sf::Color::Transparent);
        storyWindow.draw(backgroundBox);
        storyWindow.draw(storyText);
        storyWindow.draw(nextBtn);
        storyWindow.draw(closeBtn);

        if (fadeAlpha > 0) {
            fadeAlpha = std::max(0, fadeAlpha - 5);
            fade.setFillColor(sf::Color(0, 0, 0, fadeAlpha));
            storyWindow.draw(fade);
        }

        storyWindow.display();
    }
}
