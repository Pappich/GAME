#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2f size)
	{
		bullet.setSize(size);
		bullet.setFillColor(sf::Color{ 160, 96, 255 });
		bullet.setScale(.5f, 1.f);
	}

	void fire(int speed)
	{
		bullet.move(5, 0);
	}

	int getRight()
	{
		return bullet.getPosition().x + bullet.getSize().x;
	}
	int getLeft()
	{
		return bullet.getPosition().x;
	}
	int getTop()
	{
		return bullet.getPosition().y;
	}
	int getBottom()
	{
		return bullet.getPosition().y + bullet.getSize().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(bullet);
	}

	void setPos(sf::Vector2f newPos)
	{
		bullet.setPosition(newPos);
	}

private:
	sf::RectangleShape bullet;
};


