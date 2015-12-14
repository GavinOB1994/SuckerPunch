#pragma once

template <typename T> 
class HealthBar
{
private:
	T totalHealth;
public:
	const T MAXHEALTH = 5;

	HealthBar(T h = 5)
	{
		totalHealth = h;
	}

	void setHealth(T h)
	{
		totalHealth = h;
	}
	T getHealth()
	{
		return totalHealth;
	}
};

