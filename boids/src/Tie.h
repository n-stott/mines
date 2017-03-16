#ifndef TIE_H
#define TIE_H

#include <Eigen/Dense>

#include "Boid.h"
#include <cmath>

#include "star_wars_ships.h"

class Tie : public Boid {
public:
	// Constructor
	// Constructor
	Tie() : Boid(), prey{false} {};
	Tie(Eigen::Vector3f pi, Eigen::Vector3f vi, Eigen::Vector3f ai) : Boid(pi,vi,ai), prey{false} {};
	Tie(float i, float e) : Boid(i,e), prey(false) {};

	bool prey = true;

	void draw();
	static int style;
	static void incr_style();
};


#endif