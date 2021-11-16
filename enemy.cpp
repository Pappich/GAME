#include "enemy.h"

void enemy::initexture()
{
	//load
	this->texture.loadFromFile("enemy.PNG");
}

void enemy::iniSprite()
{
	this->sprite.setTexture(texture);
	//this->sprite.setTextureRect(sf::IntRect(0, 0, 50, 75));
	this->sprite.setPosition(400, 300);
}

enemy::enemy()
{
	this->initexture();
	this->iniSprite();
}

enemy::~enemy()
{

}

void enemy::Moveupdate(sf::RenderWindow* window)
{
	this->speedMove = 4.25;
	if (this->sprite.getPosition().x >= 300 && this->sprite.getPosition().x <= 400)
	{
		//left
		this->sprite.move(-2.f, 0.f);
		window->setFramerateLimit(this->speedMove);

		this->sprite.setTextureRect(sf::IntRect(this->A_x * 50, this->A_y * 1, 50, 75));

		this->A_x = A_x + 1;

		if (this->A_x * 50 >= 200)
		{
			this->A_x = 0;
		}
	}
	else if (this->sprite.getPosition().x <= 400 && this->sprite.getPosition().y >= 200)
	{
		//top
		this->sprite.move(0.f, -2.f);
		window->setFramerateLimit(this->speedMove);

		this->sprite.setTextureRect(sf::IntRect(this->A_x * 50, this->A_y * 3, 50, 75));
		this->A_x = A_x + 1;
		if (this->A_x * 50 >= 200)
		{
			this->A_x = 0;
		}
	}
	else
	{
		window->setFramerateLimit(this->speedMove);

		this->sprite.setTextureRect(sf::IntRect(this->A_x * 0, this->A_y * 0, 50, 75));
	}
}

void enemy::update(sf::RenderWindow* window)
{
	this->Moveupdate(window);
}

const sf::Vector2f& enemy::getPos() const
{
	return this->sprite.getPosition();
}

void enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}