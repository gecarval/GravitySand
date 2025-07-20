#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "../classes/Particle.hpp"
#include <cstdint>
#include <deque>
#include <sys/types.h>

static const size_t MAX_CAPACITY = 4;

enum QUADSECTOR {
  PARENT = (1 << 0),
  NORTH_WEST = (1 << 1),
  NORTH_EAST = (1 << 2),
  SOUTH_WEST = (1 << 3),
  SOUTH_EAST = (1 << 4),
};

class QuadTree {
private:
  Particle *p[MAX_CAPACITY];
  Rectangle quad;
  double_t totalMass;
  Vector2 massCenter;
  Vector2 min;
  Vector2 max;
  uint8_t sector;
  size_t level;
  size_t count;
  bool divided;
  QuadTree *parent;
  QuadTree *nw;
  QuadTree *ne;
  QuadTree *sw;
  QuadTree *se;
  void calcCenterOfMass(void);
  void subDivide(void);

public:
  QuadTree();
  ~QuadTree();
  QuadTree(QuadTree *parent, const Rectangle &quad, const size_t &lvl,
           const uint8_t &sector);
  void clear(void);
  void insert(Particle *p);
  void build(std::deque<Particle> &p);
  void renderQuads(const Camera2D &c);
  void setTotalMass(const double_t &m);
  const double_t &getTotalMass(void) const;
  void setMassCenter(const Vector2 &v);
  const Vector2 &getMassCenter(void) const;
  void setMin(const Vector2 &v);
  const Vector2 &getMin(void) const;
  void setMax(const Vector2 &v);
  const Vector2 &getMax(void) const;
  void setLevel(const size_t &lvl);
  const size_t &getLevel(void) const;
  void isDivided(const bool &state);
  const bool &isDivided(void) const;
  bool isEmpty(void) const;
  void setSector(const u_int8_t &sector);
  const u_int8_t &getSector(void) const;
  void setChildren(QuadTree *node, const uint8_t &sector);
  QuadTree *getChildren(const uint8_t &sector) const;
  Particle *const *getParticles(void) const;
};

#endif
