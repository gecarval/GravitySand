#include "../includes/Game.hpp"

static void renderer(void) {
	static bool	 i = false;
	static float j = 1.0;
	ImGui::Text("Engine Settings");
	ImGui::Checkbox("Gravity", &i);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Turns gravity ON/OFF on the engine.");
	ImGui::Separator();
	ImGui::TextColored({0, 128, 128, 255}, "Gravity Value");
	ImGui::SliderFloat("G", &j, -100.0, 100.0);
	ImGui::Separator();
	ImGui::Text("Funny Button");
	if (ImGui::Button("click") == true) std::cout << "LMAO!" << std::endl;
}

void renderImGui(void) {
	rlImGuiBegin();
	ImGui::Begin("Gravity Sand Settings");
	renderer();
	ImGui::End();
	rlImGuiEnd();
}
