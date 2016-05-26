/* Author: Lakhdeep Singh
 * HW3 - CS 335 Individual Contribution to project
 * Date Written: 4/15/16-5/3/16, modified 4/27/16, modified 5/2/16
 *
 * So far,  the code down below is for the movement of the aliens
 * this all works and does compile,
 * and more code for more movement will be added soon.
 * This code will compile with the main Alien_Shoot.cpp file
 * */
#include <iostream>
#include <functional>
#include "common.h"

using namespace std;

//Alien alien;
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

// test code for more alien's movement
// to show more than one alien's movement
/*
switch(x){
	case 0:{
		       if(do_up)
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
