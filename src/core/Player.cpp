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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) player.move({0, -Speed});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) player.move({-Speed, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move({0, Speed});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move({Speed, 0});
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
