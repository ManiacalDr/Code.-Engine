// Test file by Gregory Watts


// There is going to need to be 2 ways to load in a sprite, 2 via individual images and 1 via a sprite map seperated by UV, which might need to be set inside of a program. 
// We should have some form of scene graph, to allow for loading in multiple sprites.

#include "renderer.h"
using namespace glm;

int main(){
	Renderer renderer;

	//setup

	do {
		renderer.render();
	} while (renderer.finish);
}