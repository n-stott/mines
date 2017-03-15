#ifndef XWING_H
#define XWING_H

#include <Eigen/Dense>

#include "Boid.h"

#include "star_wars_ships.h"


class Xwing : public Boid {
public:
	// Constructor
	Xwing() : Boid(), prey{false} {};
	Xwing(Eigen::Vector3f pi, Eigen::Vector3f vi, Eigen::Vector3f ai) : Boid(pi,vi,ai), prey{false} {};
	Xwing(float i, float e) : Boid(i,e), prey(false) {};

	bool prey;
	
	void draw();
	
	
};

#endif