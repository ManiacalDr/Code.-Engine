// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

#include "jsoncons/json.hpp"
#include "scene.h"
#include "object.hpp"
#include "sprite.h"

Scene::Scene()
{
	root = new Object();
}

Scene::~Scene()
{
	delete root;
}

void addObj(Object* previous, jsoncons::json current) {
	Object* temp;

	if (current.contains("name")) {
		temp = new Sprite((current)["name"].as<std::string>(), glm::vec3((current)["position"][0].as<float>(), (current)["position"][1].as<float>(), (current)["position"][2].as<float>()), (current)["rotation"].as<double>(), glm::vec3((current)["scale"][0].as<float>(), (current)["scale"][1].as<float>(), (current)["scale"][1].as<float>()));
		previous->addLink(*temp);
	}
	else if (current.contains("iscollider")) {
		temp = new Collision( glm::vec3((current)["position"][0].as<float>(), (current)["position"][1].as<float>(), (current)["position"][2].as<float>()), (current)["rotation"].as<double>(), glm::vec3((current)["scale"][0].as<float>(), (current)["scale"][1].as<float>(), (current)["scale"][1].as<float>()));
		previous->addLink(*temp);
	}
	else if (current.contains("isanimaitor")) {
		temp = new Animator(glm::vec3((current)["position"][0].as<float>(), (current)["position"][1].as<float>(), (current)["position"][2].as<float>()), (current)["rotation"].as<double>(), glm::vec3((current)["scale"][0].as<float>(), (current)["scale"][1].as<float>(), (current)["scale"][1].as<float>()));
		previous->addLink(*temp);
	}

	while (current["link"] != NULL) {
		addObj(temp, current);
	}
}

void Scene::processFile(const std::string file)
{
	std::ifstream content(file);
	jsoncons::json scene = jsoncons::json::parse(content);

	addObj(root, scene);
}

void writeNode(std::ofstream& file, Object* node) {
	//write node
	Sprite* tmpSprite = dynamic_cast<Sprite*>(node);
	if (tmpSprite != nullptr) {
		file << tmpSprite->writeJSON();
	}
	Collision* tmpCollision = dynamic_cast<Collision*>(node);
	if (tmpCollision != nullptr) {
		file << tmpCollision->writeJSON();
	}
	Animator* tmpAnimator = dynamic_cast<Animator*>(node);
	if (tmpAnimator != nullptr) {
		file << tmpAnimator->writeJSON();
	}
	//write links, calling writeNode
	file << "\"link\" :[\n{\n";
	for (std::vector<Object*>::iterator i = node->link.begin(); i != node->link.end(); i++) {
		file << "{\n";
		writeNode(file, *i);
		file << "},\n";
	}
	file << "}]\n";
}

void Scene::writeFile(const std::string file) {
	std::ofstream content;
	content.open(file, std::ofstream::binary);

	content << "({\n";
	writeNode(content, root);
	content << "})";
}