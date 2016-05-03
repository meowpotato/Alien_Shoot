/* No main function is included per instructions, so this file
 * will not compile by itself, it will be built with a makefile
 * into the Alien_Shoot.cpp file
 * 
 * Author: Jeff Cadena
 * CMPS 335 Individual contribution to project
 * Date: Written 4/11/16-5/3/16, modified 4/27/16, 
 * modified 5/2/16
 * Purpose: Make weapon classes, appropriate child classes
 * using inheritance, and functions that will be called
 * in the main project program Alien_Shoot.cpp
 * */

#include <iostream>
#include "jeffC.h"

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
		std::string get_manufacturer();
		std::string get_model();
		std::string get_caliber();
		void show_weapon_specs(Rect);

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

// Display the specifications of the weapon
void Weapon::show_weapon_specs(Rect r)
{
	ggprint8b(&r, 16, 0, "Current Weapon");
	ggprint8b(&r, 16, 0, "==============");
	ggprint8b(&r, 16, 0, "Manufacturer: Glock");
	ggprint8b(&r, 16, 0, "Model: 30");
	ggprint8b(&r, 16, 0, "Caliber: 45ACP");
}



// Set the manufacturer of the weapon
void Weapon::set_manufacturer(string str)
{
	manufacturer = str;
}

// Set the model of the weapon
void Weapon::set_model(string str)
{
	model = str;
}

// Set the caliber of the weapon
void Weapon::set_caliber(string str)
{
	caliber = str;
}

// Get the manufacturer of the weapon
std::string Weapon::get_manufacturer()
{
	return manufacturer;
}

// Get the model of the weapon
std::string Weapon::get_model()
{
	return model;
}

// Get the caliber of the weapon
std::string Weapon::get_caliber()
{
	return caliber;
}

// Get the x-coordinate of bullet's position
int Bullet::get_x()
{
	return x;
}

// Get the y-coordinate of bullet's position
int Bullet::get_y()
{
	return y;
}
// Get the z-coordinate of bullet's position
int Bullet::get_z()
{
	return z;
}
