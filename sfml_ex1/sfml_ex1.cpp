#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <random>
#include <windows.h>
#include "Character.h"
#include "Bullet.h"
#include "Item.h"
#include "objCollision.h"

using namespace std;
using namespace sf;

int main() {
	int nX = 1200;
	int nY = 900;
	RenderWindow window(VideoMode(nX, nY), "Bullet Dodge");
	window.setFramerateLimit(120);

	random_device rd; // create random_device to receive seed value
	mt19937 gen(rd()); // reset random-number create engine via random_device
	uniform_int_distribution<int> dis_x(0, 1100); // create random_number (posX)
	uniform_int_distribution<int> dis_y(0, 800); // create random_number (posY)
	
	double characterRadius = 30;
	double bulletRadius = 20;
	double characterDiameter = characterRadius * 2;
	double bulletDiameter = bulletRadius * 2;
	double c_posX = 0;
	double c_posY = nY - characterDiameter;
	double b_posX = 0;
	double b_posY = nY - bulletDiameter;
	double i_posX = 0;
	double i_posY = nY - 25;
	
	bool collide = false; // check collision state
	bool getItem = false; // check if character getting an item
	bool itemCreated = false; // check if item is created
	bool isBulletCreated = false; // check if bullet is created

	Character Character1(c_posX + 580, c_posY - 450, characterRadius);
	objCollision collTest;

	vector<Bullet> bulletList;
	vector<Item> itemList;

	Item item1(dis_x(gen), dis_y(gen), 25);
	itemList.push_back(item1);

	for (int i = 0; i < 5; i++) { // initial bullets quantity = 5
		Bullet obj(dis_x(gen), dis_y(gen), bulletRadius);
		bulletList.push_back(obj);
	}

	for (int i = 0; i < 4; i++) { // check collision between bullets
		for (int j = i + 1; j < 5; j++) { 
			if (collTest.spawnCollision(bulletList[i], bulletList[j]) < 40) {
				while (collTest.spawnCollision(bulletList[i], bulletList[j]) < 40) {
					bulletList.erase(bulletList.begin() + i);
					Bullet newObj(dis_x(gen), dis_y(gen), bulletRadius);
					bulletList.push_back(newObj);
				}
			}
		}
	}

	Text timeText;
	Text bulletText;
	
	int t = 0;
	
	Font font;
	if (!font.loadFromFile("C:\\Users\\seungjun\\source\\repos\\sfml_ex1\\sfml_ex1\\arial.ttf")) {
		return 42; // Robust error handling!
	}

	timeText.setFont(font);
	timeText.setString(to_string(t) + " sec");
	timeText.setCharacterSize(50);
	timeText.setFillColor(Color::Yellow);
	timeText.setPosition(0, 0);

	bulletText.setFont(font);
	bulletText.setString("Bullets: " + to_string(5));
	bulletText.setCharacterSize(50);
	bulletText.setFillColor(Color::Yellow);
	bulletText.setPosition(0, 50);

	Clock timer;

	float currentTime = 0;

	// 여기서부터 게임 루프
	while (window.isOpen())
	{	
		// 이벤트 검사 및 처리
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

		// detect key stroke
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			Character1.move(0, -Character1.getVelocity());
			Character1.posY += -Character1.getVelocity();
			if (Character1.posY <= 0)
				Character1.setPosition(Character1.posX, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			Character1.move(0, Character1.getVelocity());
			Character1.posY += Character1.getVelocity();
			if (Character1.posY >= 850)
				Character1.setPosition(Character1.posX, 850);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			Character1.move(-Character1.getVelocity(), 0);
			Character1.posX += -Character1.getVelocity();
			if (Character1.posX <= 0) // set character position (0, y) when moving through the window
				Character1.setPosition(0, Character1.posY);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			Character1.move(Character1.getVelocity(), 0);
			Character1.posX += Character1.getVelocity();
			if (Character1.posX >= 1142)
				Character1.setPosition(1142, Character1.posY);
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) { // press Q to quit
			window.close();
		}
		
		for (int i = 0; i < bulletList.size(); i++) { // move bullets
			bulletList[i].posX += bulletList[i].getXVelocity();
			bulletList[i].posY += bulletList[i].getYVelocity();
			bulletList[i].move(bulletList[i].getXVelocity(), bulletList[i].getYVelocity());
		}

		for (int i = 0; i < bulletList.size(); i++) {
			if (bulletList[i].posY >= 850 || bulletList[i].posY <= 0) {
				bulletList[i].bulletYVelocity *= -1;
			}
			if (bulletList[i].posX >= 1142 || bulletList[i].posX <= 0) {
				bulletList[i].bulletXVelocity *= -1;
			}
		}

		float time = timer.getElapsedTime().asSeconds(); // check time
		
		timeText.setString(to_string(time) + " sec");
		bulletText.setString("Bullets: " + to_string(bulletList.size()));

		// 화면을 지운다. 
		window.clear();

		window.draw(Character1.getCharacter());

		for (int i = 0; i < bulletList.size(); i++) {
			window.draw(bulletList[i].getBullet());
		}
		
		window.draw(timeText);
		window.draw(bulletText);

		if ((int)time % 4 == 0 && (int)time != 0) { // create item every 4 seconds, duration is a second
			Item item1(dis_x(gen), dis_y(gen), 25);
			itemList.push_back(item1);
			itemCreated = true;
			window.draw(itemList[0].getItem());
		}
		else {
			itemList.clear();
			itemCreated = false;
		}

		if (collTest.collisionItem(Character1, item1) == true && itemCreated == true) { // when collide to item
			getItem = true;
			Character1.setVelocity(7);
			currentTime = time;
		}

		if ((int)time - (int)currentTime > 4) { // if time elapsed after getting an item
			Character1.setVelocity(4);
			currentTime = 0;
		}

		// display the screen
		window.display();

		// GAME OVER SITUATION
		for (int i = 0; i < bulletList.size(); i++) {
			if (collTest.collisionTest(Character1, bulletList[i]) == true && (int)time != 0) // when collide to bullets
				collide = true;
		}

		if ((int)time % 5 == 0) { // create one bullet at every 5 seconds
			if (isBulletCreated == true)
				continue;

			if ((int)time == 0)
				continue;
			else {
				Bullet obj(dis_x(gen), dis_y(gen), bulletRadius);
				bulletList.push_back(obj);
				isBulletCreated = true;
			}
		}
		else {
			isBulletCreated = false;
		}
		
		while (collide == true) { // when game is over
			Text endText;
			Text endText2;
			window.clear();

			endText.setFont(font);
			endText.setCharacterSize(50);
			endText.setFillColor(Color::Yellow);
			endText.setPosition(0, 0);
			timeText.setPosition(0, 50);

			endText2.setFont(font);
			endText2.setCharacterSize(50);
			endText2.setFillColor(Color::Yellow);
			endText2.setPosition(0, 100);

			endText.setString("Game Over!");
			endText2.setString("Press R to restart or Q to quit");

			window.draw(endText);
			window.draw(timeText);
			window.draw(endText2);
			window.display();

			if (Keyboard::isKeyPressed(Keyboard::R)) { // when restart
				timeText.setPosition(0, 0);
				Character1.setPosition(c_posX + 580, c_posY - 450);
				timer.restart();

				bulletList.clear(); // delete all bullets
				
				// create new bullets when restart the game
				for (int i = 0; i < 5; i++) { // initial bullets quantity = 5
					Bullet obj(dis_x(gen), dis_y(gen), bulletRadius);
					bulletList.push_back(obj);
				}

				for (int i = 0; i < 4; i++) {
					for (int j = i + 1; j < 5; j++) {
						if (collTest.spawnCollision(bulletList[i], bulletList[j]) == true) {
							bulletList.erase(bulletList.begin() + i);
							Bullet newObj(dis_x(gen), dis_y(gen), bulletRadius);
							bulletList.push_back(newObj);
						}
					}
				}

				Character1.setVelocity(4);
				currentTime = 0;

				collide = false;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Q)) { // when quit
				window.close();
			}
		}
	}
}

