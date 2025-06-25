#include "../includes/Game.hpp"

void initEngine(void) {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Gravity Sand");
	SetTargetFPS(60);
	rlImGuiSetup(true);
}

void updateEngine(void) {
	while (!WindowShouldClose()) {
		engineInput();
		// BeginDrawing();
		ClearBackground({0, 0, 24, 255});
		// BeginMode2D((Camera){});
		EndMode2D();
		DrawFPS(10, 10);
		renderImGui();
		EndDrawing();
	}
}

void endEngine(void) {
	rlImGuiShutdown();
	CloseWindow();
}

int main(void) {
	initEngine();
	updateEngine();
	endEngine();
	return (0);
}
