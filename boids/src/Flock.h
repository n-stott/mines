#ifndef FLOCK_H
#define FLOCK_H

#include <iostream>

#include <vector>
#include "math_u.h"
#include <Eigen/Dense>

#include "Boid.h"
#include "Xwing.h"
#include "Tie.h"

template <class T>
class Flock {
public:
	// Constructor
	Flock();
	Flock(int n, float b);
	
	std::vector<T> boids;

	template<typename T2>
	operator Flock<T2>();

	Eigen::Vector3f containment(T const &b);

	Eigen::Vector3f separation(T const &b);
	Eigen::Vector3f alignment(T const &b);
	Eigen::Vector3f cohesion(T const &b);

	template<class T2>
	Eigen::Vector3f target(T const &b, Flock<T2> &e);

	template<class T2>
	Eigen::Vector3f dodge(T const &b, Flock<T2> &e);

	template<class T2>
	void move(float dt, Flock<T2> &e);

	void draw();

	
};

#endif 