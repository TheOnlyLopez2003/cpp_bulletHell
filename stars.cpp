#include"stars.h"
#include"globals.h"
#include<allegro5/allegro_primitives.h>
star::star() {
	xPos = rand() % 800;
	yPos = rand() % 800;
	r = rand() % 50;
	g = rand() % 255;
	b = rand() % 255;
	size = rand() % 5;
}

void star::draw() {
	al_draw_filled_circle(xPos, yPos, size, al_map_rgb(r, g, b));

}

void star::reposition() {
	if (yPos > SCREEN_W) {
		r = rand() % 50;
		g = rand() % 255;
		b = rand() % 255;
		size = rand() % 5;
		xPos = rand() % SCREEN_W;
		yPos = 0;
	}
}

void star::move() {
	yPos += 15;
}
