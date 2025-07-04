#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../classes/Particle.hpp"
#include <cstdint>

static const size_t MAX_CAPACITY = 4;

class QuadTree {
  private:
	Particle *p[MAX_CAPACITY];
	Rectangle quad;
	double_t  tmass;
	uint8_t	  qPos;
	size_t	  count;
	size_t	  level;
	bool	  empty;
	bool	  divided;
	QuadTree *parent;
	QuadTree *nw;
	QuadTree *ne;
	QuadTree *sw;
	QuadTree *se;

  public:
	QuadTree();
	~QuadTree();
	void insert(const Particle &p);
};

#endif
