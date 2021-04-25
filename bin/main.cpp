// Test file by Gregory Watts


// There is going to need to be 2 ways to load in a sprite, 1 via individual images and 1 via a sprite map seperated by UV, which might need to be set inside of a program. 
// We should have some form of scene graph, to allow for loading in multiple sprites.
#include "render/renderer.h"
#include "render/scene.h"
#include "render/editor.h"

int main() {
	Renderer renderer;
	Scene scene;
	Editor editor;
;
	RenderMode mode = renderer.getMode();

	//setup

	do {
		if (mode != renderer.getMode()) {
			switch (renderer.getMode()) {
			case RenderMode::MENU:
				mode = RenderMode::MENU;
				break;
			case RenderMode::GAME:
				mode = RenderMode::GAME;
				break;
			case RenderMode::EDITOR:
				mode = RenderMode::EDITOR;
				renderer.setEditor(&editor);
				break;
			default:
				break;
			}
		}
		//scene.update();
		renderer.render(scene);
	} while (renderer.finish);
}