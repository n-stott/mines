#ifndef BOIDS_H
#define BOIDS_H

#include <Eigen/Dense>


class Boid {
public:
	Eigen::Vector3f p;
	Eigen::Vector3f v;
	Eigen::Vector3f a;

	// Constructor
	Boid();
	// Destructor
	~Boid();
	void draw();
};

#endif  // BOIDS_LIB_SAMPLE_CLASS_H_
