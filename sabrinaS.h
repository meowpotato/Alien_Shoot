#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>

#include "ppm.h"

extern Ppmimage *bigfootImage;
extern Ppmimage *backgroundImage;
extern Ppmimage *forestImage;
extern Ppmimage *curtainsImage;
extern Ppmimage *umbrellaImage;
extern Ppmimage *mainMenuImage;
extern Ppmimage *pauseMenuImage;
extern Ppmimage *glock30Image;
extern Ppmimage *glock17Image;
extern GLuint bigfootTexture;
extern GLuint silhouetteTexture;
extern GLuint forestTexture;
extern GLuint backgroundTexture;
extern GLuint mainMenuTexture;
extern GLuint pauseMenuTexture;
extern GLuint glock30Texture;
extern GLuint glock17Texture;
extern GLuint curtainsTexture;
extern GLuint umbrellaTexture;

