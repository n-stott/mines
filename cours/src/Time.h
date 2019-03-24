#ifndef TIME_H
#define TIME_H

struct Time {
	float t = 0;
	float last_t = 0;
	float dt = 0;

	void update(float new_t) {
		last_t = t;
		t = new_t;
		dt = (t - last_t)*0.001;
	}
};

#endif