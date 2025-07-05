#include "../includes/Game.hpp"

static void renderer(Game &game) {
	static bool		   i	 = false;
	static float	   j	 = game.gravity.getGravity();
	static const float MAX_G = 10000.0;
	ImGui::Text("Engine Settings");
	ImGui::Checkbox("Gravity", &i);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Turns gravity ON/OFF on the engine.");
	ImGui::Separator();
	ImGui::TextColored({0, 128, 128, 255}, "Gravity Value");
	ImGui::SliderFloat("G", &j, -MAX_G, MAX_G);
	ImGui::Separator();
	ImGui::Text("Funny Button");
	if (ImGui::Button("click") == true) std::cout << "LMAO!" << std::endl;
	game.gravity.setGravity(j * i);
}

void renderImGui(Game &game) {
	rlImGuiBegin();
	ImGui::Begin("Gravity Sand Settings");
	renderer(game);
	ImGui::End();
	rlImGuiEnd();
}
