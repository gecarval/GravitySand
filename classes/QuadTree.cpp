#include "./QuadTree.hpp"

QuadTree::QuadTree() {};

QuadTree::~QuadTree() {};

void QuadTree::insert(const Particle &p) {
	(void)p;
	return;
};

void QuadTree::clear(void) {
	return;
}

void QuadTree::setMax(const Vector2 &v) {
	if (v.x > this->max.x) this->max.x = v.x;
	if (v.y > this->max.y) this->max.y = v.y;
};

const Vector2 &QuadTree::getMax(void) const {
	return (this->max);
};

void QuadTree::setMin(const Vector2 &v) {
	if (v.x < this->min.x) this->min.x = v.x;
	if (v.y < this->min.y) this->min.y = v.y;
};

const Vector2 &QuadTree::getMin(void) const {
	return (this->min);
};
