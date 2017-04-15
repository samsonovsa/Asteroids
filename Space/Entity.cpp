#include "Entity.h"
#include <string>

using namespace sf;

Entity::Entity()
{
	life = 1;
}


Entity::~Entity() {};


void Entity::settings(Animation &a, int X, int Y, int width, int high, float dec, float Angle, int radius)
{
	anim = a;
	x = X; y = Y;
	angle = Angle;
	R = radius;
	W = width;
	H = high;
	DEGTORAD = dec;
}

void Entity::update() {};

void Entity::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	anim.sprite.setRotation(angle + 90);
	app.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 0));
	circle.setPosition(x, y);
	circle.setOrigin(R, R);
	app.draw(circle);
}


