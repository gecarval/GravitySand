#include "Gravity.hpp"
#include <deque>

Gravity::Gravity(std::deque<Particle> &p) : particle(p), gravity(1.0) {
}

Gravity::Gravity(std::deque<Particle> &p, const double_t &G)
	: particle(p), gravity(G) {
}

Gravity::~Gravity() {
}

void Gravity::attract() {
	if (this->gravity == 0.0) return;
	for (std::deque<Particle>::iterator p1 = this->particle.begin();
		 p1 != this->particle.cend(); p1++) {
		for (std::deque<Particle>::iterator p2 = p1;
			 p2 != this->particle.cend(); p2++) {
			(*p1).attract(*p2, this->gravity);
		}
	}
}

void Gravity::update() {
	for (std::deque<Particle>::iterator p = this->particle.begin();
		 p != this->particle.cend(); p++) {
		(*p).update();
	}
}

void Gravity::render(void) {
}

const std::deque<Particle> &Gravity::getParticles() const {
	return (this->particle);
}

void Gravity::setParticles(std::deque<Particle> &other) {
	this->particle = other;
}

const double_t &Gravity::getGravity() const {
	return (this->gravity);
}

void Gravity::setGravity(const double_t &other) {
	this->gravity = other;
}
