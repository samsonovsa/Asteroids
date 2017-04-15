#include <SFML\Graphics.hpp>
#include <time.h>
#include <list>
#include "Bullet.h"
#include "Entity.h"
#include "Animation.h"
#include "Asteroid.h"
#include "Player.h"

using namespace sf;


const int W=1280;
const int H = 1024;
float DEGTORAD=0.017453f;

bool isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}

int main()
{
	
	RenderWindow app(VideoMode(W, H), "SPACEWARS");
	app.setFramerateLimit(60);
	Texture t1, t2,t3,t4,t5,t6,t7,t8,t9;
	t1.loadFromFile("images/spaceship.png");
	t8.loadFromFile("images/alienspaceship1.png");
	t9.loadFromFile("images/alienspaceship2.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");

	t1.setSmooth(true);
	t2.setSmooth(true);
	t8.setSmooth(true);
	t9.setSmooth(true);

	Sprite background(t2);

	Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
	Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
	Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
	Animation sPlayer2(t8, 0, 0, 50, 50, 1, 0);
	Animation sPlayer_go(t1, 40, 40, 50, 50, 1, 0);
	Animation sPlayer_go2(t9, 0, 0, 50, 50, 1, 0);
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);


	std::list<Entity*> entities;

	for (int i = 0; i<2; i++)
	{
		Asteroid *a = new Asteroid();
		a->settings(sRock, rand() % W, rand() % H,  W, H, DEGTORAD, rand() % 360, 25);
		entities.push_back(a);
	}

	Player *p = new Player("player1");
	p->settings(sPlayer, 200, 200,  W, H, DEGTORAD, 0, 20);
	entities.push_back(p);

	Player *p2 = new Player("player2");
	p2->settings(sPlayer2, 300, 300, W, H, DEGTORAD, 180, 20);
	entities.push_back(p2);
	                                                 

	/////main loop/////
	while (app.isOpen()) 
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space)
				{
					Bullet *b2 = new Bullet();
					b2->settings(sBullet, p2->x+ cos(p2->angle*DEGTORAD) * 30, p2->y+ sin(p2->angle*DEGTORAD) * 30, W, H, DEGTORAD, p2->angle, 5);
					entities.push_back(b2);
				}
			if (event.key.code == Keyboard::Add)
			{
				Bullet *b = new Bullet();
				b->settings(sBullet, p->x + cos(p->angle*DEGTORAD) * 30, p->y + sin(p->angle*DEGTORAD) * 30, W, H, DEGTORAD, p->angle, 5);
				entities.push_back(b);
			}
		}

		
		if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3;
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 3;
		if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust = true;
		else p->thrust = false;

		if (Keyboard::isKeyPressed(Keyboard::D)) p2->angle += 3;
		if (Keyboard::isKeyPressed(Keyboard::A))  p2->angle -= 3;
		if (Keyboard::isKeyPressed(Keyboard::W)) p2->thrust = true;
		else p2->thrust = false;

		//Игровая механика
		for (auto a : entities)
			for (auto b : entities)
			{
				//Встреча выстрела и астероида
				if (a->name == "asteroid" && b->name == "bullet")
					if (isCollide(a, b))

					{
						a->life = false;
						b->life = false;
						//Создаем взрыв
						Entity *e = new Entity();
						e->settings(sExplosion, a->x, a->y,W, H, DEGTORAD );
						e->name = "explosion";
						entities.push_back(e);

						//Создается новый астероид
						for (int i = 0; i<2; i++)
						{
							if (a->R == 15) continue;
							Entity *e = new Asteroid();
							e->settings(sRock_small, a->x, a->y, W, H, DEGTORAD, rand() % 360, 15);
							entities.push_back(e);
						}

					}
				

				// Встреча астероида с игроком
				if (a->name == "player1" && b->name == "asteroid")
					if (isCollide(a, b))
					{
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y, W, H, DEGTORAD);
						e->name = "explosion";
						entities.push_back(e);
						p->countDeth++;
						p->settings(sPlayer, W / 2, H / 2, W, H, DEGTORAD, 0, 20);
						p->dx = 0; p->dy = 0;

					}

				// Встреча астероида с игроком
				if (a->name == "player2" && b->name == "asteroid")
					if (isCollide(a, b))
					{
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y, W, H, DEGTORAD);
						e->name = "explosion";
						entities.push_back(e);
						p2->countDeth++;
						p2->settings(sPlayer2, W / 2, H / 2, W, H, DEGTORAD, 0, 20);
						p2->dx = 0; p2->dy = 0;

					}
					

				// Встреча выстрела с игроком2
				if (a->name == "player2" && b->name == "bullet")
					if (isCollide(a, b))
					{
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y, W, H, DEGTORAD);
						e->name = "explosion";
						entities.push_back(e);
						p2->countDeth++;
						p2->settings(sPlayer2, W / 2, H / 2, W, H, DEGTORAD, 0, 20);
						p2->dx = 0; p2->dy = 0;

					}
				// Встреча выстрела с игроком1
				if (a->name == "player1" && b->name == "bullet")
					if (isCollide(a, b))
					{
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y, W, H, DEGTORAD);
						e->name = "explosion";
						entities.push_back(e);
						p->countDeth++;
						p->settings(sPlayer, W / 2, H / 2, W, H, DEGTORAD, 0, 20);
						p->dx = 0; p->dy = 0;

					}
			}


		if (p->thrust)  p->anim = sPlayer_go;
		else   p->anim = sPlayer;

		if (p2->thrust)  p2->anim = sPlayer_go2;
		else   p2->anim = sPlayer2;

		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;
		//создание новых астероидов
		if (rand() % 453 == 0)
		{
			Asteroid *a = new Asteroid();
			a->settings(sRock, rand() % W, rand() % H,  W, H, DEGTORAD, 25);
			entities.push_back(a);
		}

		//обновление всех элементов списка
		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();
			//если объект мертв, уничтожаем его
			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}

		
		//////draw//////
		app.draw(background);

		for (auto i : entities)
			i->draw(app);

		app.display();
		
	}
	return 0;
}

