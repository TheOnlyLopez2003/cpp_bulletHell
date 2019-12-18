#pragma once
#include<allegro5/allegro_primitives.h>
//alienship class
class AlienShip {
private:
	int xPos;
	int yPos;
	int xDir;
	int yDir;
	int health;
	ALLEGRO_BITMAP* image;
public:
	AlienShip(int x, int y, ALLEGRO_BITMAP* pic);
	void move();
	void draw();
	void decreaseHealth();
	int getX();
	int getY();
	int getHealth();
};
