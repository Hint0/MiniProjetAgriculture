#include "Player.hpp"

Player::Player(float setPV, float setSpeed, float setRadius, sf::Color setColor) :
	Character(setSpeed, setPV)
{
	player.setFillColor(sf::Color::Transparent);
	player.setRadius(setRadius);

	this->setSpriteTexture("res/Sprites/Player.png");
	this->setSpritePos(player.getPosition());
}

void Player::playerMovement(void)
{
	float Speed = Character::getSpeed();
	float up_down = 0;
	float left_right = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) up_down = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) left_right = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) up_down = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) left_right = 1;
	float mag = sqrt(left_right * left_right + up_down * up_down);
	if (mag != 0)
	{
		sf::Vector2f dir = { Speed * (left_right / mag), Speed * (up_down / mag) };
		player.move(dir);
		this->setSpritePos(player.getPosition());
	}

}

sf::CircleShape Player::getShape(void)
{
	return player;
}

sf::Vector2f Player::getPosition(void)
{
	return sf::Vector2f(player.getPosition().x + player.getRadius(),
		player.getPosition().y + player.getRadius());
}

void Player::setPosition(sf::Vector2f pos)
{
	player.setPosition(pos.x - player.getRadius(), pos.y - player.getRadius());
	this->setSpritePos(player.getPosition());
}

void Player::drawPV(sf::RenderWindow* window)
{
	for (int i = 1; i < getPV() + 1; i++)
	{
		sf::CircleShape pv(15.f);
		pv.setOutlineColor(sf::Color::Black);
		pv.setOutlineThickness(3);
		pv.setFillColor(sf::Color::Red);
		pv.setPosition(window->getSize().x - i * 37, 7);
		window->draw(pv);
	}
}
