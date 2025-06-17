#include "Weapon.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

Weapon::Weapon(float fireRate, float bulletSpeed, sf::Color bulletColor, float bulletRadius) :
	fireRate{ fireRate },
	bulletSpeed{ bulletSpeed },
	bulletColor{ bulletColor },
	bulletRadius{ bulletRadius }
{
}

void Weapon::updateBullets(Bullet bullet)
{
	bullets.push_back(bullet);
}

std::vector<Bullet> Weapon::getBullets(void)
{
	return bullets;
}

void Weapon::updateBullet(sf::RenderWindow* window, std::vector<std::unique_ptr<Enemy>> &enemies,
                          Player player) {

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].getBullet().move(bullets[i].getVelocity());

		// Out of bounds
		if (bullets[i].getBullet().getPosition().x < 0 ||
			bullets[i].getBullet().getPosition().x > static_cast<float>(window->getSize().x) ||
			bullets[i].getBullet().getPosition().y < 0 ||
			bullets[i].getBullet().getPosition().y > static_cast<float>(window->getSize().y))
		{
			bullets.erase(bullets.begin() + i);
			continue;
		}
		else
		{
			// Not out of bounds... So collision
			for (size_t k = 0; k < enemies.size(); k++)
			{
				// Collision
				if (bullets[i].getBullet().getGlobalBounds().intersects(
					(enemies)[k]->getShape().getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
					enemies.erase(enemies.begin() + k);
					break;
				}
			}
			//Collision player ??
			//C'est du cut content actuellement, j'arrive pas à figurer comment faire fonctionner CORRECTEMENT ceci
/*
            if (bullets[i].getBullet().getGlobalBounds().intersects(
                    player.getShape().getGlobalBounds())) 
			{
                bullets.erase(bullets.begin() + i);
                player.getDamage(1);
                break;
            }
*/
		}
	}

}

float Weapon::getFireRate(void) { return fireRate; }

void Weapon::ClearBullets()
{
	bullets.clear();
}
