#include "../includes/Game.hpp"

Particle	*particles;
Gravity		gravity;
Camera2D	camera = {(Vector2){0, 0}, (Vector2){0, 0}, 0.0f, 1.0f};

void initParticles(void) {
	int		randYPos;
	int		randXPos;
	Vector2 pos;

	particles = new Particle[1000];
	for (int i = 0; i < 1000; i++) {
		randYPos = rand() % WINDOW_HEIGHT;
		randXPos = rand() % WINDOW_WIDTH;
		pos = {static_cast<float>(randXPos), static_cast<float>(randYPos)};
		particles[i] = Particle(rand() % 3, pos);
	}
	gravity.setParticles(std::list<Particle>(particles, particles + 1000));
}

void initEngine(void) {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Gravity Sand");
	SetTargetFPS(60);
	rlImGuiSetup(true);
	initParticles();
}

void renderGame(void) {
	gravity.render();
}

void updateEngine(void) {
	while (!WindowShouldClose()) {
		engineInput();
		gravity.attract();
		gravity.update();
		BeginDrawing();
		ClearBackground({0, 0, 24, 255});
		BeginMode2D(camera);
		renderGame();
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
