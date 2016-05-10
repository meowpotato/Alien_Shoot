/* No main function is included per instructions, so this file
 * will not compile by itself, it will be built with a makefile
 * into the Alien_Shoot.cpp file
 * 
 * Author: Jeff Cadena
 * CMPS 335 Individual contribution to project
 * Date: Written 4/11/16-Present 
 * Modified 4/27/16, 5/2/16, 5/6/16
 * Purpose: Make weapon classes, appropriate child classes
 * using inheritance, and functions that will be called
 * in the main project program Alien_Shoot.cpp.
 * */

#include <iostream>
#include <GL/glu.h>

extern "C" {
#include "fonts.h"
}

using namespace std;

// Global vars
int x_resolution = 1250;
int y_resolution = 900;

class Weapon {
	protected:
		// Coordinates of center
		int x, y, z;
		float angle;
		float color[3];
		// Gun specs
		std::string manufacturer;
		std::string model;
		std::string caliber;
		std::string sights;
		// Signals if this weapon is selected
		bool current_weapon;
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
			current_weapon = false;
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
		std::string get_sights();
		void show_weapon();
		void show_weapon_specs(Rect);
		void show_fact_sights();
};

class Glock : public Weapon {
	public:
		Glock() {
			manufacturer = "Glock";
			model = "";
			caliber = "";
			sights = "Factory Sights";
		}
};

class Sig_Sauer : public Weapon {
	public:
		Sig_Sauer() {
			manufacturer = "Sig Sauer";
			model = "";
			caliber = "";
			sights = "Factory Sights";
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
		// Signals if the bullet makes contact w/ an object
		bool hit_object;
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
			hit_object = false;
		}
		void move();
		int get_x();
		int get_y();
		int get_z();
		void delete_bullet();
};

// Displays the factory sights
void Weapon::show_fact_sights()
{
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(45.0, 100.0, 0.0);
		glVertex3f(45.0, 110.0, 0.0);
		glVertex3f(55.0, 110.0, 0.0);
		glVertex3f(55.0, 100.0, 0.0);
	glEnd();
	glPopMatrix();
}

// Displays a rear-view of the weapon
void Weapon::show_weapon()
{
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 95.0, 0.0);
		glVertex3f(5.0, 100.0, 0.0);
		glVertex3f(95.0, 100.0, 0.0);
		glVertex3f(100.0, 95.0, 0.0);
		glVertex3f(100.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
}

// Display the specifications of the weapon.
// Specs will be placed at the bottom right-hand
// corner as is common in shooter games
void Weapon::show_weapon_specs(Rect r)
{
	// Display weapon manufacturer    
	ggprint8b(&r, 16, 0, "Current Weapon");
	ggprint8b(&r, 16, 0, "==============");

	if (get_manufacturer() == "Glock")
		ggprint8b(&r, 16, 0, "Manufacturer: Glock");
	else if (get_manufacturer() == "Sig Sauer")
		ggprint8b(&r, 16, 0, "Manufacturer: Sig Sauer");
	// Display weapon model
	if (get_model() == "17")
		ggprint8b(&r, 16, 0, "Model: 17");
	else if (get_model() == "30")
		ggprint8b(&r, 16, 0, "Model: 30");
	else if (get_model() == "32")
		ggprint8b(&r, 16, 0, "Model: 32");
	//Display weapon caliber
	if (get_caliber() == "9mm")	
		ggprint8b(&r, 16, 0, "Caliber: 9mm");
	else if (get_caliber() == "0.40")	
		ggprint8b(&r, 16, 0, "Caliber: 0.40");
	else if (get_caliber() == "45 ACP")	
		ggprint8b(&r, 16, 0, "Caliber: 45 ACP");
	else if (get_caliber() == "45 GAP")	
		ggprint8b(&r, 16, 0, "Caliber: 45 GAP");
	//Display weapon sights
	if (get_sights() == "Factory")	
		ggprint8b(&r, 16, 0, "Sights: Factory");
	if (get_sights() == "3 Dot")	
		ggprint8b(&r, 16, 0, "Sights: 3 Dot");
	else if (get_sights() == "Fiberoptic")	
		ggprint8b(&r, 16, 0, "Sights: Fiberoptic");
}

// Assign the manufacturer of the weapon
void Weapon::set_manufacturer(string str)
{
	manufacturer = str;
}

// Assign the model of the weapon
void Weapon::set_model(string str)
{
	model = str;
}

// Assign the caliber of the weapon
void Weapon::set_caliber(string str)
{
	caliber = str;
}

// Assign the sights of the weapon
void Weapon::set_sights(string str)
{
	sights = str;
}

// Return the manufacturer of the weapon
std::string Weapon::get_manufacturer()
{
	return manufacturer;
}

// Return the model of the weapon
std::string Weapon::get_model()
{
	return model;
}

// Return the caliber of the weapon
std::string Weapon::get_caliber()
{
	return caliber;
}

// Return the sights of the weapon
std::string Weapon::get_sights()
{
	return sights;
}

// Return the x-coordinate of bullet's position
int Bullet::get_x()
{
	return x;
}

// Return the y-coordinate of bullet's position
int Bullet::get_y()
{
	return y;
}
// Return the z-coordinate of bullet's position
int Bullet::get_z()
{
	return z;
}
