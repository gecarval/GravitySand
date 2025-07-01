#include "Particle.hpp"

Particle::Particle()
	: type(SAND_PT), color(PART_COLORS[SAND_PT]), pos(Vector2()),
	  vel(Vector2()), acel(Vector2()), mass(PART_MASS[SAND_PT]),
	  density(PART_DENSE[SAND_PT]), fluidity(PART_FLUID[SAND_PT]),
	  temperature(PART_TEMP[SAND_PT]), tempConductivity(PART_COND[SAND_PT]) {
}

Particle::Particle(const int &new_type)
	: type(new_type), color(PART_COLORS[new_type]), pos(Vector2()),
	  vel(Vector2()), acel(Vector2()), mass(PART_MASS[new_type]),
	  density(PART_DENSE[new_type]), fluidity(PART_FLUID[new_type]),
	  temperature(PART_TEMP[new_type]), tempConductivity(PART_COND[new_type]) {
}

Particle::Particle(const int &new_type, const Vector2 &new_pos)
	: type(new_type), color(PART_COLORS[new_type]), pos(new_pos),
	  vel(Vector2()), acel(Vector2()), mass(PART_MASS[new_type]),
	  density(PART_DENSE[new_type]), fluidity(PART_FLUID[new_type]),
	  temperature(PART_TEMP[new_type]), tempConductivity(PART_COND[new_type]) {
}

Particle &Particle::operator=(const Particle &other) {
	if (this != &other) {
		this->setType(other.getType());
		this->setMass(other.getMass());
		this->setColor(other.getColor());
		this->setDensity(other.getDensity());
		this->setFluidity(other.getFluidity());
		this->setTempConductivity(other.getTempConductivity());
	}
	return (*this);
}

Particle::~Particle() {
}

void Particle::update(void) {
	this->vel += this->acel * GetFrameTime();
	this->pos += this->vel * GetFrameTime();
	this->acel = Vector2();
}

const int &Particle::getType(void) const {
	return (this->type);
}

void Particle::setType(const int &data) {
	this->type = data;
}

const Color &Particle::getColor(void) const {
	return (this->color);
}

void Particle::setColor(const Color &data) {
	this->color = data;
}

const Vector2 &Particle::getPos(void) const {
	return (this->pos);
}

void Particle::setPos(const Vector2 &data) {
	this->pos = data;
}

const Vector2 &Particle::getVel(void) const {
	return (this->vel);
}

void Particle::setVel(const Vector2 &data) {
	this->vel = data;
}

const Vector2 &Particle::getAcel(void) const {
	return (this->acel);
}

void Particle::setAcel(const Vector2 &data) {
	this->acel = data;
}

const double_t &Particle::getMass(void) const {
	return (this->mass);
}

void Particle::setMass(const double_t &data) {
	this->mass = data;
}

const double_t &Particle::getDensity(void) const {
	return (this->density);
}

void Particle::setDensity(const double_t &data) {
	this->density = data;
}

const double_t &Particle::getFluidity(void) const {
	return (this->fluidity);
}

void Particle::setFluidity(const double_t &data) {
	this->fluidity = data;
}

const double_t &Particle::getTemperature(void) const {
	return (this->temperature);
}

void Particle::setTemperature(const double_t &data) {
	this->temperature = data;
}

const double_t &Particle::getTempConductivity(void) const {
	return (this->tempConductivity);
}

void Particle::setTempConductivity(const double_t &data) {
	this->tempConductivity = data;
}
