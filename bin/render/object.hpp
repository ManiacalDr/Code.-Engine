#include <vector>
#include <glm/ext.hpp>
#include<GL/glu.h>

class Object
{
public:
	glm::vec3 position;
	float rotation;
	glm::vec3 scale;


	Object() { position = vec3(0.0); rotation = 0; scale = vec3(0.0); }
	~Object() {}
	Object(glm::vec3 p, float r, glm::vec3 s) { position = p; rotation = r; scale = s; }

	glm::mat4 getModel() {return translate(position) * rotate(rotation) * scale(scale);}
	glm::mat4 translate(glm::vec3 m) { return glm::translate(glm::mat4(1.0), m); }
	glm::mat4 rotate(float r) { return glm::rotate(glm::mat4, glm::radians(r), glm::vec3(0.0f, 0.0f, 1.0f); }
	glm::mat4 scale(glm::vec3 s) { glm::mat4 temp = glm::scale(glm::mat4, s); return glm::translate(temp, s / 2); }

	void addLink(Object* o) {
		link.emplace_back(new o);
	}

private:
	std::vector<std::unique_ptr<Object>> link;
};