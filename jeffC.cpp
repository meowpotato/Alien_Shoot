/* No main function is included per instructions, so this file
 * will not compile by itself, it will be built with a makefile
 * into the Alien_Shoot.cpp file
 * 
 * Author: Jeff Cadena
 * CMPS 335 Individual contribution to project
 * Date: Written 4/11/16-Present 
 * Modified 4/27, 5/2, 5/6, 5/22, 5/24, 5/26
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
		void show_muzzle_flash();
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
		int x_velocity;
		int y_velocity;
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
		void set_x(int);
		void set_y(int);
		void set_z(int);
		void set_xvel(int);
		void set_yvel(int);
		int get_x();
		int get_y();
		int get_z();
		int get_xvel();
		int get_yvel();
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

// Display the bullet
void Bullet::show_bullet()
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(45.0, 121.0, 0.0);
	glVertex3f(45, 124.0, 0.0);
	glVertex3f(48.0, 124.0, 0.0);
	glVertex3f(48.0, 121.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();
} 

// Display muzzle flash when the weapon fires
void Weapon::show_muzzle_flash()
{
	// Left half of flash    
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 95.0, 0.0);
	glVertex3f(-20.0, 130.0, 0.0);
	glVertex3f(0.0, 75.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 55.0, 0.0);
	glVertex3f(-20.0, 25.0, 0.0);
	glVertex3f(0.0, 35.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	// Right half of flash    
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(95.0, 95.0, 0.0);
	glVertex3f(115.0, 130.0, 0.0);
	glVertex3f(100.0, 75.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(100.0, 55.0, 0.0);
	glVertex3f(115.0, 25.0, 0.0);
	glVertex3f(100.0, 35.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();
}

// Displays the factory sights
void Weapon::show_fact_sights()
{
	// Show black front sight
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(45.0, 100.0, 0.0);
	glVertex3f(45.0, 110.0, 0.0);
	glVertex3f(55.0, 110.0, 0.0);
	glVertex3f(55.0, 100.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	// Show white dot on front sight 
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(47.0, 103.0, 0.0);
	glVertex3f(47.0, 108.0, 0.0);
	glVertex3f(53.0, 108.0, 0.0);
	glVertex3f(53.0, 103.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	// Show black left rear factory sight
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);		
	glVertex3f(5.0, 100.0, 0.0);
	glVertex3f(10.0, 110.0, 0.0);
	glVertex3f(30.0, 110.0, 0.0);
	glVertex3f(30.0, 100.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();
	
	// Show left part of white U on rear sight 
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 90.0, 0.0);
	glVertex3f(20.0, 105.0, 0.0);
	glVertex3f(25.0, 105.0, 0.0);
	glVertex3f(25.0, 90.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	// Show bottom part of white U on rear sight 
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(25.0, 90.0, 0.0);
	glVertex3f(25.0, 95.0, 0.0);
	glVertex3f(75.0, 95.0, 0.0);
	glVertex3f(75.0, 90.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	// Show black right rear factory sight
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(70.0, 100.0, 0.0);
	glVertex3f(70.0, 110.0, 0.0);
	glVertex3f(90.0, 110.0, 0.0);
	glVertex3f(95.0, 100.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();
	
	
	// Show right part of white U on rear sight 
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(75.0, 90.0, 0.0);
	glVertex3f(75.0, 105.0, 0.0);
	glVertex3f(80.0, 105.0, 0.0);
	glVertex3f(80.0, 90.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();
}

// Displays a rear-view of the weapon
void Weapon::show_weapon()
{
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 95.0, 0.0);
	glVertex3f(5.0, 100.0, 0.0);
	glVertex3f(95.0, 100.0, 0.0);
	glVertex3f(100.0, 95.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	// Show serrations on rear of pistol
	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_LINES);
	glVertex3f(20.0, 70.0, 0.0);
	glVertex3f(80.0, 70.0, 0.0);
	glVertex3f(20.0, 66.0, 0.0);
	glVertex3f(80.0, 66.0, 0.0);
	glVertex3f(20.0, 62.0, 0.0);
	glVertex3f(80.0, 62.0, 0.0);
	glVertex3f(20.0, 58.0, 0.0);
	glVertex3f(80.0, 58.0, 0.0);
	glVertex3f(20.0, 54.0, 0.0);
	glVertex3f(80.0, 54.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();

	glPushMatrix();
	glTranslatef(280,0,0);
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_LINES);
	glVertex3f(10.0, 30.0, 0.0);
	glVertex3f(10.0, 82.0, 0.0);
	glVertex3f(10.0, 30.0, 0.0);
	glVertex3f(90.0, 30.0, 0.0);
	glVertex3f(90.0, 30.0, 0.0);
	glVertex3f(90.0, 82.0, 0.0);
	glVertex3f(10.0, 82.0, 0.0);
	glVertex3f(90.0, 82.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();
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

// Return the x-velocity
int Bullet::get_xvel()
{
	return x_velocity;
}

// Return the y-velocity
int Bullet::get_yvel()
{
	return y_velocity;
}

// Assign the x-coordinate of bullet's position
void Bullet::set_x(int val)
{
	x = val;
}

// Assign the y-coordinate of bullet's position
void Bullet::set_y(int val)
{
	y = val;
}
// Assign the z-coordinate of bullet's position
void Bullet::set_z(int val)
{
	z = val;
}

// Assign the x velocity
void Bullet::set_xvel(int val)
{
	x_velocity = val;
}

// Assign the y velocity
void Bullet::set_yvel(int val)
{
	y_velocity = val;
}

// Return the x-coordinate of target's position
int Target::get_x()
{
	return x;
}

// Return the y-coordinate of target's position
int Target::get_y()
{
	return y;
}
// Return the z-coordinate of target's position
int Target::get_z()
{
	return z;
}

// Assign the x-coordinate of target's position
void Target::set_x(int val)
{
	x = val;
}

// Assign the y-coordinate of target's position
void Target::set_y(int val)
{
	y = val;
}

// Assign the z-coordinate of target's position
void Target::set_z(int val)
{
	z = val;
}

// Assign target's width
void Target::set_width(int val)
{
	width = val;
}

// Assign target's height
void Target::set_height(int val)
{
	height = val;
}

// Return target's width
int Target::get_width()
{
	return width;
}

// Return target's height
int Target::get_height()
{
	return height;
}

// Display the target
void Target::show_target()
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3f(1.0, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0, 8.0, 0.0);
	glVertex3f(16.0, 8.0, 0.0);
	glVertex3f(8.0, 16.0, 0.0);
	glVertex3f(8.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
	glFlush();
}
