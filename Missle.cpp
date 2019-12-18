#include"Missle.h"
#include"globals.h"
#include<allegro5/allegro_primitives.h>
#include<iostream>

Missle::Missle(int x, int y) {
	x = xPos;
	y = yPos;
	radius = 64;
}

void Missle::move() {
	yPos -= 10;
}

void Missle::draw() {
	if (isAlive) {
		al_draw_filled_circle(xPos + 15, yPos, 5, al_map_rgb(255, 0, 0));
	}
}

void Missle::kill() {
	isAlive = false;
}

int Missle::getX() {
	return xPos;
}

int Missle::getY() {
	return yPos;
}

bool Missle::offScreen() {
	if (yPos < 0) return true;
	else return false;

}

bool Missle::isalive() {
	return isAlive;
}

void Missle::shoot(int x, int y) {
	isAlive = true;
	xPos = x;
	yPos = y;
}

bool Missle::collide(double x, double y) {
	double dx = (xPos - x) * (xPos - x);
	double dy = (yPos - y) * (yPos - y);

	double dxy = sqrt(dx + dy);

	if (dxy <= radius) {
		return true;
	}
	else return false;
}
