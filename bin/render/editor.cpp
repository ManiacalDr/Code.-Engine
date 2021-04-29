#include "editor.h"
#include "imgui.h"
#include "sprite.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::render()
{
	Sprite* mysprite = (Sprite*)editable;
	bool active = false;
	bool passive = false;
	if (editable != NULL) {
		ImGui::Begin("Edit Sprite");
		ImGui::InputFloat("position x", &editable->position.x);
		ImGui::InputFloat("position y", &editable->position.y);
		ImGui::InputFloat("position z", &editable->position.z);
		ImGui::SliderFloat("rotation", &editable->rotation, 0.0f, 360.0f);
		ImGui::InputFloat("scale x", &editable->scaleValue.x);
		ImGui::InputFloat("scale y", &editable->scaleValue.y);
		if (mysprite->collider==nullptr)
		{
			ImGui::Checkbox("addActiveCollider", &active);
			ImGui::Checkbox("addPassiveCollider", &passive);
		}
		if (mysprite->collider != nullptr) {
			ImGui::Checkbox("remove collider", &active);
		}
		//mysprite->spriteTranslate();
		ImGui::End();
	}
	if (active && mysprite->collider == nullptr)
	{
		mysprite->addCollider(true);
	}
	else if (passive && mysprite->collider == nullptr)
	{
		mysprite->addCollider(false);
	}
	else if (active && mysprite->collider != nullptr) {
		mysprite->removeCollier();
	}
}
