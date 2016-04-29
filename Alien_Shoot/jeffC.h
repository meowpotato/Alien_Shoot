/*
 * Name: Jeff Cadena
 * CMPS 335 Group Project
 * Purpose: To create wrapper functions that will use
 * the frameworks to enable the creation of more weapon choices 
 * for the user
 *
 * */


#ifndef JEFFC_H
#define JEFFC_H
#endif
Ppmimage *glock17Image=NULL;
GLuint glock17Texture;

void load_weapon_texture();
void load_weapon_image();

void load_weapon_image()
{
	glock17Image = ppm6GetImage("./images/glock_17.ppm");
}


void load_weapon_texture()
{
	//Glock 17 Weapon
	glBindTexture(GL_TEXTURE_2D, glock17Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			glock17Image->width, glock17Image->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, glock17Image->data);
}
