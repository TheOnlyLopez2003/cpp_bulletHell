#include"AlienShip.h"
#include"globals.h"
#include<allegro5/allegro_primitives.h>
#include<iostream>

AlienShip::AlienShip(int x, int y, ALLEGRO_BITMAP* pic) {

	xPos = x;
	yPos = y;
	xDir = 2;
	yDir = 0;
	image = pic;
	health = 100;

}

void AlienShip::draw() {

	al_draw_bitmap(image, xPos, yPos, NULL);

}

void AlienShip::move() {
	if (xPos < 0 || xPos + 125 > 800)
		xDir *= -1;
	xPos += xDir;
}

void AlienShip::decreaseHealth() {

	if(health > 0) {
		health--;
	}

}

int AlienShip::getX() {
	return xPos;
}

int AlienShip::getY() {
	return yPos;
}

int AlienShip::getHealth() {
	return health;
}
