//MANY THINGS NEED TO BE DELETED BUT LETS LEAVE THEM FOR NOW 
//SO WE MAKE SURE WE DON'T DELETE ANYTHING WE COULD USE
//cs335
//Alien Shoot game
//Modifiers: Sabrina Smith, Jeff Cadena, Lakhdeep, Pedro 
//
//
//program: rainforest
//author:  Gordon Griesel
//date:    2013 to present
//
//This program demonstrates the use of OpenGL and XWindows
//
//Texture maps are displayed.
//Press B to see bigfoot roaming his forest.
//
//The rain builds up like snow on the ground.
//Fix it by removing each raindrop for the rain linked list.
//look for the 
//
//
//
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <cstring>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "ppm.h"
#include "common.h"
#include "sabrinaS.h"
#include "jeffC.h"
extern "C" {
#include "fonts.h"
}

using namespace std;

class Weapon {
	protected:
		// Coordinates of center
		int x, y, z;
		float angle;
		float color[3];
		std::string manufacturer;
		std::string model;
		std::string caliber;
	public:
		// Default ctor to initialize vars
		Weapon() {
			x = 0;
			y = 0;
			z = 0;
			//Default color
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 1.0;
		}
		void shoot();
		void pan();
		void muzzle_flash();
		void set_manufacturer(std::string);
		void set_model(std::string);
		void set_caliber(std::string);
		void set_sights(std::string);
		std::string get_manufacturer();
		std::string get_model();
		std::string get_caliber();
		void show_weapon();
		void show_weapon_specs(Rect);
		void show_fact_sights();
		void show_muzzle_flash();
};

class Glock : public Weapon {
	public:
		Glock() {
			manufacturer = "Glock";
			model = "";
			caliber = "";
		}
};

class Bullet {
	protected:
		// Width and height of the bullet
		int width;
		int height;
		// x, y, z are position vars
		int x;
		int y;
		int z;
		std::string caliber;
		// Velocity of the bullet
		float x_velocity;
		float y_velocity;
	public:
		Bullet() {
			width = 0;
			height = 0;
			x = 0;
			y = 0;
			z = 0;
			caliber = "9mm";
			x_velocity = 0;
			y_velocity = 0;
		}
		void move();
		void set_x(int);
		void set_y(int);
		void set_z(int);
		int get_x();
		int get_y();
		int get_z();
		void delete_bullet();
		void show_bullet();
};

class Target {
	private:
		int x;
		int y;
		int z;
		int width;
		int height;
	public:
		Target() {
			x = 0;
			y = 0;
			z = 0;
			width = 0;
			height = 0;
		}
		void set_x(int);
		void set_y(int);
		void set_z(int);
		int get_x();
		int get_y();
		int get_z();
		void set_width(int);
		void set_height(int);
		int get_width();
		int get_height();
		void show_target();
};

