#include "Gravity.hpp"
#include <deque>

Gravity::Gravity() : gravity(1.0) {
}

Gravity::Gravity(const double_t &G) : gravity(G) {
}

Gravity::~Gravity() {
}

void Gravity::attract(std::deque<Particle> &p) {
	if (this->gravity == 0.0) return;
	for (std::deque<Particle>::iterator p1 = p.begin(); p1 != p.cend(); p1++) {
		for (std::deque<Particle>::iterator p2 = p1; p2 != p.cend(); p2++) {
			(*p1).attract(*p2, this->gravity);
		}
	}
}

void Gravity::update(std::deque<Particle> &p) {
	for (std::deque<Particle>::iterator p1 = p.begin(); p1 != p.cend(); p1++) {
		(*p1).update();
	}
}

void Gravity::render(void) {
}

const double_t &Gravity::getGravity() const {
	return (this->gravity);
}

void Gravity::setGravity(const double_t &other) {
	this->gravity = other;
}
