//Author: Sabrina Smith
//Class: CMPS 335
//Purpose: Lab 5 - Work on project material
//	   Loading images and textures outside of main.cpp file	   
//Modified: 5/2/16


#include "sabrinaS.h"
#include "common.h"

int tothumans = 0;
int totaliens = 0;
int deleted1 = 0;
int deleted2 = 0;
int deleted3 = 0;
int deleted4 = 0;
int deleted5 = 0;
int deleted6 = 0;
Alien *row1HeadAlien = NULL;
Alien *row2HeadAlien = NULL;
Alien *row3HeadAlien = NULL;
Human *row1HeadHuman = NULL;
Human *row2HeadHuman = NULL;
Human *row3HeadHuman = NULL;

float wid = 32.0f;
Ppmimage *bigfootImage=NULL;
Ppmimage *alienImage=NULL;
Ppmimage *humanImage=NULL;
Ppmimage *forestImage=NULL;
Ppmimage *backgroundImage=NULL;
Ppmimage *curtainsImage=NULL;
Ppmimage *levelsImage=NULL;
Ppmimage *umbrellaImage=NULL;
Ppmimage *mainMenuImage=NULL;
Ppmimage *pauseMenuImage=NULL;
Ppmimage *dashImage=NULL;
Ppmimage *gameOverImage=NULL;
Ppmimage *glock30Image=NULL;
Ppmimage *glock17Image=NULL;
GLuint bigfootTexture;
GLuint alienTexture;
GLuint humanTexture;
GLuint alienSilhouetteTexture;
GLuint humanSilhouetteTexture;
GLuint forestTexture;
GLuint levelsTexture;
GLuint backgroundTexture;
GLuint mainMenuTexture;
GLuint pauseMenuTexture;
GLuint dashTexture;
GLuint gameOverTexture;
GLuint glock30Texture;
GLuint glock17Texture;
GLuint curtainsTexture;
GLuint umbrellaTexture;

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

void loadImages() 
{
	alienImage       = ppm6GetImage("./images/alien.ppm");
	humanImage       = ppm6GetImage("./images/human.ppm");
	levelsImage	 = ppm6GetImage("./images/levels.ppm");
	backgroundImage  = ppm6GetImage("./images/background.ppm");
	mainMenuImage    = ppm6GetImage("./images/mainMenu.ppm");
	pauseMenuImage   = ppm6GetImage("./images/pauseMenu.ppm");
	dashImage 	 = ppm6GetImage("./images/dash.ppm");
	gameOverImage  	 = ppm6GetImage("./images/gameOver.ppm");
	glock30Image     = ppm6GetImage("./images/glock_30.ppm");
	glock17Image     = ppm6GetImage("./images/glock_17.ppm");
	curtainsImage    = ppm6GetImage("./images/curtains1.ppm");
}

