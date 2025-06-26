#include "Particle.hpp"

Particle::Particle(const int &type) {
	this->type = type;
	this->color = PART_COLORS[type];
	this->pos = Vector2();
	this->vel = Vector2();
	this->acel = Vector2();
	this->density = 1.0;
	this->temperature = 0.0;
	this->viscocity = 1.0;
}

Particle::Particle(const int &type, const Vector2 &pos) {
	this->type = type;
	this->color = PART_COLORS[type];
	this->pos = pos;
	this->vel = Vector2();
	this->acel = Vector2();
	this->density = 1.0;
	this->temperature = 0.0;
	this->viscocity = 1.0;
}

Particle &Particle::operator=(const Particle &other) {
	if (this != &other) {
		this->type = other.type;
		this->color = other.color;
		this->pos = other.pos;
		this->vel = other.vel;
		this->acel = other.acel;
		this->density = other.density;
		this->temperature = other.temperature;
		this->viscocity = other.viscocity;
	}
	return (*this);
}

Particle::~Particle() {
}
