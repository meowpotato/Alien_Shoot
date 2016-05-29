//Author: Sabrina Smith
//Class: CMPS 335
//Purpose: Lab 5 - Work on project material
//	   Loading images and textures outside of main.cpp file	   
//Modified: 5/2/16


#include "sabrinaS.h"
#include "common.h"

int totaliens = 0;
int deleted1 = 0;
int deleted2 = 0;
int deleted3 = 0;
Alien *row1_head = NULL;
Alien *row2_head = NULL;
Alien *row3_head = NULL;

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
	glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	unsigned char *silhouetteData = buildAlphaData(alienImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);
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

int createAliens1() 
{
        Alien *node = (Alien *)malloc(sizeof(Alien));
        printf("alien created\n");
        node->prev = NULL;
        node->next = NULL;
        node->pos[0] = -100.0 + (rand() % 5);
        node->pos[1] = 365.0;
        node->vel[0] = rand() % 5 + 1;
        node->vel[1] = 0.0;
        node->next = row1_head;
        if (row1_head != NULL)
                row1_head->prev = node;
        row1_head = node;
        ++totaliens;
        printf("number of aliens:%d\n", totaliens);
        return totaliens;
}


int createAliens2() 
{
	Alien *node = (Alien *)malloc(sizeof(Alien));
	printf("alien created\n");
	node->prev = NULL;
	node->next = NULL;
	node->pos[0] = -100.0 + (rand() % 5);
	node->pos[1] = 270.0;
	node->vel[0] = rand() % 5 + 3;
	node->vel[1] = 0.0;
	node->next = row2_head;
	if (row2_head != NULL)
		row2_head->prev = node;
	row2_head = node;
	++totaliens;
	printf("number of aliens:%d\n", totaliens);
	return totaliens;
}

int createAliens3() 
{
	Alien *node = (Alien *)malloc(sizeof(Alien));
	printf("alien created\n");
	node->prev = NULL;
	node->next = NULL;
	node->pos[0] = -100.0 + (rand() % 5);
	node->pos[1] = 175.0;
	node->vel[0] = rand() % 5 + 5;
	node->vel[1] = 0.0;
	node->next = row3_head;
	if (row3_head != NULL)
		row3_head->prev = node;
	row3_head = node;
	++totaliens;
	printf("number of aliens:%d\n", totaliens);
	return totaliens;
}

void deleteAlien1(Alien *currentAlien)
{
        if (currentAlien->prev == NULL) {
                if (currentAlien->next == NULL) {
                        row1_head = NULL;
                }
                else {
                        currentAlien->next->prev = NULL;
                        row1_head = currentAlien->next;
                }
        }

        else {
                if (currentAlien->next == NULL) {
                        currentAlien->prev->next = NULL;
                }
                else {
                        currentAlien->prev->next = currentAlien->next;
                        currentAlien->next->prev = currentAlien->prev;
                }
        }

	        

	free(currentAlien);
        currentAlien = NULL;
        --totaliens;
        printf("Alien deleted\n");
}

void deleteAlien2(Alien *currentAlien) 
{
	if (currentAlien->prev == NULL) {
		if (currentAlien->next == NULL) {
			row2_head = NULL;
		}
		else {
			currentAlien->next->prev = NULL;
			row2_head = currentAlien->next;
		}
	}

	else {
		if (currentAlien->next == NULL) {
			currentAlien->prev->next = NULL;
		}
		else {
			currentAlien->prev->next = currentAlien->next;
			currentAlien->next->prev = currentAlien->prev;
		}
	}

	free(currentAlien);
	currentAlien = NULL;
	--totaliens;
	printf("Alien deleted\n");
}

void deleteAlien3(Alien *currentAlien) 
{
	if (currentAlien->prev == NULL) {
		if (currentAlien->next == NULL) {
			row3_head = NULL;
		}
		else {
			currentAlien->next->prev = NULL;
			row3_head = currentAlien->next;
		}
	}

	else {
		if (currentAlien->next == NULL) {
			currentAlien->prev->next = NULL;
		}
		else {
			currentAlien->prev->next = currentAlien->next;
			currentAlien->next->prev = currentAlien->prev;
		}
	}

	free(currentAlien);
	currentAlien = NULL;
	--totaliens;
	printf("Alien deleted\n");
}

int moveAlien1(Alien *alien)
{
        //move alien...
        //Update position
        alien->pos[0] += alien->vel[0];
        //alien.pos[1] += alien.vel[1];
        //Check for collision with window edges
        if (//(alien->pos[0] < -140.0 && alien->vel[0] < 0.0) ||
                        (alien->pos[0] >= (float)xres+140.0 && alien->vel[0] > 0.0) && alien->pos[1] ==  270.0) {
                //alien->vel[0] = -alien->vel[0];
                deleteAlien2(alien);
                return 1;
        }
        
	return 0;
        //if ((alien->pos[1] < 150.0 && alien->vel[1] < 0.0) ||
        //              (alien->pos[1] >= (float)yres && alien->vel[1] > 0.0)) {
        //      alien->vel[1] = -alien->vel[1];
        //      addgrav = 0;
        //}
}

