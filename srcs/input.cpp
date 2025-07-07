#include "../includes/Game.hpp"

void engineInput(Game &game) {
	const float		   WALKSPEED = (0.8f * GetFrameTime()) / (game.camera.zoom);
	static const float MIN_ZOOM = 0.1f / ((float)WINDOW_WIDTH / 5000.0f);

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		std::cout << "Right Mouse was Clicked" << std::endl;
	}
	if (IsKeyDown(KEY_ENTER)) {
		std::cout << "Enter Key is Pressed" << std::endl;
	}
	if (IsKeyPressed(KEY_SPACE)) {
		std::cout << "Space Key was Clicked" << std::endl;
	}
	if (IsKeyDown(KEY_W)) {
		game.camera.target.y -= (WINDOW_WIDTH * WALKSPEED);
	}
	if (IsKeyDown(KEY_S)) {
		game.camera.target.y += (WINDOW_WIDTH * WALKSPEED);
	}
	if (IsKeyDown(KEY_A)) {
		game.camera.target.x -= (WINDOW_WIDTH * WALKSPEED);
	}
	if (IsKeyDown(KEY_D)) {
		game.camera.target.x += (WINDOW_WIDTH * WALKSPEED);
	}
	game.camera.zoom += ((float)GetMouseWheelMove() * 0.1f * game.camera.zoom);
	if (game.camera.zoom > 3.0f)
		game.camera.zoom = 3.0f;
	else if (game.camera.zoom < MIN_ZOOM)
		game.camera.zoom = MIN_ZOOM;
}
