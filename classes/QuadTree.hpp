#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "../classes/Particle.hpp"
#include <cstdint>

static const size_t MAX_CAPACITY = 4;

class QuadTree {
  private:
	Particle *p[MAX_CAPACITY];
	Rectangle quad;
	double_t  tmass;
	Vector2	  min;
	Vector2	  max;
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
	void		   clear(void);
	void		   insert(const Particle &p);
	void		   setMin(const Vector2 &v);
	const Vector2 &getMin(void) const;
	void		   setMax(const Vector2 &v);
	const Vector2 &getMax(void) const;
};

#endif
