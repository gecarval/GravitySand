#ifndef GAME_HPP
#define GAME_HPP

// MACROS
#include "raylib/raylib.h"
static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;

// INCLUDES
#include "../classes/Gravity.hpp"
#include "./imgui/imgui.h"
#include "imgui/rlImGui.h"
#include <iostream>
#include <string>

static const int PART_MAX_AMOUNT = 500;

class Game {
  public:
	Camera2D			 camera;
	RenderTexture2D		 screen;
	std::deque<Particle> particles;
	QuadTree			 quadTree;
	Gravity				 gravity;
	Game() {};
	~Game() {};
};

void renderImGui(Game &game);
void engineInput(Game &game);

#endif