//defined types
typedef double Flt;
typedef double Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) 	(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
			(c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define ALPHA 1

//X Windows variables
Display *dpy;
Window win;

//function prototypes
void initXWindows(void);
void initOpengl(void);
void cleanupXWindows(void);
void checkResize(XEvent *e);
void checkMouse(XEvent *e);
void checkKeys(XEvent *e);
void init();
void loadImages();
void loadTextures();
void load_weapon_texture();
void buildTextures();
unsigned char *buildAlphaData(Ppmimage *);
void physics(Bullet *);
void render(Glock, Bullet*, Target *);

void checkAliens();
void createAliens2();
void createAliens3();
void drawAliens3(void);
void drawAliens2(void);

//void moveAlien(Alien);
//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 30.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end) 
{
	return (double)(end->tv_sec - start->tv_sec ) +
		(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) 
{
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------


int done=0;
int xres=1024, yres=1024;
int totaliens = 0;
//Alien alien;

bool space = false;
int pauseMenu = 0;
int glock30 = 0;
int glock17 = 0;
int showBigfoot=1;
int forest=1;
int curtains=1;
int silhouette=1;
int trees=1;
int showRain=0;
int fire = 0;
int move_bullet = 0;
//
int main(void)
{
	Glock glock32;
	Target *target = new Target;
	target->set_x(280);
	target->set_y(700);
	target->set_z(0);
	Bullet *bullet = new Bullet;
	bullet->set_x(280);
	bullet->set_y(-25);
	bullet->set_z(0);
	logOpen();
	logOpen();
	initXWindows();
	initOpengl();
	init();
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	while (!done) {
		while (XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			checkResize(&e);
			checkMouse(&e);
			checkKeys(&e);
		}
		//
		//Below is a process to apply physics at a consistent rate.
		//1. Get the time right now.
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		//2. How long since we were here last?
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		//3. Save the current time as our new starting time.
		timeCopy(&timeStart, &timeCurrent);
		//4. Add time-span to our countdown amount.
		physicsCountdown += timeSpan;
		//5. Has countdown gone beyond our physics rate? 
		//       if yes,
		//           In a loop...
		//              Apply physics
		//              Reducing countdown by physics-rate.
		//              Break when countdown < physics-rate.
		//       if no,
		//           Apply no physics this frame.
		while (physicsCountdown >= physicsRate) {
			//6. Apply physics
			physics(bullet);
			//7. Reduce the countdown by our physics-rate
			physicsCountdown -= physicsRate;
		}
		//Always render every frame.
		render(glock32, bullet, target);
		glXSwapBuffers(dpy, win);
		fire = 0;
	}
	cleanupXWindows();
	cleanup_fonts();
	logClose();

	delete bullet;
	delete target;

	return 0;
}

void cleanupXWindows(void)
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void setTitle(void)
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Alien Shoot");
}

void setupScreenRes(const int w, const int h)
{
	xres = w;
	yres = h;
}

void initXWindows(void)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
	XSetWindowAttributes swa;

	setupScreenRes(580, 580);
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,
			vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask, &swa);
	GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	setTitle();
}

void reshapeWindow(int width, int height)
{
	//window has been resized.
	setupScreenRes(width, height);
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, xres, 0, yres, -1, 1);
	setTitle();
}

void initOpengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, xres, yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, xres, 0, yres, -1, 1);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);

	//Clear the screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();

	loadImages();
	loadTextures();
	buildTextures();
}

void checkResize(XEvent *e)
{
	//The ConfigureNotify is sent by the
	//server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	if (xce.width != xres || xce.height != yres) {
		//Window size did change.
		reshapeWindow(xce.width, xce.height);
	}
}

void initSounds(void)
{
	//You may add sound here for some extra credit.
	//Fmod is not allowed.
	//OpenAL sound only.
	//Look for the openalTest folder under code.
}

void init() 
{
	while (totaliens < 100) {
		createAliens2();
		++totaliens;
		createAliens3();
		++totaliens;
	}
}

void checkMouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	static int n = 0;
	//
		cout << "e->xbutton.button: " <<e->xbutton.button
			<< endl;
		if (e->xbutton.button == 41) {
			fire = 1;
			move_bullet = 1;
		}		

	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		cout << "savex: " <<savex << endl;
		cout << "savey: " <<savey<< endl;
		//Mouse moved
		//int xdiff = savex - e->xbutton.x;
		//int ydiff = savey - e->xbutton.y;
		
		savex = e->xbutton.x;
		savey = e->xbutton.y;
		if (++n < 10)
			return;
		cout << "Mouse moved" << endl;
	}
}

void checkKeys(XEvent *e)
{
	//keyboard input?
	static int shift=0;
	int key = XLookupKeysym(&e->xkey, 0);
	if (e->type == KeyRelease) {
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return;
	}
	if (e->type == KeyPress) {
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift=1;
			return;
		}
	} 
	else {
		return;
	}
	switch(key) {
		case XK_b:
			//showBigfoot ^= 1;
			//if (showBigfoot) {
			//}
			break;
		case XK_d:
			//deflection ^= 1;
			break;
		case XK_f:
			//forest ^= 1;
			//curtains ^= 1;
			//level1 ^= 1;
			break;
		case XK_s:
			silhouette ^= 1;
			printf("silhouette: %i\n",silhouette);
			break;
		case XK_t:
			trees ^= 1;
			break;
		case XK_u:
			break;
		case XK_p:
			pauseMenu ^= 1;
			break;
		case XK_r:
			break;
		case XK_space:
			space = true;
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
		case XK_n:
			break;
		case XK_w:
			glock30 ^= 1;
			//glock17 ^= 1;
			if (shift) {} 
			break;
		case XK_Escape:
			done=1;
			break;
	}
}

