#ifndef MATH_U_H
#define MATH_U_H

#include <cstdlib>
#include <Eigen/Dense>

float rand(float a, float b);

float smooth(float d, float ri, float re);

float sat(float x, float l, float u);

float loop(float x, float l, float u);

Eigen::Vector3f limit(Eigen::Vector3f v, float l);

Eigen::Vector3f set_mag(Eigen::Vector3f v, float l);

#endif