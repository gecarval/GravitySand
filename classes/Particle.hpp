#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../includes/raylib/raylib.h"
#include "../includes/raylib/raymath.h"
#include <cmath>

static const int PART_SIZE = 2;

class Particle {
  private:
	int		  type;
	Color	  color;
	Vector2	  pos;
	Vector2	  vel;
	Vector2	  acel;
	double_t  mass;
	double_t  density;
	double_t  fluidity;
	double_t  temperature;
	double_t  tempConductivity;
	Rectangle size;

  public:
	Particle();
	Particle(const int &type);
	Particle(const int &type, const Vector2 &pos);
	Particle &operator=(const Particle &other);
	~Particle();
	void update(void);
	void render(void) const;
	void renderAt(const Camera2D &c) const;
	void intersect(const Particle &other) const;
	void attract(Particle &other, const double_t &G);
	void attract(const Vector2 &v, const double_t &m, const double_t &G);
	const Rectangle &getSize(void) const;
	void			 setSize(const Rectangle &data);
	const int		&getType(void) const;
	void			 setType(const int &data);
	void			 setNewType(const int &data);
	const Color		&getColor(void) const;
	void			 setColor(const Color &data);
	const Vector2	&getPos(void) const;
	void			 setPos(const Vector2 &data);
	const Vector2	&getVel(void) const;
	void			 setVel(const Vector2 &data);
	const Vector2	&getAcel(void) const;
	void			 setAcel(const Vector2 &data);
	const double_t	&getMass(void) const;
	void			 setMass(const double_t &data);
	const double_t	&getDensity(void) const;
	void			 setDensity(const double_t &data);
	const double_t	&getFluidity(void) const;
	void			 setFluidity(const double_t &data);
	const double_t	&getTemperature(void) const;
	void			 setTemperature(const double_t &data);
	const double_t	&getTempConductivity(void) const;
	void			 setTempConductivity(const double_t &data);
};

enum ParticleType {
	SAND_PT = 0,
	WATER_PT,
	LAVA_PT,
	ParticleTypeLen,
};

static const Color PART_COLORS[] = {
	[SAND_PT] = (Color){0xC2, 0xB2, 0x80, 0xFF},
	[WATER_PT] = (Color){0xD4, 0xF1, 0xF9, 0xFF},
	[LAVA_PT] = (Color){0xFF, 0x25, 0x00, 0xFF},
};

static const double_t PART_TEMP[] = {
	[SAND_PT] = 0.0,
	[WATER_PT] = 20.0,
	[LAVA_PT] = 1000.0,
};

static const double_t PART_COND[] = {
	[SAND_PT] = 0.0,
	[WATER_PT] = 0.5,
	[LAVA_PT] = 1.0,
};

static const double_t PART_MASS[] = {
	[SAND_PT] = 1.2,
	[WATER_PT] = 0.8,
	[LAVA_PT] = 2.0,
};

static const double_t PART_DENSE[] = {
	[SAND_PT] = 1.0,
	[WATER_PT] = 0.8,
	[LAVA_PT] = 0.9,
};

static const double_t PART_FLUID[] = {
	[SAND_PT] = 0.0,
	[WATER_PT] = 2.0,
	[LAVA_PT] = 0.5,
};

#endif