Flt VecNormalize(Vec vec)
{
	Flt len, tlen;
	Flt xlen = vec[0];
	Flt ylen = vec[1];
	Flt zlen = vec[2];
	len = xlen*xlen + ylen*ylen + zlen*zlen;
	if (len == 0.0) {
		MakeVector(0.0,0.0,1.0,vec);
		return 1.0;
	}
	len = sqrt(len);
	tlen = 1.0 / len;
	vec[0] = xlen * tlen;
	vec[1] = ylen * tlen;
	vec[2] = zlen * tlen;
	return(len);
}

void physics(Bullet *bullet)
{
	checkAliens();
	//cout << "bullet y coord: " << bullet->get_y() << endl;
	if (bullet->get_y() > 400) {
		move_bullet = 0;
		bullet->set_x(280);
		bullet->set_y(-25);
		bullet->set_z(0);
	}
	if (move_bullet)
		bullet->set_y(bullet->get_y() + 2);
}

void render(Glock glock32, Bullet *bullet, Target *target)
{
	//Clear the screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//draw a quad with texture
	glColor3f(1.0, 1.0, 1.0);

	if (!space) {
		glBindTexture(GL_TEXTURE_2D, mainMenuTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
	}
	else if (pauseMenu == 1) {
		glBindTexture(GL_TEXTURE_2D, pauseMenuTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
	}
	else if (glock30 == 1) {
		glBindTexture(GL_TEXTURE_2D, glock30Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
	}
	else if (glock17 == 1) {
		glBindTexture(GL_TEXTURE_2D, glock17Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
	}
	else {
		//------------------------------------------------
		//BACKGROUND
		glBindTexture(GL_TEXTURE_2D, backgroundTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
		//------------------------------------------------

		//------------------------------------------------
		//ALIENS
		drawAliens2();
		drawAliens3();
		//------------------------------------------------
		
		//------------------------------------------------
		//LEVELS
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBindTexture(GL_TEXTURE_2D, levelsTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		//------------------------------------------------

		//------------------------------------------------
		//CURTAINS
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBindTexture(GL_TEXTURE_2D, curtainsTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		//------------------------------------------------
		
		// Display the user's weapon and display the target
		//Glock glock32;
		glBindTexture(GL_TEXTURE_2D, 0);
		glVertex3f(100.0, 0.0, 0.0);
		target->show_target();
		glock32.show_weapon();
		glock32.show_fact_sights();
		if (fire)
			glock32.show_muzzle_flash();
		glock32.set_model("32");
		glock32.set_caliber("45 GAP");

		// Display bullet
		//Bullet bullet;
		if (move_bullet)
			bullet->show_bullet();
		
		/*
		Rect r;
		r.bot = yres - 20;
		r.left = 10;
		r.center = 0;
		ggprint8b(&r, 16, 0, "B - Bigfoot");
		ggprint8b(&r, 16, 0, "F - Forest");
		ggprint8b(&r, 16, 0, "S - Silhouette");
		ggprint8b(&r, 16, 0, "T - Trees");
		ggprint8b(&r, 16, 0, "U - Umbrella");
		ggprint8b(&r, 16, 0, "R - Rain");
		ggprint8b(&r, 16, 0, "D - Deflection");
		ggprint8b(&r, 16, 0, "N - Sounds");
		ggprint8b(&r, 16, 0, "W - Weapon");
		*/

		// Reposition the Rect instance r so weapon menu will be 
		// displayed in bottom right corner
		//r.bot = yres - 400;
		//r.left = 550;
		//r.center = 540;

		//glock32.show_weapon_specs(r);
	}
}
