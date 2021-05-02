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
	int uvSety = 424;//Size of total picture
	int frameSizex = 106;
	int frameSizey = 106;//Size of each frame. Later is frame/uv to get the Uv coords
	int frames = 12;//Default UV options for dragon

	if (editable != NULL) {
		ImGui::Begin("Edit Sprite");
		//ImGui::SliderFloat3("Position", position, -10000, 10000);
		ImGui::InputFloat("position x", &editable->position.x);
		ImGui::InputFloat("position y", &editable->position.y);
		ImGui::InputFloat("position z", &editable->position.z);
		ImGui::SliderFloat("rotation", &editable->rotation, 0.0f, 360.0f);
		ImGui::InputFloat("scale x", &editable->scaleValue.x);
		ImGui::InputFloat("scale y", &editable->scaleValue.y);
		//editable->position = glm::vec3(position[0], position[1], position[2]);
		if (mysprite->collider==nullptr)//Shows tabs for Active or Passive Collider. Active is moving, while Passive is not.
		{
			ImGui::Checkbox("addActiveCollider", &active);
			ImGui::Checkbox("addPassiveCollider", &passive);
		}
		if (mysprite->UV == nullptr) {//Shows tabs to set up and use a sprite sheet
			ImGui::Text("Sprite Sheet Settings");
			ImGui::InputInt("spriteSheetSizeX",&uvSetx);
			ImGui::InputInt("spriteSheetSizeY", &uvSety);
			ImGui::InputInt("frameSizeX", &frameSizex);
			ImGui::InputInt("frameSizeY", &frameSizey);
			ImGui::InputInt("number of frames", &frames);
			ImGui::Checkbox("useSpriteSheet", &spriteSheet);
		}
			if (scene->playerSprite != mysprite)//If this object is not a player, set up tab to make it the player
			{
				ImGui::Checkbox("makePlayer", &player);
			}
		ImGui::End();
	}
	if (active && mysprite->collider == nullptr)
	{
		mysprite->addCollider(true, scene);
	}
	else if (passive && mysprite->collider == nullptr)
	{
		mysprite->addCollider(false, scene);
	}
	if (spriteSheet && mysprite->UV == nullptr)//Default set up for dragon UV and animation
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
	if(mysprite!=nullptr)//Makes sprite Player
		if (player && scene->playerSprite != mysprite)
		{
			mysprite->makePlayer(scene);
		}
}
