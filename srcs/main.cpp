#include "../includes/Game.hpp"
#include <deque>

void initParticles(Game &game) {
	int		randYPos;
	int		randXPos;
	Vector2 pos;

	game.particles = std::deque<Particle>(PART_MAX_AMOUNT);
	for (std::deque<Particle>::iterator p = game.particles.begin();
		 p != game.particles.end(); p++) {
		randYPos = rand() % WINDOW_HEIGHT;
		randXPos = rand() % WINDOW_WIDTH;
		pos = (Vector2){static_cast<float>(randXPos),
						static_cast<float>(randYPos)};
		(*p).setNewType(rand() % 3);
		(*p).setPos(pos);
	}
	game.gravity.setGravity(3000.0);
}

void initEngine(Game &game) {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Gravity Sand");
	//	SetTargetFPS(60);
	rlImGuiSetup(true);
	initParticles(game);
	game.camera = (Camera2D){
		(Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f},
		(Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f}, 0.0f, 1.0f};
	game.screen = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void renderGame(Game &game) {
	BeginTextureMode(game.screen);
	ClearBackground({0, 0, 24, 255});
	for (std::deque<Particle>::iterator p = game.particles.begin();
		 p != game.particles.cend(); p++) {
		(*p).renderAt(game.camera);
	}
	EndTextureMode();
}

void updateEngine(Game &game) {
	while (!WindowShouldClose()) {
		engineInput(game);
		game.gravity.attract(game.particles);
		game.gravity.update(game.particles);
		renderGame(game);
		BeginDrawing();
		DrawTexture(game.screen.texture, 0, 0, WHITE);
		BeginMode2D(game.camera);
		EndMode2D();
		DrawFPS(10, 10);
		renderImGui(game);
		EndDrawing();
	}
}

void endEngine() {
	rlImGuiShutdown();
	CloseWindow();
}

int main(void) {
	Game game;
	initEngine(game);
	updateEngine(game);
	endEngine();
	return (0);
}
