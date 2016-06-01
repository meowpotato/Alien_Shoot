/* Author: Lakhdeep Singh
 * HW3 - CS 335 Individual Contribution to project
 * Date Written: 4/15/16-5/31/16, modified 4/27/16, modified 5/2/16, 5/4/16,
 * 5/10/16, 5/14/16, 5/22/16, 5/26/16, 5/28/16, 5/29/16, 5/30/16
 *
 * So far,  the code down below is for the movement of the aliens
 * this all works and does compile,
 * and more code for more movement will be added soon.
 * This code will compile with the main Alien_Shoot.cpp file
 * A lot of the coding has been done in the main file of our game
 * */
//Put in .h file
/*#include <iostream>
#include <functional>
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <cstdlib> */

#include "common.h"
#include "lakhdeepS.h"


//defined types
typedef double Flt;
typedef double Vec [3];
typedef Flt 	Matrix [4][4];

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random (a) (rand()%a)
#define MakeVector(x, y, z, v) (v) [0]=(x), (v)[1]=(y), (v)[2]=(z)

using namespace std;

void moveAlien(Alien alien)
{
	//Alien alien;
	//move alien...
	int addgrav = 1;
	//Update position
	alien.pos[0] += alien.vel[0];
	alien.pos[1] += alien.vel[1];
	//Check for collision with window edges
	if ((alien.pos[0] < -140.0 && alien.vel[0] < 0.0) ||
			(alien.pos[0] >= (float)xres+140.0 && alien.vel[0] > 0.0)) {
		alien.vel[0] = -alien.vel[0];
		addgrav = 0;
	}
	if ((alien.pos[1] < 150.0 && alien.vel[1] < 0.0) ||
			(alien.pos[1] >= (float)yres && alien.vel[1] > 0.0)) {
		alien.vel[1] = -alien.vel[1];
		addgrav = 0;
	}
	//Gravity
	if (addgrav)
		alien.vel[1] -= 0.75;
}

//same thing for second one
void moveAlien2(Alien alien)
{
	int addgrav = 2;
	alien.pos[0] += alien.vel[0];
	alien.pos[1] += alien.vel[1];
	if ((alien.pos[0] < -140.0 && alien.vel[0] < 0.0) ||
			(alien.pos[0] >= (float)xres+140.0 && alien.vel[0] > 0.0)) {
		alien.vel[0] = -alien.vel[0];
		addgrav = 0;
	}
	if ((alien.pos[1] < 150.0 && alien.vel[1] < 0.0) ||
			(alien.pos[1] >= (float)yres && alien.vel[1] > 0.0)) {
		alien.vel[1] = -alien.vel[1];
		addgrav = 0;
	}
	if (addgrav)
		alien.vel[1] -= 0.75;
}

/*
//Attempt to have scoreboard showing
void showScoreboard()
{
	Rect r;
	glClear(GL_COLOR_BUFFER_BIT);
	//
	r.bot = yres - 20;
	r.left = 10;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ff0000, "SCORE");
	ggprint8b(&r, 16, 0x00ff0000, "n score: %i", g->score);
}
*/

// test code for more alien's movement
// to show more than one alien's movement
/*
	switch(x){
	case 0:{
	       if (do_up)
	      	   run_do_up();
	       else if(do_a)
	       	   run_do_a();
	       else if(do_n)
	           run_do_n();
	       else
	       success = false;
	       break;
	       }
	case 1:{
	       if(do_n)
	           run_do_n();
	       else if(do_a)
	           run_do_a();
	       else
	       success = false;
	       break;
	       }
	default: {
	       if(do_a)
	           run_do_a();
	       else if(do_n)
	           run_do_n();
	       else
	       success = false;
	       }
}


if (display_lakhdeep)
	rectangle r;
	r.pos[0] = 250;
	r.pos[1] = 250;
	r.height = 50;
	r.width = 50;
	drawRectangle(r);
	display();
*/

//third alien
void moveAlien3(Alien alien)
{
	int addgrav = 3;
	alien.pos[0] += alien.vel[0];
	alien.pos[1] += alien.vel[1];
	if ((alien.pos[0] < -140.0 && alien.vel[0] < 0.0) ||
			(alien.pos[0] >= (float)xres+140.0 && alien.vel[0] > 0.0)) {
		alien.vel[0] = -alien.vel[0];
		addgrav = 0;
	}
	if ((alien.pos[1] < 150.0 && alien.vel[1] < 0.0) ||
			(alien.pos[1] >= (float)yres && alien.vel[1] > 0.0)) {
		alien.vel[1] = -alien.vel[1];
		addgrav = 0;
	}
	if (addgrav)
		alien.vel[1] -= 0.75;
}

/*
//delete alien to respawn
void deleteAlien1(Alien alien)
{
        if (alien->prev == NULL) {
                if (alien->next == NULL) {
                        row1_head = NULL;
                }
                else {
                        alien->next->prev = NULL;
                        row1_head = alien->next;
                }
        }

        else {
                if (alien->next == NULL) {
                        alien->prev->next = NULL;
                }
                else {
                        alien->prev->next = currentAlien->next;
                        alien->next->prev = currentAlien->prev;
                }
        }
	} */
//movement of Humans
void moveHuman1(Human human)
{
	int addgrav = 1;
	human.pos[0] += human.vel[0];
	human.pos[1] += human.vel[1];
	if ((human.pos[0] < -140.0 && human.vel[0] < 0.0) ||
			(human.pos[0] >= (float)xres+140.0 && human.vel[0] > 0.0)) {
		human.vel[0] = -human.vel[0];
		addgrav = 0;
	}
	if ((human.pos[1] < 150.0 && human.vel[1] < 0.0) ||
			(human.pos[1] >= (float)yres && human.vel[1] > 0.0)) {
		human.vel[1] = -human.vel[1];
		addgrav = 0;
	}
	if (addgrav)
		human.vel[1] -= 0.75;
}

void moveHuman2(Human human)
{
        int addgrav = 2;
        human.pos[0] += human.vel[0];
        human.pos[1] += human.vel[1];
        if ((human.pos[0] < -160.0 && human.vel[0] < 0.0) ||
                        (human.pos[0] >= (float)xres+140.0 && human.vel[0] > 0.0)) {
                human.vel[0] = -human.vel[0];
                addgrav = 0;
        }
        if ((human.pos[1] < 150.0 && human.vel[1] < 0.0) ||
                        (human.pos[1] >= (float)yres && human.vel[1] > 0.0)) {
                human.vel[1] = -human.vel[1];
                addgrav = 0;
        }
        if (addgrav)
                human.vel[1] -= 0.80;
}
/*void moveHuman3(Human human)
{
	int addgrav = 3;
}*/
