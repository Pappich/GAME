#include "Sun.h"

void Sun::iniShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);

}

void Sun::initVariables()
{
	this->type = 0;
	this->point = 0;
}

Sun::Sun(float pos_x, float pos_y)
{
	this->initShape();
	this->initVariables();

	this->shape.setPosition(pos_x, pos_y);
}

Sun::~Sun()

