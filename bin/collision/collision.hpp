#include "scene.h"

class Collision {
	Scene* scene;

	Collision() {};
	~Collision() {};

	void setScene(Scene* scn) {
		scene = scn;
	}
};