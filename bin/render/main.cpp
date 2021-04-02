// Test file by Gregory Watts


// There is going to need to be 2 ways to load in a sprite, 2 via individual images and 1 via a sprite map seperated by UV, which might need to be set inside of a program. 
// We should have some form of scene graph, to allow for loading in multiple sprites.

#include "scene.h"
#include "renderer.h"

int main(){
	Scene scene;
	Renderer renderer;

	//setup

	do {
		scene.update();
		renderer.render(&scene);
	} while (renderer.finish);
}