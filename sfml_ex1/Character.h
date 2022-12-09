#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class Character {
public:
	CircleShape triangle;

	double radius;
	double diameter;
	double posX;
	double posY;
	double velocity;
	Character() {
		posX = 0;
		posY = 0;
		radius = 10;
		diameter = radius * 2;
		velocity = 4;
		triangle.setPosition(posX, posY);
		triangle.setRadius(radius);
		triangle.setFillColor(Color(255, 212, 0));
		triangle.setPointCount(3);
	}

	Character(double x, double y, double rad) {
		posX = x;
		posY = y;
		radius = rad;
		diameter = radius * 2;
		velocity = 4;
		triangle.setPosition(posX, posY);
		triangle.setRadius(radius);
		triangle.setFillColor(Color(255, 212, 0));
		triangle.setPointCount(3);
	}

	void setVelocity(double vel) {
		velocity = vel;
	}

	inline double getVelocity() {
		return velocity;
	}

	void setRadius(double rad) {
		radius - rad;
		diameter = radius * 2;
		triangle.setRadius(radius);
	}

	void setPosition(double x, double y) {
		posX = x;
		posY = y;
		triangle.setPosition(x, y);
	}

	inline void move(double dx, double dy) {
		triangle.move(dx, dy);
	}

	inline CircleShape getCharacter() {
		return triangle;
	}

	~Character() {}
};