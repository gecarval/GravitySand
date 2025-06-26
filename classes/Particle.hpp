#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../includes/raylib/raylib.h"
#include "../includes/raylib/raymath.h"

enum ParticleType {
	Sand = 0,
	Water,
	Lava,
};

static const Color PART_COLORS[] = {
	[Sand] = (Color){0xC2, 0xB2, 0x80, 0xFF},  // Sand
	[Water] = (Color){0xD4, 0xF1, 0xF9, 0xFF}, // Water
	[Lava] = (Color){0xFF, 0x25, 0x00, 0xFF},  // Lava
};

class Particle {
  public:
	Particle(const int &type);
	Particle(const int &type, const Vector2 &pos);
	Particle &operator=(const Particle &other);
	~Particle();

  private:
	int		 type;
	Color	 color;
	Vector2	 pos;
	Vector2	 vel;
	Vector2	 acel;
	double_t density;
	double_t temperature;
	double_t viscocity;
};

#endif
