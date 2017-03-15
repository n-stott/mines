#include "math_u.h"

float rand(float a, float b) {
	return a + (b-a)*((float) std::rand()) / RAND_MAX;
}

float smooth(float d, float ri, float re) {
	return (d < re)*( (d < ri) ? 1 : (re-d)/(re-ri) );
}

float sat(float x, float l, float u) {
	return (x < l) ? l : ( (x > u) ? u : x ); 
}

float loop(float x, float l, float u) {
	return (x < l) ? u : ( (x > u) ? l : x ); 
}

Eigen::Vector3f limit(Eigen::Vector3f v, float l) {
	if (v.norm() > l) {
		v = v.normalized()*l;
	}
	return v;
}

Eigen::Vector3f set_mag(Eigen::Vector3f v, float l) {
	return v = v.normalized()*l;
}