// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <cassert>

#include "jsoncons/include/jsoncons/json.hpp"
#include "scene.h"

Scene::Scene()
{
	root = Object();
}

Scene::~Scene()
{

}

void addObj(Object& previous, const auto& current) {
	Object* temp;

	if (current.contains("name")) {
		temp = new Sprite((*current)["name"], (*current)["position"], (*current)["rotation"], (*current)["scale"]);
		previous.addLink(&temp);
	}
	else if (current.contains("iscollider")) {
		temp = new Collision((*current)["iscollider"], (*current)["position"], (*current)["rotation"], (*current)["scale"]);
		previous.addLink(&temp);
	}
	else if (current.contains("isanimaitor")) {
		temp = new Animator((*current)["isanimator"], (*current)["position"], (*current)["rotation"], (*current)["scale"]);
		previous.addLink(&temp);
	}

	if (current["link"] != NULL) {
		addObj(temp, current + 1);
	}
}

void Scene::processFile(const std::string file)
{
	std::ifstream content(file);
	json scene = json::parse(content);

	Object* previous = &root;

	for (const auto& current : scene.array_range()) {
		addObj(previous, current);
	}
}

void Scene::writeFile(const std::string file) {

}