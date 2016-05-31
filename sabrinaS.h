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

extern Ppmimage *alienImage;
extern Ppmimage *humanImage;
extern Ppmimage *backgroundImage;
extern Ppmimage *curtainsImage;
extern Ppmimage *levelsImage;
extern Ppmimage *mainMenuImage;
extern Ppmimage *pauseMenuImage;
extern Ppmimage *dashImage;
extern Ppmimage *gameOverImage;
extern GLuint alienTexture;
extern GLuint humanTexture;
extern GLuint alienSilhouetteTexture;
extern GLuint humanSilhouetteTexture;
extern GLuint backgroundTexture;
extern GLuint levelsTexture;
extern GLuint mainMenuTexture;
extern GLuint pauseMenuTexture;
extern GLuint dashTexture;
extern GLuint gameOverTexture;
extern GLuint curtainsTexture;

typedef double Vec[3];

typedef struct t_alien {
        Vec pos;
        Vec vel;
        struct t_alien *prev;
        struct t_alien *next;
} Alien;

typedef struct t_human {
        Vec pos;
        Vec vel;
        struct t_human *prev;
        struct t_human *next;
} Human;

extern Alien *row1HeadAlien;
extern Alien *row2HeadAlien;
extern Alien *row3HeadAlien;
extern Human *row1HeadHuman;
extern Human *row2HeadHuman;
extern Human *row3HeadHuman;
