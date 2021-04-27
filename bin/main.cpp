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
	Collision collision;

	collision.setScene(&scene);

	renderer.setScene(&scene);
	renderer.setEditor(&editor);
;
	RenderMode mode = RenderMode::NONE;

	//setup

	float xpos = -480.0f;
	int id = 0;

	do {
		if (mode != renderer.getMode()) {
			switch (renderer.getMode()) {
			case RenderMode::MENU:
				mode = RenderMode::MENU;
				scene.objects.emplace_back(new Sprite("start", glm::mat2x4(1.0f), "assets/textures/menu/start.png", glm::vec3(-387.0f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Start"));
				scene.objects.emplace_back(new Sprite("editor", glm::mat2x4(1.0f), "assets/textures/menu/editor.png", glm::vec3(-67.5f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Editor"));
				scene.objects.emplace_back(new Sprite("quit", glm::mat2x4(1.0f), "assets/textures/menu/quit.png", glm::vec3(326.0f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Quit"));
				break;
			case RenderMode::GAME:
				mode = RenderMode::GAME;
				break;
			case RenderMode::EDITOR:
				scene.objects.clear();
				mode = RenderMode::EDITOR;
				for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator("assets\\textures")) {
					std::cout << entry.path() << boost::filesystem::extension(entry.path()) << '\n';
					if (boost::filesystem::extension(entry.path()) == ".jpg" || boost::filesystem::extension(entry.path()) == ".png") {
						scene.objects.emplace_back(new Sprite(entry.path().stem().string(), glm::mat2x4(1.0f), entry.path().string(), glm::vec3(xpos, -286.0f, 0.0f), 0.0f, glm::vec3(100.0f), std::to_string(id)));
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
	} while (renderer.finish);
}