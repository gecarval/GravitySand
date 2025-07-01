#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../classes/Particle.hpp"
#include <list>

class Gravity {
  public:
	Gravity();
	~Gravity();
	void					   attract(void);
	const std::list<Particle> &getParticles(void);
	void					   setParticles(const std::list<Particle> &other);

  private:
	std::list<Particle> particle;
};

#endif
