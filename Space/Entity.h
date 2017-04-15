#pragma once
#include <conio.h>
#include "Animation.h"
#include <SFML\Graphics.hpp>


class Entity
{
//protected:

public:
	int W, H;
	float DEGTORAD;
	float x, y, dx, dy, R, angle;
	
	bool life;
	std::string name;
	Animation anim;

	Entity();


	void settings(Animation &a, int X, int Y, int width, int high, float dec, float Angle = 0, int radius = 1);


	virtual void update();

	void draw(RenderWindow &app);

	virtual ~Entity();
};

