//Author: Sabrina Smith
//Class: CMPS 335
//Purpose: Lab 5 - Work on project material
//	   Loading images and textures outside of main .cpp file	   


#include "sabrinaS.h"

Ppmimage *bigfootImage=NULL;
Ppmimage *forestImage=NULL;
Ppmimage *forestTransImage=NULL;
Ppmimage *umbrellaImage=NULL;
Ppmimage *mainMenuImage=NULL;
Ppmimage *pauseMenuImage=NULL;
Ppmimage *glock30Image=NULL;
GLuint bigfootTexture;
GLuint silhouetteTexture;
GLuint forestTexture;
GLuint mainMenuTexture;
GLuint pauseMenuTexture;
GLuint glock30Texture;
GLuint forestTransTexture;
GLuint umbrellaTexture;

float wid = 120.0f;


void loadImages() {
	bigfootImage     = ppm6GetImage("./images/bigfoot.ppm");
	forestImage      = ppm6GetImage("./images/forest.ppm");
	mainMenuImage    = ppm6GetImage("./images/mainMenu.ppm");
	pauseMenuImage   = ppm6GetImage("./images/pauseMenu.ppm");
	glock30Image     = ppm6GetImage("./images/glock_30.ppm");
	forestTransImage = ppm6GetImage("./images/forestTrans.ppm");
	umbrellaImage    = ppm6GetImage("./images/umbrella.ppm");
}

void loadTextures() {
	glGenTextures(1, &bigfootTexture);
	glGenTextures(1, &silhouetteTexture);
	glGenTextures(1, &forestTexture);
	glGenTextures(1, &mainMenuTexture);
	glGenTextures(1, &pauseMenuTexture);
	glGenTextures(1, &glock30Texture);
	glGenTextures(1, &umbrellaTexture);
}

unsigned char *buildAlphaData(Ppmimage *img)
{
	//add 4th component to RGB stream...
	int i;
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		//get largest color component...
		//*(ptr+3) = (unsigned char)((
		//              (int)*(ptr+0) +
		//              (int)*(ptr+1) +
		//              (int)*(ptr+2)) / 3);
		//d = a;
		//if (b >= a && b >= c) d = b;
		//if (c >= a && c >= b) d = c;
		//*(ptr+3) = d;
		*(ptr+3) = (a|b|c);
		ptr += 4;
		data += 3;
	}
	return newdata;
}


void buildTextures() {
	int w = bigfootImage->width;
	int h = bigfootImage->height;
	//
	glBindTexture(GL_TEXTURE_2D, bigfootTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
	//
	//silhouette
	//this is similar to a sprite graphic
	//
	glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	unsigned char *silhouetteData = buildAlphaData(bigfootImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	//  GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
	//
	//umbrella
	//
	glBindTexture(GL_TEXTURE_2D, umbrellaTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	silhouetteData = buildAlphaData(umbrellaImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	//  GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
	//
	//forest
	glBindTexture(GL_TEXTURE_2D, forestTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			forestImage->width, forestImage->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, forestImage->data);

	//-------------------------------------------------------------------------
	//
	//main menu
	glBindTexture(GL_TEXTURE_2D, mainMenuTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			mainMenuImage->width, mainMenuImage->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, mainMenuImage->data);


	//-------------------------------------------------------------------------
	//
	//pause menu
	glBindTexture(GL_TEXTURE_2D, pauseMenuTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			pauseMenuImage->width, pauseMenuImage->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, pauseMenuImage->data);

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//
	//Glock 30 Weapon
	glBindTexture(GL_TEXTURE_2D, glock30Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			glock30Image->width, glock30Image->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, glock30Image->data);

	//-------------------------------------------------------------------------
	//
	//forest transparent part
	//
	glBindTexture(GL_TEXTURE_2D, forestTransTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	w = forestTransImage->width;
	h = forestTransImage->height;
	unsigned char *ftData = buildAlphaData(forestTransImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	//GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
}
/*
void renderMainMenu () {
	glBindTexture(GL_TEXTURE_2D, mainMenuTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
	glEnd();
}

void renderPauseMenu () {
	glBindTexture(GL_TEXTURE_2D, pauseMenuTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
	glEnd();

}

void renderGun () {
	glBindTexture(GL_TEXTURE_2D, glock30Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
	glEnd();

}
void renderBackground () {
	glBindTexture(GL_TEXTURE_2D, forestTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
	glEnd();

}
void renderBigfoot () {
	
	Bigfoot alien;

	glPushMatrix();
	glTranslatef(alien.pos[0], alien.pos[1], alien.pos[2]);
	//if (!silhouette) {
	//	glBindTexture(GL_TEXTURE_2D, bigfootTexture);
	//} else {
		glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);
	//}
	glBegin(GL_QUADS);
	if (alien.vel[0] > 0.0) {
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
	} else {
		glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-wid);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
		glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, wid);
		glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-wid);
	}
	glEnd();
	glPopMatrix();
	//
	if (trees && silhouette) {
		glBindTexture(GL_TEXTURE_2D, forestTransTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
	}
	glDisable(GL_ALPHA_TEST);

}*/
