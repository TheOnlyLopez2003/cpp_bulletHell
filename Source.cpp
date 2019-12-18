#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <ctime>
#include<iostream>
#include<vector>
#include"stars.h"
#include"Missle.h"
#include"AlienShip.h"
#include"shipbull.h"
#include"globals.h"
#define value cout
using namespace std;

int main()
{
	value << "Flag 1" << endl;

	vector<star*> starfield;
	vector<star*>::iterator iter3;
	for (int i = 0; i <= 300; i++) {
		star* newStar = new star();
		starfield.push_back(newStar);
	}

	//vector<bullet*> shipbull;
	//vector<bullet*>::iterator iter4;

	//set up allegro
	al_init();
	srand(time(NULL));
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_primitives_addon();
	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* shipPic = al_load_bitmap("ship.png");
	ALLEGRO_BITMAP* image = al_load_bitmap("mothership.png");
	ALLEGRO_BITMAP* image2 = al_load_bitmap("boom.png");
	ALLEGRO_FONT* font = al_load_ttf_font("Minecraft.ttf", 30, NULL);
	//position of player
	double xPos = 400;
	double yPos = 700;
	AlienShip Enemy1(400, 100, al_load_bitmap("mothership.png"));
	//game variables
	bool key[5] = { false, false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop
	double ticker = 0;
	double counter = 0;
	double minBullets = 60;
	double cellNum = 0;
	int dir = 0;
	int justShot = 0;
	int AlienHit = 0;
	int hitX = 0;
	int hitY = 0;
	int playerHealth = 100;

	//cout << "Flag 2" << endl;
	al_start_timer(timer);
	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//vector to hold missles
	vector<Missle*> missles;
	vector<Missle*>::iterator iter2;
	for (int i = 0; i < 10; i++) {
		Missle* newMissle = new Missle(0, 0);
		missles.push_back(newMissle);
	}

	al_flip_display();

	//cout << "Flag 3" << endl;

	while (!doexit)//game loop!
	{
		ALLEGRO_EVENT ev;
		//cout << "Flag 3.5" << endl;
		al_wait_for_event(event_queue, &ev);
		//cout << "Flag 4" << endl;
		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			counter++; //variable to slow down object creation. Initialize it to 0 above your game loop
			minBullets -= .001; //variable initialized to 60. Subtracting here speeds up object creation over time!
			if (counter > minBullets) {
				//create newbullets, push into vector

				//bullet* newbullet = new bullet(AlienShip.getX(), AlienShip.getY(), 0);
				//bullets.push_back(newbullet);

				//more bullet instantiations will go here!

				counter = 0;
			}

			//this is to slow down your animation
			//otherwise it moves at the speed of your game loop
			ticker++;
			if (ticker > 10) {
				ticker = 0;
			}
			if (ticker == 0) {
				cellNum++;
			}

			//move the animation forward, loop back after 4 cells
			if (dir == KEY_UP || dir == KEY_DOWN) {
				if (ticker == 0) {
					cellNum++;
				}
				if (cellNum > 4) {
					cellNum = 0;
				}

			}
			if (dir == KEY_LEFT || dir == KEY_RIGHT) {
				if (cellNum < 5) {
					cellNum = 5;
				}
				if (cellNum > 9) {
					cellNum = 5;
				}
			}


			Enemy1.move();
			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP] && yPos > 0) {
				yPos -= 4.0;
			}
			if (key[KEY_DOWN] && yPos + 30 < 800) {
				yPos += 4.0;
			}
			if (key[KEY_LEFT] && xPos > 0) {
				xPos -= 4.0;
			}
			if (key[KEY_RIGHT] && xPos + 30 < 800) {
				xPos += 4.0;
			}
			if (key[KEY_SPACE]) {
				for (iter2 = missles.begin(); iter2 != missles.end(); iter2++) {
					if ((*iter2)->isalive() == false && justShot > 5) {
						(*iter2)->shoot(xPos, yPos);
						justShot = 0;
					}
				}
			}

			justShot++;
			// move missles
			for (iter2 = missles.begin(); iter2 != missles.end(); iter2++) {
				if ((*iter2)->isalive()) {
					(*iter2)->move();
				}
			}

			// cull missles
			for (iter2 = missles.begin(); iter2 != missles.end(); iter2++) {
				if ((*iter2)->offScreen()) {
					(*iter2)->kill();
				}
			}

			//cout << "Flag 5" << endl;

			//check missle collision with Mothership
			for (iter2 = missles.begin(); iter2 != missles.end(); iter2++) {
				if ((*iter2)->collide(Enemy1.getX() + 64, Enemy1.getY() - 16)) {

					Enemy1.decreaseHealth();
					value << "AlienShip Hit!" << endl;
					AlienHit = 30;
					hitX = (*iter2)->getX();
					hitY = (*iter2)->getY();
				}
			}
			////////////////////////bullets///////////////////////////////////
			//move bullet
			//for (iter4 = minBullets.begin(); iter4 != minBullets.end(); iter4++) {
			//	if ((*iter4)->isalive()) {
			//		(*iter4)->move();
			//	}
			//}
			//
			////cull bullet
			//for (iter4 = minBullets.begin(); iter4 != minBullets.end(); iter4++) {
			//	if ((*iter4)->offScreen()) {
			//		(*iter4)->kill();
			//	}
			//}


			//check bullet collision with player
			for (iter2 = missles.begin(); iter2 != missles.end(); iter2++) {
				if ((*iter2)->collide(Enemy1.getX() + 64, Enemy1.getY() - 16)) {

					Enemy1.decreaseHealth();
					value << "AlienShip Hit!" << endl;
					AlienHit = 30;
					hitX = (*iter2)->getX();
					hitY = (*iter2)->getY();
				}
			}

			redraw = true;
		}
		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		//cout << "Flag 6" << endl;

		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing(without this things smear)
			//replaces the draw circle function in the render section


			for (iter2 = missles.begin(); iter2 != missles.end(); iter2++) {
				(*iter2)->draw();
			}
			for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
				(*iter3)->draw();
			}
			for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
				(*iter3)->reposition();
				(*iter3)->move();
			}
			for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
				(*iter3)->draw();
			}
			if (dir == KEY_LEFT) {
				al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, ALLEGRO_FLIP_HORIZONTAL);
			}
			else {
				al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, NULL);
			}

			Enemy1.draw();

			//cout << "Flag 7" << endl;

			if (AlienHit > 0) {
				al_draw_bitmap_region(image2, cellNum * 20, 0, 20, 20, hitX, hitY, 0);
				AlienHit--;
			}

			//draw the player health bar
			al_draw_rectangle(20, 20, 120, 40, al_map_rgb(255, 255, 255), 10);
			al_draw_filled_rectangle(20, 20, 20 + playerHealth, 40, al_map_rgb(200, 40, 140));
			al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 50, NULL, "Player Health: ");

			//draw AlienShip health
			al_draw_rectangle(400, 20, 500, 40, al_map_rgb(255, 255, 255), 10);
			al_draw_filled_rectangle(400, 20, 400 + Enemy1.getHealth(), 40, al_map_rgb(200, 200, 40));
			al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 50, NULL, "Enemy Health: ");

			//ends game
			if (Enemy1.getHealth() == 0) {
				ALLEGRO_FONT* font = al_load_ttf_font("Minecraft.ttf", 80, NULL);
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_textf(font, al_map_rgb(255, 255, 255), 160, 380, NULL, "GAME OVER");

			}

			//al_draw_circle(xPos, yPos, 50, al_map_rgb(50, 120, 10), 10); //draw the player
			al_flip_display(); //flip everything from memory to gamescreen
		}//end render

	}//end game loop

	//cout << "Flag 8" << endl;

	al_rest(.00001);

	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}
