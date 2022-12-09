#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Item {
public:
	CircleShape square;

	double posX;
	double posY;
	double radius;
	double diameter;

	Item() {
		posX = 0;
		posY = 0;
		radius = 25;
		diameter = radius * 2;
		square.setRadius(radius);
		square.setPosition(posX, posY);
		square.setFillColor(Color(255, 192, 203));
		square.setPointCount(4);
	}

	Item(double x, double y, double rad) {
		posX = x;
		posY = y;
		radius = rad;
		diameter = radius * 2;
		square.setRadius(radius);
		square.setPosition(posX, posY);
		square.setFillColor(Color(255, 192, 203));
		square.setPointCount(4);
	}

	void setPosition(double x, double y) {
		posX = x;
		posY = y;
		square.setPosition(x, y);
	}

	void setRadius(double rad) {
		radius - rad;
		diameter = radius * 2;
		square.setRadius(radius);
	}

	inline CircleShape getItem() {
		return square;
	}
};