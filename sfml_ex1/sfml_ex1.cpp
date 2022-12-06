#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <random>
#include <windows.h>

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

	double getVelocity() {
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

	void move(double dx, double dy) {
		triangle.move(dx, dy);
	}

	CircleShape getCharacter() {
		return triangle;
	}

	~Character() {}
};

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

	double getXVelocity() {
		return bulletXVelocity;
	}

	double getYVelocity() {
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

	void move(double dx, double dy) {
		circle.move(dx, dy);
	}

	CircleShape getBullet() {
		return circle;
	}

	~Bullet() {}
};

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

	CircleShape getItem() {
		return square;
	}
};

class objCollision {
public:
	double radius;
	double posX;
	double posY;

	bool collisionTest(Character c1, Bullet c2);
	bool collisionItem(Character c1, Item c2);
	~objCollision() {}
};

bool objCollision::collisionTest(Character c1, Bullet c2) {
	double distance;
	distance = sqrt(pow(abs(c1.posX - c2.posX), 2) + pow(abs(c1.posY - c2.posY), 2));

	if (distance <= c1.radius + c2.radius) {
		return true;
	}
	else {
		return false;
	}
}

bool objCollision::collisionItem(Character c1, Item c2) {
	double distance;
	distance = sqrt(pow(abs(c1.posX - c2.posX), 2) + pow(abs(c1.posY - c2.posY), 2));
	if (distance <= c1.radius + c2.radius) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	int nX = 1200;
	int nY = 900;
	RenderWindow window(VideoMode(nX, nY), "Moving Ball");
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
	double velocity = 15;
	double bulletXVelocity = 15;
	double bulletYVelocity = 15;
	bool collide = false; // check collision state
	bool getItem = false; // check if character get item

	CircleShape triangle(characterRadius); //반지름
	triangle.setPosition(c_posX, c_posY);
	triangle.setFillColor(Color(255, 212, 0));
	triangle.setPointCount(3);

	CircleShape circle(bulletRadius);
	circle.setPosition(b_posX, b_posY);
	circle.setFillColor(Color(129, 193, 71));
	circle.setPointCount(30);

	CircleShape square(25, 4);
	square.setPosition(i_posX, i_posY);
	square.setFillColor(Color(255, 192, 203));
	square.setPointCount(4);

	Character Character1(c_posX + 580, c_posY - 450, characterRadius);
	objCollision collTest;

	vector<Bullet> bulletList;
	vector<Item> itemList;

	Item item1(800, 800, 25);
	itemList.push_back(item1);

	for (int i = 0; i < 5; i++) { // initial bullets quantity = 5
		Bullet obj(dis_x(gen), dis_y(gen), bulletRadius);
		bulletList.push_back(obj);
	}

	Text timeText;
	Text bulletText;
	
	int t = 0;
	/*int b = bulletList.size();*/
	bool isCreated = false;

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

	Clock itemTimer;

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
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			window.close();
		}
		
		for (int i = 0; i < bulletList.size(); i++) {
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

		float time = timer.getElapsedTime().asSeconds();
		
		timeText.setString(to_string(time) + " sec");
		bulletText.setString("Bullets: " + to_string(bulletList.size()));

		// 화면을 지운다. 
		window.clear();

		// 화면에 원을 그린다. 
		window.draw(Character1.getCharacter());

		for (int i = 0; i < bulletList.size(); i++) {
			window.draw(bulletList[i].getBullet());
		}
		
		window.draw(timeText);
		window.draw(bulletText);


		if ((int)time % 4 == 0 && (int)time != 0) { // create item every 4 seconds, duration is a second
			Item item1(800, 800, 25);
			itemList.push_back(item1);
			window.draw(itemList[0].getItem());
		}
		else {
			itemList.clear();
		}

		

		if (collTest.collisionItem(Character1, item1) == true) { // when collide to item
			getItem = true;
			Character1.setVelocity(7);
			currentTime = time;
		}

		if ((int)time - (int)currentTime > 4) {
			Character1.setVelocity(4);
			currentTime = 0;
			cout << "changed" << endl;
		}

		// 화면을 표시한다. 
		window.display();


		for (int i = 0; i < bulletList.size(); i++) {
			if (collTest.collisionTest(Character1, bulletList[i]) == true) // when collide to bullets
				collide = true;
		}

		if ((int)time % 5 == 0) { // create one bullet at every 5 seconds
			if (isCreated == true)
				continue;

			if ((int)time == 0)
				continue;
			else {
				Bullet obj(dis_x(gen), dis_y(gen), bulletRadius);
				bulletList.push_back(obj);
				isCreated = true;
			}
		}
		else {
			isCreated = false;
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

