#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Bullet.h"
#include "Item.h"

using namespace std;
using namespace sf;

class objCollision {
public:
	double radius;
	double posX;
	double posY;

	bool collisionTest(Character c1, Bullet c2);
	bool collisionItem(Character c1, Item c2);
	double spawnCollision(Bullet c1, Bullet c2);
	~objCollision() {}
};