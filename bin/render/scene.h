#include"object.hpp"
#include"sprite.h"

class Scene
{
public:
	Object root;

	Scene();
	~Scene();

	void processFile(const std::string file);

private:

};