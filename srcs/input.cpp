#include "../includes/Game.hpp"

void engineInput(void) {
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		std::cout << "Right Mouse was Clicked" << std::endl;
	}
	if (IsKeyDown(KEY_ENTER)) {
		std::cout << "Enter Key is Pressed" << std::endl;
	}
	if (IsKeyPressed(KEY_SPACE)) {
		std::cout << "Space Key was Clicked" << std::endl;
	}
}
