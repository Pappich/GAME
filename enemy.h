#pragma once
#include<SFML\Graphics.hpp>

class enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	//animation
	float speedMove;
	float A_x = 0;
	float A_y = 0;

	//function
	void initexture();
	void iniSprite();

public:
	enemy();
	virtual ~enemy();
	//fuction
	void Moveupdate(sf::RenderWindow* window);//animation
	void update(sf::RenderWindow* window);
	const sf::Vector2f& getPos() const;
	void render(sf::RenderTarget* target);
};


