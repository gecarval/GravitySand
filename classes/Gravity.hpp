#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../classes/Particle.hpp"
#include <list>

class Gravity {
  public:
	Gravity();
	~Gravity();

  private:
	std::list<Particle> particle;
};

#endif
