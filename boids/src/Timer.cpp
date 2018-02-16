#include "Timer.h"

int epoch = 0;
int lastTick = 0;
int delta = 0;

Timer* Timer::tr = new Timer();

int Timer::getEpoch(){
	return tr->epoch;
}

int Timer::getLastTick() {
	return tr->lastTick;
}

int Timer::getDelta() {
	return tr->delta;
}

void Timer::update() {
	int t = glutGet(GLUT_ELAPSED_TIME);
	tr->delta = t - tr->lastTick;
	tr->lastTick = t;
}
