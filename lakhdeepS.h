/*
 * Author: Lakhdeep Singh
 * CS 335 Group Project
 * Purpose: To have definitions. The frameworks for the movement
 *
 * */
#include <iostream>
#include <functional>
//#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <cstdlib>
extern "C"  {
	#include "fonts.h"
}

#ifndef LAKHDEEPS_H
#define LAKHDEEPS_H
#endif

typedef double Vec[3];

typedef struct t_alien {
        Vec pos;
        Vec vel;
        struct t_alien *prev;
        struct t_alien *next;
} Alien;

void moveAlien(Alien);
