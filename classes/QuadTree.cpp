#include "./QuadTree.hpp"
#include <cstdint>

QuadTree::QuadTree()
	: parent(nullptr), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr),
	  tmass(0), qPos(PARENT), level(0), count(0), empty(true),
	  divided(false) {};

QuadTree::QuadTree(QuadTree *p, const Rectangle &q, const size_t &lvl,
				   const uint8_t &qp)
	: parent(p), quad(q), level(lvl), qPos(qp) {};

QuadTree::~QuadTree() {};

void QuadTree::subDivide(void) {
	Rectangle	r;
	const float cx = this->quad.x;
	const float cy = this->quad.y;
	const float wd = this->quad.width / 2.0f;
	const float hg = this->quad.height / 2.0f;
	this->count++;
	this->divided = true;
	r = (Rectangle){cx, cy, wd, hg};
	this->nw = new QuadTree(this, r, this->level + 1, NORTH_WEST);
	r = (Rectangle){cx + wd, cy, wd, hg};
	this->ne = new QuadTree(this, r, this->level + 1, NORTH_EAST);
	r = (Rectangle){cx, cy + hg, wd, hg};
	this->sw = new QuadTree(this, r, this->level + 1, SOUTH_WEST);
	r = (Rectangle){cx + wd, cy + hg, wd, hg};
	this->se = new QuadTree(this, r, this->level + 1, SOUTH_EAST);
	for (size_t i = 0; i < MAX_CAPACITY; i++) return;
}

void QuadTree::insert(Particle *p) {
	QuadTree *node;
	node = this;
	if (node == nullptr) return;
	if (!CheckCollisionPointRec(p->getPos(), node->quad)) return;
	while (node->isDivided()) {
		node->count++;
		node->tmass += p->getMass();
		node = node->getChildren(NORTH_WEST);
		if (CheckCollisionPointRec(p->getPos(), node->quad)) continue;
		node = node->getChildren(NORTH_EAST);
		if (CheckCollisionPointRec(p->getPos(), node->quad)) continue;
		node = node->getChildren(SOUTH_WEST);
		if (CheckCollisionPointRec(p->getPos(), node->quad)) continue;
		node = node->getChildren(SOUTH_EAST);
		if (CheckCollisionPointRec(p->getPos(), node->quad)) continue;
	}
	node->tmass += p->getMass();
	if (node->count < MAX_CAPACITY) {
		node->empty = false;
		node->mid += p->getPos();
		node->p[node->count++] = p;
	} else if (!node->isDivided()) {
		node->subDivide();
		return (this->nw->insert(p), this->ne->insert(p), this->sw->insert(p),
				this->se->insert(p));
	}
};

static void clearChildren(QuadTree *t) {
	if (t == nullptr) return;
	if (t->isDivided()) {
		clearChildren(t->getChildren(NORTH_WEST));
		clearChildren(t->getChildren(NORTH_EAST));
		clearChildren(t->getChildren(SOUTH_WEST));
		clearChildren(t->getChildren(SOUTH_EAST));
	}
	if (t->getLevel() != 0) {
		delete t;
		return;
	}
	t->setChildren(nullptr, NORTH_WEST);
	t->setChildren(nullptr, NORTH_EAST);
	t->setChildren(nullptr, SOUTH_WEST);
	t->setChildren(nullptr, SOUTH_EAST);
};

void QuadTree::clear(void) {
	this->tmass = 0.0;
	this->min = Vector2Zero();
	this->max = Vector2Zero();
	this->qPos = PARENT;
	this->level = 0;
	this->count = 0;
	this->empty = true;
	this->divided = false;
	this->parent = nullptr;
	clearChildren(this);
};

void QuadTree::setLevel(const size_t &lvl) {
	this->level = lvl;
};

const size_t &QuadTree::getLevel(void) const {
	return (this->level);
};

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

void QuadTree::isDivided(const bool &state) {
	this->divided = state;
};

const bool &QuadTree::isDivided(void) const {
	return (this->divided);
};

void QuadTree::setChildren(QuadTree *node, const uint8_t &n) {
	if (n & NORTH_WEST) this->nw = node;
	if (n & NORTH_EAST) this->ne = node;
	if (n & SOUTH_WEST) this->sw = node;
	if (n & SOUTH_EAST) this->se = node;
};

QuadTree *QuadTree::getChildren(const uint8_t &n) const {
	if (n & NORTH_WEST) return (this->nw);
	if (n & NORTH_EAST) return (this->ne);
	if (n & SOUTH_WEST) return (this->sw);
	if (n & SOUTH_EAST) return (this->se);
	return (nullptr);
};
