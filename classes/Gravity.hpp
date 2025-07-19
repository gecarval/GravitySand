#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../classes/QuadTree.hpp"

class Gravity {
public:
  Gravity();
  Gravity(const double_t &G);
  ~Gravity();
  void render(void);
  void attract(std::deque<Particle> &other);
  const double_t &getGravity(void) const;
  void setGravity(const double_t &other);

private:
  double_t gravity;
};

#endif
