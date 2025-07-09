#include "./QuadTree.hpp"
#include <cstdlib>

QuadTree::QuadTree()
	: tmass(0), qPos(PARENT), level(0), count(0), empty(true), divided(false),
	  parent(nullptr), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {
	this->min = {0, 0};
	this->max = {1920, 1080};
	const float width = (std::abs(this->max.x)) + (this->min.x);
	const float height = (std::abs(this->max.y)) + (this->min.y);
	this->quad = (Rectangle){this->min.x, this->min.y, width, height};
};

QuadTree::QuadTree(QuadTree *p, const Rectangle &q, const size_t &lvl,
				   const uint8_t &qp)
	: quad(q), tmass(0), qPos(qp), level(lvl), count(0), empty(true),
	  divided(false), parent(p), nw(nullptr), ne(nullptr), sw(nullptr),
	  se(nullptr) {};

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
};

QuadTree::~QuadTree() {};

void QuadTree::build(std::deque<Particle> &p) {
	const float width = (std::abs(this->max.x)) + (this->min.x);
	const float height = (std::abs(this->max.y)) + (this->min.y);
	this->quad = (Rectangle){this->min.x, this->min.y, width, height};
	for (std::deque<Particle>::iterator p1 = p.begin(); p1 != p.cend(); p1++) {
		this->insert(&(*p1));
	}
};

void QuadTree::subDivide(void) {
	Rectangle	r;
	const float cx = this->quad.x;
	const float cy = this->quad.y;
	const float wd = this->quad.width / 2.0f;
	const float hg = this->quad.height / 2.0f;
	this->divided = true;
	r = (Rectangle){cx, cy, wd, hg};
	this->nw = new QuadTree(this, r, this->level + 1, NORTH_WEST);
	r = (Rectangle){cx + wd, cy, wd, hg};
	this->ne = new QuadTree(this, r, this->level + 1, NORTH_EAST);
	r = (Rectangle){cx, cy + hg, wd, hg};
	this->sw = new QuadTree(this, r, this->level + 1, SOUTH_WEST);
	r = (Rectangle){cx + wd, cy + hg, wd, hg};
	this->se = new QuadTree(this, r, this->level + 1, SOUTH_EAST);
	for (size_t i = 0; i < MAX_CAPACITY; i++) {
		this->nw->insert(p[i]);
		this->ne->insert(p[i]);
		this->sw->insert(p[i]);
		this->se->insert(p[i]);
		this->p[i] = nullptr;
	};
}

void QuadTree::insert(Particle *p) {
	if (!CheckCollisionPointRec(p->getPos(), this->quad)) return;
	this->mid += p->getPos();
	this->tmass += p->getMass();
	if (this->isDivided()) {
		this->count++;
		this->nw->insert(p);
		this->ne->insert(p);
		this->sw->insert(p);
		this->se->insert(p);
		return;
	}
	if (this->count < MAX_CAPACITY) {
		this->empty = false;
		this->p[this->count++] = p;
		return;
	}
	this->subDivide();
	this->nw->insert(p);
	this->ne->insert(p);
	this->sw->insert(p);
	this->se->insert(p);
};

void QuadTree::clear(void) {
	this->tmass = 0.0;
	this->qPos = PARENT;
	this->level = 0;
	this->count = 0;
	this->empty = true;
	this->divided = false;
	this->parent = nullptr;
	clearChildren(this);
	this->nw = nullptr;
	this->ne = nullptr;
	this->sw = nullptr;
	this->se = nullptr;
};

void QuadTree::renderQuads(const Camera2D &c) {
	if (this->isDivided()) {
		this->nw->renderQuads(c);
		this->ne->renderQuads(c);
		this->sw->renderQuads(c);
		this->se->renderQuads(c);
	}
	const float		posX = (this->quad.x - c.target.x) * c.zoom + c.offset.x;
	const float		posY = (c.target.y - this->quad.y) * c.zoom + c.offset.y;
	const float		width = this->quad.width * c.zoom;
	const float		height = this->quad.height * c.zoom;
	const float		lineThickness = 1.0f;
	const Rectangle rec = (Rectangle){posX, posY, width, height};
	DrawRectangleLinesEx(rec, lineThickness, RED);
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
