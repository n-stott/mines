#ifndef FLOCK_H
#define FLOCK_H

#include "Boid.h"
#include <vector>

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
