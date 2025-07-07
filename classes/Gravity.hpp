#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../classes/Particle.hpp"
#include "../classes/QuadTree.hpp"
#include <deque>

class Gravity {
  public:
	Gravity();
	Gravity(const double_t &G);
	~Gravity();
	void			update(std::deque<Particle> &other);
	void			render(void);
	void			attract(std::deque<Particle> &other);
	const double_t &getGravity(void) const;
	void			setGravity(const double_t &other);

  private:
	double_t gravity;
};

#endif
