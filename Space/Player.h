#pragma once
#include "Entity.h"
#include <string>

class Player : public Entity
{
public:
	bool thrust;
	int countDeth;

	Player();
	Player(std::string namePlayer);
	~Player();
	void update();

};
