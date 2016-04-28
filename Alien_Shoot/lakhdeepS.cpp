//Lakhdeep Singh
//Lab 5
//CS 335 - Project

#include <iostream>
#include <functional>
using namespace std;

int xres=800, yres=600;
void moveAlien()
{
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

