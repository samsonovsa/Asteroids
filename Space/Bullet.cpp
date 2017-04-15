#include "Bullet.h"



Bullet::Bullet()
{
	name = "bullet";
}


Bullet::~Bullet()
{

}
void  Bullet::update()
{
	dx = cos(angle*DEGTORAD) * 10;
	dy = sin(angle*DEGTORAD) * 10;
  // angle+=rand()%6-3;
	x += dx;
	y += dy;

	if (x>W || x<0 || y>H || y<0) life = 0;
}

