#include "Gravity.hpp"

Gravity::Gravity() : gravity(1.0) {}

Gravity::Gravity(const double_t &G) : gravity(G) {}

Gravity::~Gravity() {}

void Gravity::attract(std::deque<Particle> &p) {
  if (this->gravity == 0.0)
    return;
  for (std::deque<Particle>::iterator p1 = p.begin(); p1 != p.cend(); p1++) {
    for (std::deque<Particle>::iterator p2 = p1; p2 != p.cend(); p2++) {
      (*p1).attract(*p2, this->gravity);
    }
  }
}

void Gravity::attract(const QuadTree &node) {
  if (node.isDivided()) {
    this->attract(*node.getChildren(NORTH_WEST));
    this->attract(*node.getChildren(NORTH_EAST));
    this->attract(*node.getChildren(SOUTH_WEST));
    this->attract(*node.getChildren(SOUTH_EAST));
    return;
  }
  if (node.isEmpty())
    return;
  Particle *const *p = node.getParticles();
  for (size_t i = 0; i < MAX_CAPACITY; i++) {
    if (p[i] == nullptr)
      break;
    for (size_t j = i; j < MAX_CAPACITY; j++) {
      if (p[j] == nullptr)
        break;
      p[i]->attract(*p[j], this->gravity);
    }
    u_int8_t sector = node.getSector();
    for (const QuadTree *n = node.getParent(); n != nullptr;
         n = n->getParent()) {
      if (!n->isEmpty()) {
        if (sector != NORTH_WEST)
          p[i]->attract(n->getChildren(NORTH_WEST)->getMassCenter(),
                        n->getChildren(NORTH_WEST)->getTotalMass(),
                        this->gravity);
        if (sector != NORTH_EAST)
          p[i]->attract(n->getChildren(NORTH_EAST)->getMassCenter(),
                        n->getChildren(NORTH_EAST)->getTotalMass(),
                        this->gravity);
        if (sector != SOUTH_WEST)
          p[i]->attract(n->getChildren(SOUTH_WEST)->getMassCenter(),
                        n->getChildren(SOUTH_WEST)->getTotalMass(),
                        this->gravity);
        if (sector != SOUTH_EAST)
          p[i]->attract(n->getChildren(SOUTH_EAST)->getMassCenter(),
                        n->getChildren(SOUTH_EAST)->getTotalMass(),
                        this->gravity);
      }
      sector = n->getSector();
    }
  }
}

void Gravity::render(void) {}

const double_t &Gravity::getGravity() const { return (this->gravity); }

void Gravity::setGravity(const double_t &other) { this->gravity = other; }
