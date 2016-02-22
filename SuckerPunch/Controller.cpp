#include "stdafx.h"
#include "Controller.h"


Controller::Controller(int contIndex)
{
	cIndex = contIndex;

	dPadDirection.x = sf::Joystick::getAxisPosition(cIndex, sf::Joystick::PovX);
	dPadDirection.y = sf::Joystick::getAxisPosition(cIndex, sf::Joystick::PovY);

	b0prev = false;
	b0curr = false;
	b1prev = false;
	b1curr = false;
	b2prev = false;
	b2curr = false;
	b3prev = false;
	b3curr = false;
	startPrev = false;
	startCurr = false;
	leftPrev = false;
	leftCurr = false;
	rightPrev = false;
	rightCurr = false;
	upPrev = false;
	upCurr = false;
	downPrev = false;
	downCurr = false;

}

void Controller::update()
{
	xAxis = sf::Joystick::getAxisPosition(cIndex, sf::Joystick::Axis::X);//Axis for analouge stick

	dPadDirection.x = sf::Joystick::getAxisPosition(cIndex, sf::Joystick::PovX); //Axis for the dpad
	dPadDirection.y = sf::Joystick::getAxisPosition(cIndex, sf::Joystick::PovY);

	b0prev = b0curr;
	b1prev = b1curr;
	b2prev = b2curr;
	b3prev = b3curr;
	startPrev = startCurr;

	leftPrev = leftCurr;
	rightPrev = rightCurr;
	upPrev = upCurr;
	downPrev = downCurr;

	b0curr = sf::Joystick::isButtonPressed(cIndex, 0);
	b1curr = sf::Joystick::isButtonPressed(cIndex, 1);
	b2curr = sf::Joystick::isButtonPressed(cIndex, 2);
	b3curr = sf::Joystick::isButtonPressed(cIndex, 3);
	startCurr = sf::Joystick::isButtonPressed(cIndex, 7);

	if (dPadDirection.x < -90)
		leftCurr = true;
	if (dPadDirection.x > 90)
		rightCurr = true;
	if (dPadDirection.y > 90)
		upCurr = true;
	if (dPadDirection.y < -90)
		downCurr = true;
}

bool Controller::b0Press()
{
	if (b0curr == true && b0prev == false) //If the button is pressed now, but was not previously pressed
		return true;  //All of this ensures you do not get accidental repeat key presses

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

bool Controller::startPress()
{
	if (startCurr == true && startPrev == false)
		return true;

	return false;
}

bool Controller::leftPress()
{
	if (leftCurr == true && leftPrev == false)
		return true;

	return false;
}
bool Controller::rightPress()
{
	if (rightCurr == true && rightPrev == false)
		return true;

	return false;
}
bool Controller::upPress()
{
	if (upCurr == true && upPrev == false)
		return true;

	return false;
}
bool Controller::downPress()
{
	if (downCurr == true && downPrev == false)
		return true;

	return false;
}

int Controller::getX()
{
	return xAxis;
}