void loadTextures() 
{
	glGenTextures(1, &alienTexture);
	glGenTextures(1, &humanTexture);
	glGenTextures(1, &backgroundTexture);
	glGenTextures(1, &alienSilhouetteTexture);
	glGenTextures(1, &humanSilhouetteTexture);
	glGenTextures(1, &levelsTexture);
	glGenTextures(1, &curtainsTexture);
	glGenTextures(1, &mainMenuTexture);
	glGenTextures(1, &pauseMenuTexture);
	glGenTextures(1, &dashTexture);
	glGenTextures(1, &gameOverTexture);
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
	//human
	//
	//
	glBindTexture(GL_TEXTURE_2D, humanTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	w = humanImage->width;
	h = humanImage->height;
	ftData = buildAlphaData(humanImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);
	//-------------------------------------------------------------------------
	//
	//alien silhouette
	//this is similar to a sprite graphic
	//
	glBindTexture(GL_TEXTURE_2D, alienSilhouetteTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	unsigned char *alienSilhouetteData = buildAlphaData(alienImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, alienSilhouetteData);
	free(alienSilhouetteData);
	//-------------------------------------------------------------------------
	//
	//human silhouette
	//this is similar to a sprite graphic
	//
	glBindTexture(GL_TEXTURE_2D, humanSilhouetteTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	unsigned char *humanSilhouetteData = buildAlphaData(humanImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, humanSilhouetteData);
	free(humanSilhouetteData);
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
	//game over
	glBindTexture(GL_TEXTURE_2D, gameOverTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			gameOverImage->width, gameOverImage->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, gameOverImage->data);

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
	//dash
	//
	glBindTexture(GL_TEXTURE_2D, dashTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	w = dashImage->width;
	h = dashImage->height;
	ftData = buildAlphaData(dashImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);

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
        //printf("alien created\n");
        node->prev = NULL;
        node->next = NULL;
        node->pos[0] = -100.0 + (rand() % 5);
        node->pos[1] = 365.0;
        node->vel[0] = rand() % 5 + 1;
        node->vel[1] = 0.0;
        node->next = row1HeadAlien;
        if (row1HeadAlien != NULL)
                row1HeadAlien->prev = node;
        row1HeadAlien = node;
        ++totaliens;
        //printf("number of aliens:%d\n", totaliens);
        return totaliens;
}


int createAliens2() 
{
	Alien *node = (Alien *)malloc(sizeof(Alien));
	//printf("alien created\n");
	node->prev = NULL;
	node->next = NULL;
	node->pos[0] = -100.0 + (rand() % 5);
	node->pos[1] = 270.0;
	node->vel[0] = rand() % 5 + 3;
	node->vel[1] = 0.0;
	node->next = row2HeadAlien;
	if (row2HeadAlien != NULL)
		row2HeadAlien->prev = node;
	row2HeadAlien = node;
	++totaliens;
	//printf("number of aliens:%d\n", totaliens);
	return totaliens;
}

int createAliens3() 
{
	Alien *node = (Alien *)malloc(sizeof(Alien));
	//printf("alien created\n");
	node->prev = NULL;
	node->next = NULL;
	node->pos[0] = -100.0 + (rand() % 5);
	node->pos[1] = 175.0;
	node->vel[0] = rand() % 5 + 5;
	node->vel[1] = 0.0;
	node->next = row3HeadAlien;
	if (row3HeadAlien != NULL)
		row3HeadAlien->prev = node;
	row3HeadAlien = node;
	++totaliens;
	//printf("number of aliens:%d\n", totaliens);
	return totaliens;
}

int createHumans1()
{
        Human *node = (Human *)malloc(sizeof(Human));
        //printf("alien created\n");
        node->prev = NULL;
        node->next = NULL;
        node->pos[0] = -100.0 + (rand() % 5);
        node->pos[1] = 365.0;
        node->vel[0] = rand() % 5 ;
        node->vel[1] = 0.0;
        node->next = row1HeadHuman;
        if (row1HeadHuman != NULL)
                row1HeadHuman->prev = node;
        row1HeadHuman = node;
        ++tothumans;
        //printf("number of aliens:%d\n", totaliens);
        return tothumans;
}


int createHumans2()
{
        Human *node = (Human *)malloc(sizeof(Human));
        //printf("alien created\n");
        node->prev = NULL;
        node->next = NULL;
        node->pos[0] = -100.0 + (rand() % 5);
        node->pos[1] = 270.0;
        node->vel[0] = rand() % 5 + 2;
        node->vel[1] = 0.0;
        node->next = row2HeadHuman;
        if (row2HeadHuman != NULL)
                row2HeadHuman->prev = node;
        row2HeadHuman = node;
        ++tothumans;
        //printf("number of aliens:%d\n", totaliens);
        return tothumans;
}

int createHumans3()
{
        Human *node = (Human *)malloc(sizeof(Human));
        //printf("alien created\n");
        node->prev = NULL;
        node->next = NULL;
        node->pos[0] = -100.0 + (rand() % 5);
        node->pos[1] = 175.0;
        node->vel[0] = rand() % 5 + 3;
        node->vel[1] = 0.0;
        node->next = row3HeadHuman;
        if (row3HeadHuman != NULL)
                row3HeadHuman->prev = node;
        row3HeadHuman = node;
        ++tothumans;
        //printf("number of aliens:%d\n", totaliens);
        return tothumans;
}

void deleteAlien1(Alien *currentAlien)
{
        if (currentAlien->prev == NULL) {
                if (currentAlien->next == NULL) {
                        row1HeadAlien = NULL;
                }
                else {
                        currentAlien->next->prev = NULL;
                        row1HeadAlien = currentAlien->next;
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
        //printf("Alien deleted\n");
}

void deleteAlien2(Alien *currentAlien) 
{
	if (currentAlien->prev == NULL) {
		if (currentAlien->next == NULL) {
			row2HeadAlien = NULL;
		}
		else {
			currentAlien->next->prev = NULL;
			row2HeadAlien = currentAlien->next;
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
	//printf("Alien deleted\n");
}

void deleteAlien3(Alien *currentAlien) 
{
	if (currentAlien->prev == NULL) {
		if (currentAlien->next == NULL) {
			row3HeadAlien = NULL;
		}
		else {
			currentAlien->next->prev = NULL;
			row3HeadAlien = currentAlien->next;
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
	//printf("Alien deleted\n");
}

void deleteHuman1(Human *currentHuman)
{
        if (currentHuman->prev == NULL) {
                if (currentHuman->next == NULL) {
                        row1HeadHuman = NULL;
                }
                else {
                        currentHuman->next->prev = NULL;
                        row1HeadHuman = currentHuman->next;
                }
        }

        else {
                if (currentHuman->next == NULL) {
                        currentHuman->prev->next = NULL;
                }
                else {
                        currentHuman->prev->next = currentHuman->next;
                        currentHuman->next->prev = currentHuman->prev;
                }
        }

        free(currentHuman);
        currentHuman = NULL;
        --tothumans;
        //printf("Alien deleted\n");
}

void deleteHuman2(Human *currentHuman)
{
        if (currentHuman->prev == NULL) {
                if (currentHuman->next == NULL) {
                        row2HeadHuman = NULL;
                }
                else {
                        currentHuman->next->prev = NULL;
                        row2HeadHuman = currentHuman->next;
                }
        }       
                
        else {  
                if (currentHuman->next == NULL) {
                        currentHuman->prev->next = NULL;
                }
                else {  
                        currentHuman->prev->next = currentHuman->next;
                        currentHuman->next->prev = currentHuman->prev;
                }       
        }

        free(currentHuman);
        currentHuman = NULL;
        --tothumans;
        //printf("Alien deleted\n");
}

void deleteHuman3(Human *currentHuman)
{
        if (currentHuman->prev == NULL) {
                if (currentHuman->next == NULL) {
                        row3HeadHuman = NULL;
                }
                else {
                        currentHuman->next->prev = NULL;
                        row3HeadHuman = currentHuman->next;
                }
        }       
                
        else {  
                if (currentHuman->next == NULL) {
                        currentHuman->prev->next = NULL;
                }
                else {  
                        currentHuman->prev->next = currentHuman->next;
                        currentHuman->next->prev = currentHuman->prev;
                }       
        }

        free(currentHuman);
        currentHuman = NULL;
        --tothumans;
        //printf("Alien deleted\n");
}

int moveAlien1(Alien *alien, Bullet *bullet, int *score)
{
        //move alien...
        //Update position
        alien->pos[0] += alien->vel[0];
        
	//Check for collision with window edges
        if ((alien->pos[0] >= (float)xres+140.0 
		&& alien->vel[0] > 0.0) && alien->pos[1] ==  365.0) {
                deleteAlien1(alien);
                return 1;
        }

	if ((bullet->get_x() < alien->pos[0]) 
			&& (bullet->get_x() > alien->pos[0] - wid)
			&& (yres-(bullet->get_y()) > alien->pos[1]) 
			&& (yres-(bullet->get_y()) < alien->pos[1] + wid)) {
			printf("ALIEN HIT!\n");
			printf("ALIEN POS[0] = %f\n", alien->pos[0]);
			*score = *score + 50;
			deleteAlien1(alien);
			return 1;
	}
        
	return 0;
}

int moveAlien2(Alien *alien, Bullet *bullet, int *score)
{
	//move alien...
	//Update position
	alien->pos[0] += alien->vel[0];
	
	//Check for collision with window edges
	if ((alien->pos[0] >= (float)xres+140.0 
		&& alien->vel[0] > 0.0) && alien->pos[1] ==  270.0) {
		deleteAlien2(alien);
		return 1;
	}
	
	if ((bullet->get_x() <= alien->pos[0]) 
			&& (bullet->get_x() >= alien->pos[0] - wid)
			&& (yres-(bullet->get_y()) >= alien->pos[1]) 
			&& (yres-(bullet->get_y()) <= alien->pos[1] + wid)) {
			printf("ALIEN HIT!\n");
			printf("ALIEN POS[0] = %f\n", alien->pos[0]);
			*score = *score + 50;
			deleteAlien2(alien);
		return 1;
	}

	return 0;
}

int moveAlien3(Alien *alien, Bullet *bullet, int *score)
{
	//move alien...
	//Update position
	alien->pos[0] += alien->vel[0];
	
	//Check for collision with window edges
	if ((alien->pos[0] >= (float)xres+140.0 
		&& alien->vel[0] > 0.0) && alien->pos[1] == 175.0) {
		deleteAlien3(alien);
		return 1;
	}
	
	if ((bullet->get_x() <= alien->pos[0]) 
			&& (bullet->get_x() >= alien->pos[0] - wid)
			&& (yres-(bullet->get_y()) >= alien->pos[1]) 
			&& (yres-(bullet->get_y()) <= alien->pos[1] + wid)) {
			printf("ALIEN HIT!\n");
			printf("ALIEN POS[0] = %f\n", alien->pos[0]);
			*score = *score + 50;
			deleteAlien3(alien);
		return 1;
	}
	return 0;
}

int moveHuman1(Human *human, Bullet *bullet, int *lives)
{
        //move human...
        //Update position
        human->pos[0] += human->vel[0];

        //Check for collision with window edges
        if ((human->pos[0] >= (float)xres+140.0
                && human->vel[0] > 0.0) && human->pos[1] ==  365.0) {
                deleteHuman1(human);
                return 1;
        }

        if ((bullet->get_x() < human->pos[0])
                        && (bullet->get_x() > human->pos[0] - wid)
                        && (yres-(bullet->get_y()) > human->pos[1])
                        && (yres-(bullet->get_y()) < human->pos[1] + wid)) {
                        printf("HUMAN HIT!\n");
                        printf("HUMAN POS[0] = %f\n", human->pos[0]);
                        *lives = *lives - 1;
                        deleteHuman1(human);
                        return 1;
        }

        return 0;
}

int moveHuman2(Human *human, Bullet *bullet, int *lives)
{
        //move human...
        //Update position
        human->pos[0] += human->vel[0];

        //Check for collision with window edges
        if ((human->pos[0] >= (float)xres+140.0
                && human->vel[0] > 0.0) && human->pos[1] ==  270.0) {
                deleteHuman2(human);
                return 1;
        }

        if ((bullet->get_x() < human->pos[0])
                        && (bullet->get_x() > human->pos[0] - wid)
                        && (yres-(bullet->get_y()) > human->pos[1])
                        && (yres-(bullet->get_y()) < human->pos[1] + wid)) {
                        printf("HUMAN HIT!\n");
                        printf("HUMAN POS[0] = %f\n", human->pos[0]);
                        *lives = *lives - 1;
                        deleteHuman2(human);
                        return 1;
        }

        return 0;
}

int moveHuman3(Human *human, Bullet *bullet, int *lives)
{
        //move human...
        //Update position
        human->pos[0] += human->vel[0];

        //Check for collision with window edges
        if ((human->pos[0] >= (float)xres+140.0
                && human->vel[0] > 0.0) && human->pos[1] ==  175.0) {
                deleteHuman3(human);
                return 1;
        }

        if ((bullet->get_x() < human->pos[0])
                        && (bullet->get_x() > human->pos[0] - wid)
                        && (yres-(bullet->get_y()) > human->pos[1])
                        && (yres-(bullet->get_y()) < human->pos[1] + wid)) {
                        printf("HUMAN HIT!\n");
                        printf("HUMAN POS[0] = %f\n", human->pos[0]);
                        *lives = *lives - 1;
                        deleteHuman3(human);
                        return 1;
        }

        return 0;
}

void drawAliens1(void) {
        Alien *alien = row1HeadAlien;
        float wid = 32.0f;
        while(alien){
                glPushMatrix();
                glTranslatef(alien->pos[0], alien->pos[1], alien->pos[2]);
                glBindTexture(GL_TEXTURE_2D, alienSilhouetteTexture);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glColor4ub(255,255,255,255);

                glBegin(GL_QUADS);
                if (alien->vel[0] > 0.0) {
                        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
                        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
                        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
                        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
                } 
                glEnd();
                glPopMatrix();
                alien = alien->next;
        }
        glDisable(GL_ALPHA_TEST);
}

void drawAliens2(void) {
	Alien *alien = row2HeadAlien;
	float wid = 32.0f;
	while(alien){
		glPushMatrix();
		glTranslatef(alien->pos[0], alien->pos[1], alien->pos[2]);
		glBindTexture(GL_TEXTURE_2D, alienSilhouetteTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);

		glBegin(GL_QUADS);
		if (alien->vel[0] > 0.0) {
			glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
			glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
			glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
		} 
		glEnd();
		glPopMatrix();
		alien = alien->next;
	}
	glDisable(GL_ALPHA_TEST);
}

void drawAliens3(void) {
	Alien *alien = row3HeadAlien;
	while(alien){
		glPushMatrix();
		glTranslatef(alien->pos[0], alien->pos[1], alien->pos[2]);
		glBindTexture(GL_TEXTURE_2D, alienSilhouetteTexture);
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

void drawHumans1(void) {
        Human *human = row1HeadHuman;
        float wid = 32.0f;
        while(human){
                glPushMatrix();
                glTranslatef(human->pos[0], human->pos[1], human->pos[2]);
                glBindTexture(GL_TEXTURE_2D, humanSilhouetteTexture);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glColor4ub(255,255,255,255);

                glBegin(GL_QUADS);
                if (human->vel[0] > 0.0) {
                        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
                        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
                        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
                        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
                } 
                glEnd();
                glPopMatrix();
                human = human->next;
        }
        glDisable(GL_ALPHA_TEST);
}

void drawHumans2(void) {
        Human *human = row2HeadHuman;
        float wid = 32.0f;
        while(human){
                glPushMatrix();
                glTranslatef(human->pos[0], human->pos[1], human->pos[2]);
                glBindTexture(GL_TEXTURE_2D, humanSilhouetteTexture);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glColor4ub(255,255,255,255);

                glBegin(GL_QUADS);
                if (human->vel[0] > 0.0) {
                        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
                        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
                        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
                        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
                }
                glEnd();
                glPopMatrix();
                human = human->next;
        }
        glDisable(GL_ALPHA_TEST);
}

void drawHumans3(void) {
        Human *human = row3HeadHuman;
        float wid = 32.0f;
        while(human){
                glPushMatrix();
                glTranslatef(human->pos[0], human->pos[1], human->pos[2]);
                glBindTexture(GL_TEXTURE_2D, humanSilhouetteTexture);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glColor4ub(255,255,255,255);

                glBegin(GL_QUADS);
                if (human->vel[0] > 0.0) {
                        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
                        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
                        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
                        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
                }
                glEnd();
                glPopMatrix();
                human = human->next;
        }
        glDisable(GL_ALPHA_TEST);
}

int checkAliens(Bullet *bullet, int *score) 
{
	Alien *node1 = row1HeadAlien;
	Alien *node2 = row2HeadAlien;
	Alien *node3 = row3HeadAlien;

	while (node1->next != NULL) {
                deleted1 = moveAlien1(node1, bullet, score);
                node1 = node1->next;
        }

	while (node2->next != NULL) {
		deleted2 = moveAlien2(node2, bullet, score);
		node2 = node2->next;
	}

	while (node3->next != NULL) {
		deleted3 = moveAlien3(node3, bullet, score);
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

int checkHumans(Bullet *bullet, int *lives)
{
        Human *node1 = row1HeadHuman;
        Human *node2 = row2HeadHuman;
        Human *node3 = row3HeadHuman;

        while (node1->next != NULL) {
                deleted4 = moveHuman1(node1, bullet, lives);
                node1 = node1->next;
        }

        while (node2->next != NULL) {
                deleted5 = moveHuman2(node2, bullet, lives);
                node2 = node2->next;
        }

        while (node3->next != NULL) {
                deleted6 = moveHuman3(node3, bullet, lives);
                node3 = node3->next;
        }

        if (deleted4 == 1 && deleted5 == 1 && deleted6 == 1)
                return 3;

        if ((deleted4 == 1 && deleted5 == 1) ||
                (deleted4 == 1 && deleted6 == 1) ||
                (deleted5 == 1 && deleted6 == 2))
                return 2;

        if (deleted4 == 1 || deleted5 == 1 || deleted6 == 1)
                return 1;

        return 0;
}

