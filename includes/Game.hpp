#ifndef GAME_HPP
#define GAME_HPP

// INCLUDES
#include "../classes/Gravity.hpp"
#include "./imgui/imgui.h"
#include "imgui/rlImGui.h"
#include "raylib/raylib.h"
#include <atomic>
#include <iostream>
#include <omp.h>
#include <string>

struct Game {
  Camera2D camera;
  RenderTexture2D screen;
  std::deque<Particle> particles;
  QuadTree quadTree;
  Gravity gravity;
  void updateParticlesVectors(void) {
    for (std::deque<Particle>::iterator p1 = this->particles.begin();
         p1 != this->particles.cend(); p1++) {
      (*p1).update();
    }
  };
};

void renderImGui(Game &game);
void engineInput(Game &game);

#endif
