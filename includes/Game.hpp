#ifndef GAME_HPP
#define GAME_HPP

// INCLUDES
#include "../classes/Gravity.hpp"
#include "./imgui/imgui.h"
#include "imgui/rlImGui.h"
#include "raylib/raylib.h"
#include <iostream>
#include <string>

class Game {
  public:
	Camera2D			 camera;
	RenderTexture2D		 screen;
	std::deque<Particle> particles;
	QuadTree			 quadTree;
	Gravity				 gravity;
	void				 update(std::deque<Particle> &p) {
		for (std::deque<Particle>::iterator p1 = p.begin(); p1 != p.cend();
			 p1++) {
			(*p1).update();
		}
	};
	Game() {};
	~Game() {};
};

void renderImGui(Game &game);
void engineInput(Game &game);

#endif
