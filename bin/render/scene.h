JSONCONS_ENUM_TRAITS()
JSONCONS_N_CTOR_GETTER_TRAITS()
JSONCONS_ALL_CTOR_GETTER_TRAITS()

#include"object.hpp"
#include"sprite.h"

class Scene
{
public:
	Object root;

	Scene();
	~Scene();

	void processFile(const std::string file);

	//needs to be stack or binary heap
private:

};