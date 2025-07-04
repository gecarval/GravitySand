#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../classes/Particle.hpp"
#include "../classes/QuadTree.hpp"
#include <deque>

class Gravity {
  public:
	Gravity(std::deque<Particle> &p);
	Gravity(std::deque<Particle> &p, const double_t &G);
	~Gravity();
	void						update(void);
	void						render(void);
	void						attract(void);
	const std::deque<Particle> &getParticles(void) const;
	void						setParticles(std::deque<Particle> &other);
	const double_t			   &getGravity(void) const;
	void						setGravity(const double_t &other);

  private:
	std::deque<Particle> &particle;
	double_t			  gravity;
};

#endif
