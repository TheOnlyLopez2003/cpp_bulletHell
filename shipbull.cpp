//#include"shipbull.h"
//#include"globals.h"
//#include<allegro5/allegro_primitives.h>
//#include<iostream>
//
//shipbull::shipbull(int x, int y) {
//	x = xPos;
//	y = yPos;
//	radius = 64;
//}
//
//void shipbull::move() {
//	yPos++;
//}
//
//void shipbull::draw() {
//	if (isAlive) {
//		al_draw_filled_circle(xPos + 15, yPos, 5, al_map_rgb(255, 0, 0));
//	}
//}
//
//void shipbull::kill() {
//	isAlive = false;
//}
//
//int shipbull::getX() {
//	return xPos;
//}
//
//int shipbull::getY() {
//	return yPos;
//}
//
//bool shipbull::offScreen() {
//	if (yPos < 0) return true;
//	else return false;
//
//}
//
//bool shipbull::isalive() {
//	return isAlive;
//}
//
//void shipbull::shoot(int x, int y) {
//	isAlive = true;
//	xPos = x;
//	yPos = y;
//}
//
//bool shipbull::collide(double x, double y) {
//	double dx = (xPos - x) * (xPos - x);
//	double dy = (yPos - y) * (yPos - y);
//
//	double dxy = sqrt(dx + dy);
//
//	if (dxy <= radius) {
//		return true;
//	}
//	else return false;
//}
