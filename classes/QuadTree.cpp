#include "./QuadTree.hpp"

QuadTree::QuadTree()
    : quad(Rectangle()), totalMass(0), massCenter(Vector2()), min(Vector2()),
      max(Vector2()), sector(PARENT), level(0), count(0), divided(false),
      parent(nullptr), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}

QuadTree::QuadTree(QuadTree *parent, const Rectangle &quad, const size_t &lvl,
                   const uint8_t &sector)
    : quad(quad), totalMass(0), massCenter(Vector2()), sector(sector),
      level(lvl), count(0), divided(false), parent(parent), nw(nullptr),
      ne(nullptr), sw(nullptr), se(nullptr) {}

QuadTree::~QuadTree() {}

void QuadTree::build(std::deque<Particle> &p) {
  const Vector2 pos = (Vector2){this->min.x, this->min.y};
  const float width = std::abs(this->max.x) + std::abs(this->min.x);
  const float height = std::abs(this->max.y) + std::abs(this->min.y);
  this->quad = (Rectangle){pos.x, pos.y, width, height};
  for (std::deque<Particle>::iterator p1 = p.begin(); p1 != p.cend(); p1++) {
    this->insert(&(*p1));
  }
  this->calcCenterOfMass();
}

void QuadTree::subDivide(void) {
  Rectangle r;
  const float cx = this->quad.x;
  const float cy = this->quad.y;
  const float wd = this->quad.width / 2.0f;
  const float hg = this->quad.height / 2.0f;
  this->isDivided(true);
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
  if (!CheckCollisionPointRec(p->getPos(), this->quad))
    return;
  this->massCenter += p->getPos();
  this->totalMass += p->getMass();
  if (this->isDivided()) {
    this->count++;
    this->nw->insert(p);
    this->ne->insert(p);
    this->sw->insert(p);
    this->se->insert(p);
    return;
  }
  if (this->count < MAX_CAPACITY) {
    this->p[this->count++] = p;
    return;
  }
  this->subDivide();
  this->nw->insert(p);
  this->ne->insert(p);
  this->sw->insert(p);
  this->se->insert(p);
}

void QuadTree::clear(void) {
  if (this->isDivided()) {
    this->nw->clear();
    this->ne->clear();
    this->sw->clear();
    this->se->clear();
  }
  if (this->getSector() != PARENT) {
    delete this;
    return;
  }
  this->totalMass = 0.0;
  this->sector = PARENT;
  this->level = 0;
  this->count = 0;
  this->divided = false;
  this->parent = nullptr;
  this->nw = nullptr;
  this->ne = nullptr;
  this->sw = nullptr;
  this->se = nullptr;
}

void QuadTree::renderQuads(const Camera2D &camera) {
  if (this->isDivided()) {
    this->nw->renderQuads(camera);
    this->ne->renderQuads(camera);
    this->sw->renderQuads(camera);
    this->se->renderQuads(camera);
    return;
  }
  const float lineThickness = 1.0f;
  DrawRectangleLinesEx(this->quad, lineThickness, RED);
  DrawCircleV(this->massCenter, 2, GREEN);
}

void QuadTree::calcCenterOfMass(void) {
  if (this->isDivided()) {
    this->nw->calcCenterOfMass();
    this->ne->calcCenterOfMass();
    this->sw->calcCenterOfMass();
    this->se->calcCenterOfMass();
  }
  if (this->count != 0)
    this->massCenter /= this->count;
}

void QuadTree::setMax(const Vector2 &v) {
  if (v.x > this->max.x)
    this->max.x = v.x;
  if (v.y > this->max.y)
    this->max.y = v.y;
}

void QuadTree::setMin(const Vector2 &v) {
  if (v.x < this->min.x)
    this->min.x = v.x;
  if (v.y < this->min.y)
    this->min.y = v.y;
}

void QuadTree::setMassCenter(const Vector2 &v) { this->massCenter = v; }

void QuadTree::setTotalMass(const double_t &m) { this->totalMass = m; }

void QuadTree::setSector(const u_int8_t &sector) { this->sector = sector; }

void QuadTree::setLevel(const size_t &lvl) { this->level = lvl; }

const Vector2 &QuadTree::getMax(void) const { return (this->max); }

const Vector2 &QuadTree::getMin(void) const { return (this->min); }

const Vector2 &QuadTree::getMassCenter(void) const {
  return (this->massCenter);
}

const double_t &QuadTree::getTotalMass(void) const { return (this->totalMass); }

const u_int8_t &QuadTree::getSector(void) const { return (this->sector); }

const size_t &QuadTree::getLevel(void) const { return (this->level); }

void QuadTree::isDivided(const bool &state) { this->divided = state; }

const bool &QuadTree::isDivided(void) const { return (this->divided); }

bool QuadTree::isEmpty(void) const { return (this->count == 0 ? true : false); }

Particle *const *QuadTree::getParticles(void) const { return (this->p); }

void QuadTree::setChildren(QuadTree *node, const uint8_t &sector) {
  if (sector & NORTH_WEST)
    this->nw = node;
  if (sector & NORTH_EAST)
    this->ne = node;
  if (sector & SOUTH_WEST)
    this->sw = node;
  if (sector & SOUTH_EAST)
    this->se = node;
}

QuadTree *QuadTree::getChildren(const uint8_t &sector) const {
  if (sector & NORTH_WEST)
    return (this->nw);
  if (sector & NORTH_EAST)
    return (this->ne);
  if (sector & SOUTH_WEST)
    return (this->sw);
  if (sector & SOUTH_EAST)
    return (this->se);
  return (nullptr);
}
