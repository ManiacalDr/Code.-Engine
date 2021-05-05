// File by Gregory Watts
#include "render/renderer.h"
#include "render/scene.h"
#include "render/editor.h"
#include "collision/collision.hpp"

void makeAnimation(Scene* scene, float xpos, float ypos, boost::filesystem::directory_entry& entry)
{
	Sprite* tmp;
	int* tmpFrames;
	tmp = new Sprite(entry.path().string(), glm::mat4x2(1.0f), entry.path().string(), glm::vec3(xpos, ypos, 0.0f), 0.0f, glm::vec3(50.0f), entry.path().stem().string());
	tmp->setUV(glm::vec2(0, 0), glm::vec2(318, 424), 12, glm::vec2(106, 106));
	scene->objects.emplace_back(tmp);
}

int main() {
	Renderer renderer;
	Scene scene;
	Editor editor;

	editor.setScene(&scene);
	renderer.setScene(&scene);
	renderer.setEditor(&editor);
	
	RenderMode mode = RenderMode::NONE;

	//setup

	float xpos = -480.0f, ypos = -261.0f;
	int id = 01;

	do {
		if (mode != renderer.getMode()) {
			mode = renderer.getMode();
			Object* tmp;
			Sprite* tmpSprite = dynamic_cast<Sprite*>(scene.playerSprite);
			switch (renderer.getMode()) {
			case RenderMode::MENU:
				scene.objects.emplace_back(new Sprite("start", "assets/textures/menu/start.png", glm::vec3(-387.0f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Start"));
				scene.objects.emplace_back(new Sprite("editor", "assets/textures/menu/editor.png", glm::vec3(-67.5f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Editor"));
				scene.objects.emplace_back(new Sprite("quit", "assets/textures/menu/quit.png", glm::vec3(326.0f, -172.585f, 0.0f), 0.0f, glm::vec3(100.0f), "Quit"));
				break;
			case RenderMode::GAME:
				if (tmpSprite != nullptr) {
					tmpSprite->collider->SetTransform(b2Vec2(scene.playerStart.x * tmpSprite->P2M, scene.playerStart.y * tmpSprite->P2M), tmpSprite->collider->GetAngle());
					std::cout << scene.playerStart.x << " " << scene.playerStart.y << std::endl;
				}
				scene.objects.clear();
				renderer.setScene(&scene);
				break;
			case RenderMode::EDITOR:
				scene.objects.clear();
				for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator("assets\\textures\\sprites")) {
					std::cout << entry.path() << boost::filesystem::extension(entry.path()) << '\n';
					if (boost::filesystem::extension(entry.path()) == ".jpg" || boost::filesystem::extension(entry.path()) == ".png") {
						scene.objects.emplace_back(new Sprite(entry.path().string(), entry.path().string(), glm::vec3(xpos, ypos, 0.0f), 0.0f, glm::vec3(50.0f), "holder"));
						xpos += 50.0f;
						id++;
					}
					if (xpos >= 480) {
						xpos = -480;
						ypos -= 50.0f;
					}
				}
				for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator("assets\\animations")) {
					std::cout << entry.path() << boost::filesystem::extension(entry.path()) << '\n';
					if (boost::filesystem::extension(entry.path()) == ".jpg" || boost::filesystem::extension(entry.path()) == ".png") {
						makeAnimation(&scene, xpos, ypos, entry);
						xpos += 50.0f;
					}
					if (xpos >= 480) {
						xpos = -480;
						ypos -= 50.0f;
					}
				}
				tmp = new Sprite("assets/textures/entities/PlayerStart.png", "assets/textures/entities/PlayerStart.png", glm::vec3(-492.0f, 251.0f, 1.0f), 0.0f, glm::vec3(50.0f), "PlayerStart");
				scene.objects.push_back(tmp);
				xpos = -480.0f;
				ypos = -261.0f;
				break;
			default:
				break;
			}
		}


		//scene.update();
		renderer.render(&scene);

		switch (mode)
		{
		case RenderMode::NONE:
			break;
		case RenderMode::GAME:
			scene.worldStep();
			break;
		case RenderMode::EDITOR:
			break;
		case RenderMode::MENU:
			break;
		default:
			break;
		}

	} while (renderer.finish);
}