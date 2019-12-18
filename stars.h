#pragma once
//stars class
class star {
private:
	int xPos;
	int yPos;
	int size;
	int r;
	int g;
	int b;
public:
	star();
	void draw();
	void move();
	void reposition();
};
