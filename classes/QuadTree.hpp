#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "../classes/Particle.hpp"
#include <cstdint>

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
	double_t  tmass;
	Vector2	  min;
	Vector2	  mid;
	Vector2	  max;
	uint8_t	  qPos;
	size_t	  level;
	size_t	  count;
	bool	  empty;
	bool	  divided;
	QuadTree *parent;
	QuadTree *nw;
	QuadTree *ne;
	QuadTree *sw;
	QuadTree *se;

  public:
	QuadTree();
	QuadTree(QuadTree *p, const Rectangle &q, const size_t &lvl,
			 const uint8_t &qp);
	~QuadTree();
	void		   clear(void);
	void		   insert(Particle *p);
	void		   setMin(const Vector2 &v);
	void		   subDivide(void);
	const Vector2 &getMin(void) const;
	void		   setMax(const Vector2 &v);
	const Vector2 &getMax(void) const;
	void		   setLevel(const size_t &lvl);
	const size_t  &getLevel(void) const;
	void		   isDivided(const bool &state);
	const bool	  &isDivided(void) const;
	void		   setChildren(QuadTree *node, const uint8_t &n);
	QuadTree	  *getChildren(const uint8_t &n) const;
};

#endif
