#include "../includes/Game.hpp"

void engineInput(Game &game) {
  const float walkSpeed = 20.0f / game.camera.zoom;
  const float zoomDelta = GetMouseWheelMove() * game.camera.zoom * 0.1f;
  const Vector2 mousePan = GetMouseDelta() / game.camera.zoom;
  static const float minZoom = 0.2f;
  static const float maxZoom = 3.0f;

  if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    game.camera.target -= mousePan;
  }
  if (IsKeyDown(KEY_W)) {
    game.camera.target.y -= walkSpeed;
  }
  if (IsKeyDown(KEY_S)) {
    game.camera.target.y += walkSpeed;
  }
  if (IsKeyDown(KEY_A)) {
    game.camera.target.x -= walkSpeed;
  }
  if (IsKeyDown(KEY_D)) {
    game.camera.target.x += walkSpeed;
  }
  game.camera.zoom += zoomDelta;
  game.camera.zoom = Clamp(game.camera.zoom, minZoom, maxZoom);
}
