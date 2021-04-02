#include"object.hpp"
#include<string>

class Collision : public Object { // While this does also inherit from object, this information is necessary for the collision box

};

class Animator : public Object { // This class might do some magic to work

};

class Sprite : public Object
{
public:
	Sprite();
	~Sprite();
	Sprite(std::string n) { name = n; }

private:
	std::string name;
};