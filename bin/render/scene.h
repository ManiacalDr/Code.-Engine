//Made by Gregory Watts
#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <string>
#include "object.hpp"

class Scene
{
public:
	Object* root;

	Scene();
	~Scene();

	void processFile(const std::string file);
	void writeFile(const std::string file);

private:

};

#endif