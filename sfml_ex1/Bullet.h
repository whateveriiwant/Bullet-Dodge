#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Bullet {
public:
	CircleShape circle;

	double radius;
	double diameter;
	double posX;
	double posY;
	double bulletXVelocity;
	double bulletYVelocity;

	Bullet() {
		posX = 0;
		posY = 0;
		radius = 20;
		diameter = radius * 2;
		bulletXVelocity = 5;
		bulletYVelocity = 5;
		circle.setPosition(posX, posY);
		circle.setRadius(radius);
		circle.setFillColor(Color(255, 105, 180));
		circle.setPointCount(30);
	}

	Bullet(double x, double y, double rad) {
		posX = x;
		posY = y;
		radius = rad;
		diameter = radius * 2;
		bulletXVelocity = 5;
		bulletYVelocity = 5;
		circle.setPosition(posX, posY);
		circle.setRadius(radius);
		circle.setFillColor(Color(255, 105, 180));
		circle.setPointCount(30);
	}

	void setVelocity(double vel) {
		bulletXVelocity = vel;
		bulletYVelocity = vel;
	}

	inline double getXVelocity() {
		return bulletXVelocity;
	}

	inline double getYVelocity() {
		return bulletYVelocity;
	}

	void setRadius(double rad) {
		radius - rad;
		diameter = radius * 2;
		circle.setRadius(radius);
	}

	void setPosition(double x, double y) {
		posX = x;
		posY = y;
		circle.setPosition(x, y);
	}

	inline void move(double dx, double dy) {
		circle.move(dx, dy);
	}

	inline CircleShape getBullet() {
		return circle;
	}

	~Bullet() {}
};