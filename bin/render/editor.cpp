#include "editor.h"
#include <imgui.h>

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::render()
{
	if (editable != NULL) {
		ImGui::Begin("Edit Sprite");
		ImGui::InputFloat("position x", &editable->position.x);
		ImGui::InputFloat("position y", &editable->position.y);
		ImGui::InputFloat("position z", &editable->position.z);
		ImGui::SliderFloat("rotation", &editable->rotation, 0.0f, 360.0f);
		ImGui::InputFloat("scale x", &editable->scaleValue.x);
		ImGui::InputFloat("scale y", &editable->scaleValue.y);
		ImGui::End();
	}
}
