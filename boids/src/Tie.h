#ifndef TIE_H
#define TIE_H

#include <Eigen/Dense>

#include "Boid.h"

#include "star_wars_ships.h"

class Tie : public Boid {
public:
	// Constructor
	using Boid::Boid;

	bool prey = true;

	void draw();
	
	
};

#endif