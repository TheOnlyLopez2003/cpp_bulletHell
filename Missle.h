#pragma once
//missile class
class Missle {
private:
	double xPos;
	double yPos;
	double angle;
	double radius;
	bool isAlive = 0;
public:
	Missle(int x, int y);
	void move();
	void draw();
	void kill();
	int getX();
	int getY();
	bool isalive();
	bool offScreen();
	void shoot(int x, int y);
	bool collide(double x, double y);
};