int moveAlien2(Alien *alien)
{
	//move alien...
	//Update position
	alien->pos[0] += alien->vel[0];
	//alien.pos[1] += alien.vel[1];
	//Check for collision with window edges
	if (//(alien->pos[0] < -140.0 && alien->vel[0] < 0.0) ||
			(alien->pos[0] >= (float)xres+140.0 && alien->vel[0] > 0.0) && alien->pos[1] ==  270.0) {
		//alien->vel[0] = -alien->vel[0];
		deleteAlien2(alien);
		return 1;
	}

	return 0;
	//if ((alien->pos[1] < 150.0 && alien->vel[1] < 0.0) ||
	//              (alien->pos[1] >= (float)yres && alien->vel[1] > 0.0)) {
	//      alien->vel[1] = -alien->vel[1];
	//      addgrav = 0;
	//}
}

int moveAlien3(Alien *alien)
{
	//move alien...
	//Update position
	alien->pos[0] += alien->vel[0];
	//alien.pos[1] += alien.vel[1];
	//Check for collision with window edges
	if (//(alien->pos[0] < -140.0 && alien->vel[0] < 0.0) ||
			(alien->pos[0] >= (float)xres+140.0 && alien->vel[0] > 0.0) && alien->pos[1] == 175.0) {
		//alien->vel[0] = -alien->vel[0];
		deleteAlien3(alien);
		return 1;
	}
	
	return 0;
	//if ((alien->pos[1] < 150.0 && alien->vel[1] < 0.0) ||
	//              (alien->pos[1] >= (float)yres && alien->vel[1] > 0.0)) {
	//      alien->vel[1] = -alien->vel[1];
	//      addgrav = 0;
	//}
}

void drawAliens1(void) {
        Alien *alien = row1_head;
        float wid = 32.0f;
        while(alien){
                glPushMatrix();
                glTranslatef(alien->pos[0], alien->pos[1], alien->pos[2]);
                glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glColor4ub(255,255,255,255);

                glBegin(GL_QUADS);
                if (alien->vel[0] > 0.0) {
                        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
                        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
                        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
                        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
                } /*else {
                        glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-wid);
                        glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
                        glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, wid);
                        glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-wid);
                }*/
                glEnd();
                glPopMatrix();
                alien = alien->next;
        }
        glDisable(GL_ALPHA_TEST);
}

void drawAliens2(void) {
	Alien *alien = row2_head;
	float wid = 32.0f;
	while(alien){
		glPushMatrix();
		glTranslatef(alien->pos[0], alien->pos[1], alien->pos[2]);
		glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);

		glBegin(GL_QUADS);
		if (alien->vel[0] > 0.0) {
			glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
			glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
			glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
		} /*else {
			glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-wid);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
			glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, wid);
			glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-wid);
		}*/
		glEnd();
		glPopMatrix();
		alien = alien->next;
	}
	glDisable(GL_ALPHA_TEST);
}

void drawAliens3(void) {
	Alien *alien = row3_head;
	float wid = 32.0f;
	while(alien){
		glPushMatrix();
		glTranslatef(alien->pos[0], alien->pos[1], alien->pos[2]);
		glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);

		glBegin(GL_QUADS);
		if (alien->vel[0] > 0.0) {
			glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
			glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
			glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
		} /*else {
			glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-wid);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
			glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, wid);
			glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-wid);
		}*/
		glEnd();
		glPopMatrix();
		alien = alien->next;
	}
	glDisable(GL_ALPHA_TEST);
}

int checkAliens() 
{
	Alien *node1 = row1_head;
	Alien *node2 = row2_head;
	Alien *node3 = row3_head;

	while (node1->next != NULL) {
                deleted1 = moveAlien1(node1);
                node1 = node1->next;
        }

	while (node2->next != NULL) {
		deleted2 = moveAlien2(node2);
		node2 = node2->next;
	}

	while (node3->next != NULL) {
		deleted3 = moveAlien3(node3);
		node3 = node3->next;
	}

	if (deleted1 == 1 && deleted2 == 1 && deleted3 == 1)
		return 3;

	if ((deleted1 == 1 && deleted2 == 1) ||
		(deleted1 == 1 && deleted3 == 1) ||
		(deleted2 == 1 && deleted3 == 2))
		return 2;

	if (deleted1 == 1 || deleted2 == 1 || deleted3 == 1) 
		return 1;

	return 0;
}

