#include "objCollision.h"

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

double objCollision::spawnCollision(Bullet c1, Bullet c2) {
	double distance;
	distance = sqrt(pow(abs(c1.posX - c2.posX), 2) + pow(abs(c1.posY - c2.posY), 2));
	cout << distance << endl;
	cout << "////////////" << endl;

	if (distance < 120)
		cout << "detected" << endl;

	//if (distance < 40) { // distance == 41
	//	cout << "detected" << endl;
	//	return true;
	//}
	//else {
	//	return false;
	//}
	return distance;
}