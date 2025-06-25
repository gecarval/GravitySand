#ifndef GAME_HPP
#define GAME_HPP

// MACROS
static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;

// INCLUDES
#include "./imgui/imgui.h"
#include "./raylib/raylib.h"
#include "./raylib/raymath.h"
#include "imgui/rlImGui.h"
#include <cmath>
#include <iostream>

void renderImGui(void);
void engineInput(void);

#endif
