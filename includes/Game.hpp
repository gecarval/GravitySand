#ifndef GAME_HPP
#define GAME_HPP

// MACROS
static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;

// INCLUDES
#include "../classes/Gravity.hpp"
#include "./imgui/imgui.h"
#include "imgui/rlImGui.h"
#include <iostream>

static const int PART_MAX_AMOUNT = 100;

class Game {
  public:
	std::deque<Particle> particles;
	Gravity				 gravity;
	Camera2D			 camera;
	Game(std::deque<Particle> &p) : particles(p), gravity(Gravity(p)) {};
	~Game() {};
};

void renderImGui(void);
void engineInput(Game &game);

#endif
