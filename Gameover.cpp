#include "Gameover.h"
Gameover::Gameover(float width, float height)
{
	if (!font.loadFromFile("puimek.ttf"))
	{
		//haddle error
	}
	gameover[0].setFont(font);
	gameover[0].setFillColor(sf::Color::Yellow);
	gameover[0].setString("SAVE SCORE");
	gameover[0].setCharacterSize(75);
	gameover[0].setOrigin(gameover[0].getLocalBounds().width / 2, gameover[0].getLocalBounds().height / 2);
	gameover[0].setPosition(sf::Vector2f(width / 1.25, height / (MAX_ITEMS + 1) * 0.80));

	gameover[1].setFont(font);
	gameover[1].setFillColor(sf::Color::White);
	gameover[1].setCharacterSize(75);
	gameover[1].setString("PLAY AGAIN");
	gameover[1].setOrigin(gameover[1].getLocalBounds().width / 2, gameover[1].getLocalBounds().height / 2);
	gameover[1].setPosition(sf::Vector2f(width / 1.25, height / (MAX_ITEMS + 1) * 1.75));

	gameover[2].setFont(font);
	gameover[2].setFillColor(sf::Color::White);
	gameover[2].setCharacterSize(75);
	gameover[2].setString("QUIT");
	gameover[2].setOrigin(gameover[2].getLocalBounds().width / 2, gameover[2].getLocalBounds().height / 2);
	gameover[2].setPosition(sf::Vector2f(width / 1.25, height / (MAX_ITEMS + 1) * 2.85));
}

Gameover::~Gameover()
{

}

void Gameover::draw(sf::RenderWindow& window)
{
	for (int i = 0;i < MAX_ITEMS;i++)
	{
		window.draw(gameover[i]);
	}
}

void Gameover::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		gameover[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		gameover[selectedItem].setFillColor(sf::Color::Yellow);
	}
}

void Gameover::MoveDown()
{
	if (selectedItem + 1 < MAX_ITEMS)
	{
		gameover[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		gameover[selectedItem].setFillColor(sf::Color::Yellow);
	}
}