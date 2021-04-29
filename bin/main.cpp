// Test file by Gregory Watts


// There is going to need to be 2 ways to load in a sprite, 1 via individual images and 1 via a sprite map seperated by UV, which might need to be set inside of a program. 
// We should have some form of scene graph, to allow for loading in multiple sprites.
#include "render/renderer.h"
#include "render/scene.h"
#include "render/editor.h"
#include "collision/collision.hpp"

int main() {
	Renderer renderer;
	Scene scene;
	Editor editor;

	renderer.setScene(&scene);
	renderer.setEditor(&editor);
;
	RenderMode mode = RenderMode::NONE;

	//setup

	float xpos = -480.0f;
	int id = 0;

	do {
		if (mode != renderer.getMode()) {
			mode = renderer.getMode();
			Sprite* tmp;
			int* tmpFrames;
			switch (renderer.getMode()) {
			case RenderMode::MENU:
				scene.objects.emplace_back(new Sprite("start", "assets/textures/menu/start.png", glm::vec3(-387.0f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Start"));
				scene.objects.emplace_back(new Sprite("editor", "assets/textures/menu/editor.png", glm::vec3(-67.5f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Editor"));
				scene.objects.emplace_back(new Sprite("quit", "assets/textures/menu/quit.png", glm::vec3(326.0f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Quit"));
				break;
			case RenderMode::GAME:
				
				break;
			case RenderMode::EDITOR:
				scene.objects.clear();
				tmp = new Sprite("dragon", glm::mat2x4(1.0f), "assets/animations/picturedragonFrames_thumb.png", glm::vec3(0.0f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "dragon");
				tmp->setUV(glm::vec2(0, 0), glm::vec2(318, 424), 12, glm::vec2(106, 106));
				tmpFrames = new int[2]{ 0,1};
				tmp->setAnimation(tmpFrames, 2);
				scene.objects.emplace_back(tmp);
				for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator("assets\\textures")) {
					std::cout << entry.path() << boost::filesystem::extension(entry.path()) << '\n';
					if (boost::filesystem::extension(entry.path()) == ".jpg" || boost::filesystem::extension(entry.path()) == ".png") {
						scene.objects.emplace_back(new Sprite(entry.path().stem().string(), entry.path().string(), glm::vec3(xpos, -286.0f, 0.0f), 0.0f, glm::vec3(100.0f), std::to_string(id)));
						xpos += 150.0f;
					}
				}
				break;
			default:
				break;
			}
		}


		//scene.update();
		renderer.render(scene);
		
		switch (mode)
		{
		case RenderMode::NONE:
			break;
		case RenderMode::GAME:
			
			break;
		case RenderMode::EDITOR:
			break;
		case RenderMode::MENU:
			break;
		default:
			break;
		}
		scene.worldStep();
	} while (renderer.finish);
}