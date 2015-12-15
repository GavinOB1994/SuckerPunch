#include "stdafx.h"
#include "Controller.h"


Controller::Controller(int contIndex)
{
	cIndex = contIndex;

	xAxis = 0;

	b0prev = false;
	b0curr = false;
	b1prev = false;
	b1curr = false;
	b2prev = false;
	b2curr = false;
	b3prev = false;
	b3curr = false;
}

void Controller::update()
{
	xAxis = sf::Joystick::getAxisPosition(cIndex, sf::Joystick::Axis::X);

	b0prev = b0curr;
	b1prev = b1curr;
	b2prev = b2curr;
	b3prev = b3curr;

	b0curr = sf::Joystick::isButtonPressed(cIndex, 0);
	b1curr = sf::Joystick::isButtonPressed(cIndex, 1);
	b2curr = sf::Joystick::isButtonPressed(cIndex, 2);
	b3curr = sf::Joystick::isButtonPressed(cIndex, 3);
}

bool Controller::b0Press()
{
	if (b0curr == true && b0prev == false)
		return true;

	return false;
}

bool Controller::b1Press()
{
	if (b1curr == true && b1prev == false)
		return true;

	return false;
}

bool Controller::b2Press()
{
	if (b2curr == true && b2prev == false)
		return true;

	return false;
}

bool Controller::b3Press()
{
	if (b3curr == true && b3prev == false)
		return true;

	return false;
}

int Controller::getX()
{
	return xAxis;
}

