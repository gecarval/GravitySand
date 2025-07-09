#include "../includes/Game.hpp"
#include <deque>

// Window Settings
static const char	*windowTitle = "Gravity Sand";
static const int	 windowWidth = 1600;
static const int	 windowheight = 900;
static const int	 frameLimit = 60;
static const Vector2 drawFpsPos = (Vector2){10.0f, 10.0f};

// Game Camera2D Settings
static const float	 posX = windowWidth / 2.0f;
static const float	 posY = windowheight / 2.0f;
static const Vector2 screenMiddle = (Vector2){posX, posY};
static const Vector2 target = screenMiddle;
static const Vector2 offset = screenMiddle;
static const float	 rotation = 0.0f;
static const float	 zoom = 1.0f;

// Render Texture Settings
static const Vector2 axisCenter = (Vector2){0.0f, 0.0f};
static const Color	 backGroundColor = (Color){0, 0, 24, 255};
static const Color	 screenColorTint = WHITE;

// Simulation Settings
static const int   particleMaxAmount = 500;
static const float defaultGravityValue = 3000.0f;

void initParticles(Game &game) {
	float	randYPos;
	float	randXPos;
	Vector2 pos;

	game.particles = std::deque<Particle>(particleMaxAmount);
	for (std::deque<Particle>::iterator p = game.particles.begin();
		 p != game.particles.end(); p++) {
		randYPos = rand() % windowheight;
		randXPos = rand() % windowWidth;
		pos = (Vector2){randXPos, randYPos};
		(*p).setNewType(rand() % 3);
		(*p).setPos(pos);
	}
}

void initEngine(Game &game) {
	InitWindow(windowWidth, windowheight, windowTitle);
	SetTargetFPS(frameLimit);
	rlImGuiSetup(true);
	initParticles(game);
	game.gravity.setGravity(defaultGravityValue);
	game.camera = (Camera2D){offset, target, rotation, zoom};
	game.screen = LoadRenderTexture(windowWidth, windowheight);
}

void renderGame(Game &game) {
	BeginTextureMode(game.screen);
	ClearBackground(backGroundColor);
	for (std::deque<Particle>::iterator p = game.particles.begin();
		 p != game.particles.cend(); p++) {
		(*p).renderAt(game.camera);
		game.quadTree.setMin((*p).getPos());
		game.quadTree.setMax((*p).getPos());
	}
	EndTextureMode();
}

void updateEngine(Game &game) {
	while (!WindowShouldClose()) {
		engineInput(game);
		game.gravity.attract(game.particles);
		game.update(game.particles);
		renderGame(game);
		BeginDrawing();
		DrawTexture(game.screen.texture, axisCenter.x, axisCenter.y,
					screenColorTint);
		BeginMode2D(game.camera);
		EndMode2D();
		DrawFPS(drawFpsPos.x, drawFpsPos.y);
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
