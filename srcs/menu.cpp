#include "../includes/Game.hpp"

static void gravitySettings(Game &game) {
	static bool		   gravitySwitch = false;
	static float	   currGravity = game.gravity.getGravity();
	static const float MAX_G = 10000.0f;
	ImGui::Text("Engine Settings");
	ImGui::Checkbox("Gravity", &gravitySwitch);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Turns gravity ON/OFF on the engine.");
	ImGui::Separator();
	ImGui::TextColored({0, 128, 128, 255}, "Gravity Value");
	ImGui::SliderFloat("G", &currGravity, -MAX_G, MAX_G);
	ImGui::Separator();
	ImGui::Text("Funny Button");
	if (ImGui::Button("click") == true) std::cout << "LMAO!" << std::endl;
	game.gravity.setGravity(currGravity * gravitySwitch);
}

void renderImGui(Game &game) {
	rlImGuiBegin();
	ImGui::Begin("Gravity Sand Settings");
	gravitySettings(game);
	ImGui::End();
	rlImGuiEnd();
}
