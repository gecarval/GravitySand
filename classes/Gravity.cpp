#include "Gravity.hpp"
#include <list>

Gravity::Gravity() {
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
					Vector2 acceleration = direction * force / p1.getMass();
					p1.setAcel(p1.getAcel() + acceleration);
					acceleration = direction * force / p2.getMass();
					p2.setAcel(p2.getAcel() - acceleration);
				}
			}
		}
	}
}

const std::list<Particle> &Gravity::getParticles() {
	return (this->particle);
}

void Gravity::setParticles(const std::list<Particle> &other) {
	this->particle = other;
}
