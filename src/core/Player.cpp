#include "Player.hpp"

Player::Player(float setPV, float setSpeed, float setRadius, sf::Color setColor): 
    Character(setSpeed, setPV)
{
    player.setFillColor(setColor);
    player.setRadius(setRadius);
}

void Player::playerMovement(void)
{
    float Speed = Character::getSpeed();
    float up_down = 0;
    float left_right = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) up_down = -Speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) left_right = -Speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) up_down = Speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) left_right = Speed;
    float mag = sqrt(2);
    if (mag != 0) 
    {
      sf::Vector2f dir = {left_right / mag, up_down / mag};
      player.move(dir);
    }


}

sf::CircleShape Player::getShape(void)
{
    return player;
}

sf::Vector2f Player::getPosition(void) {
    return sf::Vector2f(player.getPosition().x + player.getRadius(),
                        player.getPosition().y + player.getRadius());
}

void Player::setPosition(sf::Vector2f pos)
{
	player.setPosition(pos.x - player.getRadius(), pos.y - player.getRadius());
}
/*
void Player::hitDetector(void)
{
    //Collision
    if (player.getGlobalBounds().intersects(
        (Bullet.getShape().getGlobalBounds())))
    {
          getDamage(1);
    }
}
*/