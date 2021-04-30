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
	bool spriteSheet = false;
	bool player = false;

	int uvSetx = 318;
	int uvSety = 424;
	int frameSizex = 106;
	int frameSizey = 106;
	int frames = 12;
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
		if (mysprite->UV == nullptr) {
			ImGui::Text("Sprite Sheet Settings");
			ImGui::InputInt("spriteSheetSizeX",&uvSetx);
			ImGui::InputInt("spriteSheetSizeY", &uvSety);
			ImGui::InputInt("frameSizeX", &frameSizex);
			ImGui::InputInt("frameSizeY", &frameSizey);
			ImGui::InputInt("number of frames", &frames);
			ImGui::Checkbox("useSpriteSheet", &spriteSheet);
		}
			if (mysprite->scene->playerSprite != mysprite)
			{
				ImGui::Checkbox("makePlayer", &player);
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
	if (spriteSheet && mysprite->UV == nullptr)
	{
		mysprite->setUV(glm::vec2(0, 0), glm::vec2(uvSetx, uvSety), frames, glm::vec2(frameSizex, frameSizey));
		int* tmpFrames = new int[3]{ 0,1,2 };
		mysprite->setAnimation("downWalk", tmpFrames, 3);
		tmpFrames = new int[3]{ 3,4,5 };
		mysprite->setAnimation("leftWalk", tmpFrames, 3);
		tmpFrames = new int[3]{ 6,7,8 };
		mysprite->setAnimation("rightWalk", tmpFrames, 3);
		tmpFrames = new int[3]{ 9,10,11 };
		mysprite->setAnimation("upWalk", tmpFrames, 3);
	}
	if(mysprite!=nullptr)
		if (player && mysprite->scene->playerSprite != mysprite)
		{
			mysprite->makePlayer();
		}
}
