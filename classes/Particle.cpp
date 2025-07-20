#include "Particle.hpp"

Particle::Particle()
    : type(SAND_PT), color(PART_COLORS[SAND_PT]), pos(Vector2()),
      vel(Vector2()), acel(Vector2()), mass(PART_MASS[SAND_PT]),
      density(PART_DENSE[SAND_PT]), fluidity(PART_FLUID[SAND_PT]),
      temperature(PART_TEMP[SAND_PT]), tempConductivity(PART_COND[SAND_PT]),
      size((Rectangle){0, 0, PART_SIZE, PART_SIZE}) {}

Particle::Particle(const int &new_type)
    : color(PART_COLORS[new_type]), pos(Vector2()), vel(Vector2()),
      acel(Vector2()), mass(PART_MASS[new_type]), density(PART_DENSE[new_type]),
      fluidity(PART_FLUID[new_type]), temperature(PART_TEMP[new_type]),
      tempConductivity(PART_COND[new_type]),
      size((Rectangle){0, 0, PART_SIZE, PART_SIZE}) {
  this->type = new_type;
}

Particle::Particle(const int &new_type, const Vector2 &new_pos)
    : color(PART_COLORS[new_type]), vel(Vector2()), acel(Vector2()),
      mass(PART_MASS[new_type]), density(PART_DENSE[new_type]),
      fluidity(PART_FLUID[new_type]), temperature(PART_TEMP[new_type]),
      tempConductivity(PART_COND[new_type]),
      size((Rectangle){new_pos.x, new_pos.y, PART_SIZE, PART_SIZE}) {
  this->type = new_type;
  this->pos = new_pos;
}

Particle &Particle::operator=(const Particle &other) {
  if (this != &other) {
    this->type = other.type;
    this->mass = other.mass;
    this->color = other.color;
    this->density = other.density;
    this->fluidity = other.fluidity;
    this->tempConductivity = other.tempConductivity;
  }
  return (*this);
}

Particle::~Particle() {}

void Particle::update(void) {
  this->vel += this->acel * GetFrameTime();
  this->pos += this->vel * GetFrameTime();
  this->size.x = this->pos.x;
  this->size.y = this->pos.y;
  this->acel = Vector2();
}

void Particle::render(void) const { DrawRectangleRec(this->size, this->color); }

// Draw Relative to the camera2D target Vector2D
void Particle::renderAt(const Camera2D &c) const {
  const float posX = (this->size.x - c.target.x) * c.zoom + c.offset.x;
  const float posY = (c.target.y - this->size.y) * c.zoom + c.offset.y;
  const float width = this->size.width * c.zoom;
  const float height = this->size.height * c.zoom;
  const Rectangle rec = (Rectangle){posX, posY, width, height};
  DrawRectangleRec(rec, this->color);
}

void Particle::attract(Particle &other, const double_t &G) {
  if (this != &other) {
    Vector2 direction = other.pos - this->pos;
    double_t distance = Vector2Length(direction);
    if (distance > 1) {
      direction = Vector2Normalize(direction);
      double_t force = (this->mass * other.mass) / (distance * distance);
      force *= G;
      Vector2 acceleration = direction * force / this->mass;
      this->acel = this->acel + acceleration;
      acceleration = direction * force / other.mass;
      other.acel = other.acel - acceleration;
    }
  }
}

void Particle::attract(const Vector2 &v, const double_t &m, const double_t &G) {
  Vector2 direction = v - this->pos;
  double_t distance = Vector2Length(direction);
  if (distance > 1) {
    direction = Vector2Normalize(direction);
    double_t force = (this->mass * m) / (distance * distance);
    force *= G;
    Vector2 acceleration = direction * force / this->mass;
    this->acel = this->acel + acceleration;
  }
}

void Particle::intersect(const Particle &other) const {
  GetCollisionRec(this->size, other.size);
}

void Particle::setNewType(const int &data) {
  this->type = data;
  this->mass = PART_MASS[data];
  this->color = PART_COLORS[data];
  this->density = PART_DENSE[data];
  this->fluidity = PART_FLUID[data];
  this->temperature = PART_TEMP[data];
  this->tempConductivity = PART_COND[data];
}

const int &Particle::getType(void) const { return (this->type); }

void Particle::setType(const int &data) { this->type = data; }

const Color &Particle::getColor(void) const { return (this->color); }

void Particle::setColor(const Color &data) { this->color = data; }

const Vector2 &Particle::getPos(void) const { return (this->pos); }

void Particle::setPos(const Vector2 &data) {
  this->pos = data;
  this->size.x = data.x;
  this->size.y = data.y;
}

const Vector2 &Particle::getVel(void) const { return (this->vel); }

void Particle::setVel(const Vector2 &data) { this->vel = data; }

const Vector2 &Particle::getAcel(void) const { return (this->acel); }

void Particle::setAcel(const Vector2 &data) { this->acel = data; }

const double_t &Particle::getMass(void) const { return (this->mass); }

void Particle::setMass(const double_t &data) { this->mass = data; }

const double_t &Particle::getDensity(void) const { return (this->density); }

void Particle::setDensity(const double_t &data) { this->density = data; }

const double_t &Particle::getFluidity(void) const { return (this->fluidity); }

void Particle::setFluidity(const double_t &data) { this->fluidity = data; }

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

const Rectangle &Particle::getSize(void) const { return (this->size); }

void Particle::setSize(const Rectangle &data) { this->size = data; }
