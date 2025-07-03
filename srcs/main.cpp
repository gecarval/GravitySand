#include "../includes/Game.hpp"
#include <deque>

void initParticles(Game &game) {
	const int part_max_amount = 100;
	int		  randYPos;
	int		  randXPos;
	Vector2	  pos;

	game.particles = std::deque<Particle>(part_max_amount);
	for (int i = 0; i < part_max_amount; i++) {
		randYPos = rand() % WINDOW_HEIGHT;
		randXPos = rand() % WINDOW_WIDTH;
		pos = (Vector2){static_cast<float>(randXPos),
						static_cast<float>(randYPos)};
		game.particles[i].setNewType(rand() % 3);
		game.particles[i].setPos(pos);
	}
	game.gravity.setParticles(game.particles);
	game.gravity.setGravity(3000.0);
}

void initEngine(Game &game) {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Gravity Sand");
	SetTargetFPS(60);
	rlImGuiSetup(true);
	initParticles(game);
	game.camera = (Camera2D){
		(Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f},
		(Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f}, 0.0f, 1.0f};
}

void renderGame(Game &game) {
	game.gravity.render();
}

void updateEngine(Game &game) {
	while (!WindowShouldClose()) {
		engineInput(game);
		game.gravity.attract();
		game.gravity.update();
		BeginDrawing();
		ClearBackground({0, 0, 24, 255});
		BeginMode2D(game.camera);
		renderGame(game);
		EndMode2D();
		DrawFPS(10, 10);
		renderImGui();
		EndDrawing();
	}
}

void endEngine() {
	rlImGuiShutdown();
	CloseWindow();
}

int main(void) {
	std::deque<Particle> p;
	Game				 game(p);
	initEngine(game);
	updateEngine(game);
	endEngine();
	return (0);
}
