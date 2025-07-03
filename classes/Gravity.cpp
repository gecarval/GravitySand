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
	for (auto &p1 : this->particle) {
		for (auto &p2 : this->particle) {
			if (&p1 != &p2) {
				Vector2	 direction = p2.getPos() - p1.getPos();
				double_t distance = Vector2Length(direction);
				if (distance > 0) {
					direction = Vector2Normalize(direction);
					double_t force =
						(p1.getMass() * p2.getMass()) / (distance * distance);
					force *= this->gravity;
					Vector2 acceleration = direction * force / p1.getMass();
					p1.setAcel(p1.getAcel() + acceleration);
					acceleration = direction * force / p2.getMass();
					p2.setAcel(p2.getAcel() - acceleration);
				}
			}
		}
	}
}

void Gravity::update() {
	for (auto &p : this->particle) {
		p.update();
	}
}

void Gravity::render() {
	for (const auto &p : this->particle) {
		p.render();
	}
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
