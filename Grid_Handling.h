//#ifndef GRID_HANDLING_H
//#define GRID_HANDLING_H
#include <SFML/Graphics.hpp>
#include <vector>
#include<cmath>
#include<SFML/Audio.hpp>
struct Missile {
    sf::Sprite sprite;
    sf::Vector2f direction;
    bool active = false;
    sf::Vector2f target;
    int targetX = 0, targetY = 0;
};
void initializeMissile(const sf::RenderWindow& window, Missile& missileobj, const sf::Texture& texture, const sf::Vector2f& targetPosition, int targetX, int targetY, sf::Music& missilesound
) {
    missileobj.sprite.setTexture(texture);
    missileobj.sprite.setPosition(0, window.getSize().y / 2.f);

    sf::Vector2f startPos = missileobj.sprite.getPosition();
    sf::Vector2f direction = targetPosition - startPos;
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
        missileobj.direction = direction / magnitude;
    else
        missileobj.direction = sf::Vector2f(0.f, 0.f);

    float angle = std::atan2(missileobj.direction.y, missileobj.direction.x) * 180.f / 3.14159265f;
    missileobj.sprite.setRotation(angle);

    missileobj.active = true;
    missileobj.target = targetPosition;
    missileobj.targetX = targetX;
    missileobj.targetY = targetY;


}
void updateAndDrawMissile(
    sf::RenderWindow& window,
    Missile& missileobj,
    float deltaTime,
    std::vector<std::vector<sf::Sprite>>& gridSprites,
    sf::Texture& GridBlocks2,
    sf::Sprite& Target,
    sf::Sprite& splash,
    const std::vector<sf::Texture>& textureFiles_1,
    sf::Music& missilesound,
    sf::Music& explosionsound,
    sf::Music& waterexplosionsound



) {
    if (!missileobj.active)
        return;

    const float speed = 1100.f;
    sf::Vector2f movement = missileobj.direction * speed * deltaTime;
    missileobj.sprite.move(movement);

    sf::Vector2f currentPos = missileobj.sprite.getPosition();
    float distance = std::sqrt(std::pow(currentPos.x - missileobj.target.x, 2) + std::pow(currentPos.y - missileobj.target.y, 2));

    if (distance < 10.f) {
        missileobj.sprite.setPosition(missileobj.target.x, missileobj.target.y);
        missileobj.active = false;
        gridSprites[missileobj.targetX][missileobj.targetY].setTexture(GridBlocks2);
        gridSprites[missileobj.targetX][missileobj.targetY].setPosition(missileobj.sprite.getPosition());
        if (missilesound.getStatus() == sf::Sound::Playing) {
            missilesound.stop();
        }
    }
    else {
        // Start the music when the missile is launched
        if (missilesound.getStatus() != sf::Music::Playing) {
            missilesound.play();
        }
    }
    window.draw(missileobj.sprite);
}
//#endif