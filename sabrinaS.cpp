//Author: Sabrina Smith
//Class: CMPS 335
//Purpose: Lab 5 - Work on project material
//	   Loading images and textures outside of main.cpp file	   
//Modified: 5/2/16


#include "sabrinaS.h"

Ppmimage *bigfootImage=NULL;
Ppmimage *alienImage=NULL;
Ppmimage *forestImage=NULL;
Ppmimage *backgroundImage=NULL;
Ppmimage *curtainsImage=NULL;
Ppmimage *levelsImage=NULL;
Ppmimage *umbrellaImage=NULL;
Ppmimage *mainMenuImage=NULL;
Ppmimage *pauseMenuImage=NULL;
Ppmimage *glock30Image=NULL;
Ppmimage *glock17Image=NULL;
GLuint bigfootTexture;
GLuint alienTexture;
GLuint silhouetteTexture;
GLuint forestTexture;
GLuint levelsTexture;
GLuint backgroundTexture;
GLuint mainMenuTexture;
GLuint pauseMenuTexture;
GLuint glock30Texture;
GLuint glock17Texture;
GLuint curtainsTexture;
GLuint umbrellaTexture;

float wid = 120.0f;


void loadImages() 
{
	alienImage       = ppm6GetImage("./images/alien.ppm");
	levelsImage	 = ppm6GetImage("./images/levels.ppm");
	backgroundImage  = ppm6GetImage("./images/background.ppm");
	mainMenuImage    = ppm6GetImage("./images/mainMenu.ppm");
	pauseMenuImage   = ppm6GetImage("./images/pauseMenu.ppm");
	glock30Image     = ppm6GetImage("./images/glock_30.ppm");
	glock17Image     = ppm6GetImage("./images/glock_17.ppm");
	curtainsImage    = ppm6GetImage("./images/curtains1.ppm");
}

void loadTextures() 
{
	glGenTextures(1, &alienTexture);
	glGenTextures(1, &backgroundTexture);
	glGenTextures(1, &silhouetteTexture);
	glGenTextures(1, &levelsTexture);
	glGenTextures(1, &curtainsTexture);
	glGenTextures(1, &mainMenuTexture);
	glGenTextures(1, &pauseMenuTexture);
	glGenTextures(1, &glock30Texture);
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


void buildTextures() 
{
	//-------------------------------------------------------------------------
	//
	//alien
	//
	//
	glBindTexture(GL_TEXTURE_2D, alienTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	int w = alienImage->width;
	int h = alienImage->height;
	unsigned char *ftData = buildAlphaData(alienImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);
	//-------------------------------------------------------------------------
	//
	//silhouette
	//this is similar to a sprite graphic
	//
	//glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
	//
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	//unsigned char *silhouetteData = buildAlphaData(bigfootImage);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	//		GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	//free(silhouetteData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	//  GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
	//
	//background
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			backgroundImage->width, backgroundImage->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, backgroundImage->data);

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
	//
	//Glock 30 Weapon
	//
	glBindTexture(GL_TEXTURE_2D, glock30Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			glock30Image->width, glock30Image->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, glock30Image->data);

	//-------------------------------------------------------------------------
	//
	//Glock 17 Weapon
	//
	glBindTexture(GL_TEXTURE_2D, glock17Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			glock17Image->width, glock17Image->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, glock17Image->data);


	//-------------------------------------------------------------------------
	//
	//curtains
	//
	glBindTexture(GL_TEXTURE_2D, curtainsTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	w = curtainsImage->width;
	h = curtainsImage->height;
	ftData = buildAlphaData(curtainsImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);

	//-------------------------------------------------------------------------
	//
	//levels
	//
	glBindTexture(GL_TEXTURE_2D, levelsTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	w = levelsImage->width;
	h = levelsImage->height;
	ftData = buildAlphaData(levelsImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);
}
