#include "Flock.h"

template <class T>
Flock<T>::Flock() {
	boids = std::vector<T>();
}

// template<class T>
// template<typename T2>
// Flock<T>::operator Flock<T2>()
// {
// return Flock<T2>{p};
// }

template <class T>
Flock<T>::Flock(int n, float b) {
	boids = std::vector<T>();
	for(int i = 0; i < n; ++i) {
		boids.push_back(T(-b,b));
	}
}

template<class T>
Eigen::Vector3f Flock<T>::containment(T const &boid) {
	return boid.steer(-boid.p);
}

template <class T>
Eigen::Vector3f Flock<T>::separation(T const &boid) {
	Eigen::Vector3f v(0,0,0);
	int count = 0;
	for(T& b : boids) {
		float d = boid.d(b);
		if (d > 0 && d < boid.r_sep && boid.sees(b)) {
			v += (boid.p - b.p) / d;
			count++;
		}
	}
	if (count > 0) return boid.steer(v); else return 0*v;
}


template <class T>
Eigen::Vector3f Flock<T>::alignment(T const &boid) {
	Eigen::Vector3f v(0,0,0);
	int count = 0;
	for(T& b : boids) {
		float d = boid.d(b);
		if (d > 0.01 && d < boid.r_align && boid.sees(b)) {
			v += b.v;
			count++;
		}
	}
	if (count > 0) return boid.steer(v); else return 0*v;
}

template <class T>
Eigen::Vector3f Flock<T>::cohesion(T const &boid) {
	Eigen::Vector3f v(0,0,0);
	int count = 0;
	for(T& b : boids) {
		float d = boid.d(b);
		if (d > 0.01 && d < boid.r_cohe && boid.sees(b)) {
			v += b.p;
			count++;
		}
	}
	if (count > 0) return boid.steer(v); else return 0*v;
}

template <class T>
template <class T2>
Eigen::Vector3f Flock<T>::target(T const &boid, Flock<T2> &e) {
	Eigen::Vector3f v(0,0,0);
	float w = 1000;
	for(T2& b : e.boids) {
		float sd = boid.d(b);
		if (sd < w && !boid.prey) { w = sd; v = b.p - boid.p; }
	}
	v = boid.steer(v);
	return v;
}

// template Eigen::Vector3f Flock<Xwing>::target<Tie>(Xwing&, Flock<Tie>&);


template <class T>
template <class T2>
Eigen::Vector3f Flock<T>::dodge(T const &boid, Flock<T2> &e) {
	Eigen::Vector3f v(0,0,0);
	float w = 0;
	for(T2& b : e.boids) {
		float d = boid.d(b);
		v += (d  < boid.r_cohe) * (boid.p - b.p);
	}
	if (boid.prey) return limit(v,boid.max_speed); else return 0*v;
}

template <class T>
template <class T2>
void Flock<T>::move(float dt, Flock<T2> &e) {
	for(T& b : boids) {
		Eigen::Vector3f ac = cohesion(b);
		Eigen::Vector3f as = separation(b);
		Eigen::Vector3f aa = alignment(b);
		Eigen::Vector3f at = target(b, e);
		Eigen::Vector3f ad = dodge(b, e);
		Eigen::Vector3f ap = 0*containment(b);

		//std::cout << ac.norm() << std::endl;
		//std::cout << ac << "  " << as << "  " << aa << std::endl;

		Eigen::Vector3f a = 
		ac+as+aa+ap
		//+at
		//+ad
		;

		b.move(a,dt);

		b.contain(5);
	}
}

template void Flock<Xwing>::move<Tie>(float, Flock<Tie>&);
template void Flock<Tie>::move<Xwing>(float, Flock<Xwing>&);


template <class T>
void Flock<T>::draw() {
	for(T& b : boids) {
		b.draw();
	}
}

template class Flock<Boid>;
template class Flock<Xwing>;
template class Flock<Tie>;

