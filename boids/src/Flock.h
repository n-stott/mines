#ifndef FLOCK_H
#define FLOCK_H

#include "Boid.h"

class Flock {
public:
	std::vector<Boid> boids;

		// Constructor
	Flock();
	// Destructor
	~Flock();


	void draw();
	void move();
};

#endif 
