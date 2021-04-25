#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <memory>
#include <string>
#include <vector>
#include "windows.h"
#include <glm/ext.hpp>
#include<GL/glu.h>

class Object
{
public:
	std::vector<Object*> link;
	glm::vec3 position;
	float rotation;
	glm::vec3 scaleValue;

	std::string ID;


	Object() { position = glm::vec3(0.0); rotation = 0.0f; scaleValue = glm::vec3(0.0f); ID = ""; }
	~Object() { }//delete link; }
	Object(glm::vec3 p, float r, glm::vec3 s, std::string i) { position = p; rotation = r; scaleValue = s; ID = i; }

	glm::mat4 getModel() {return translate(position) * rotate(rotation) * scale(scaleValue);}
	glm::mat4 translate(glm::vec3 m) { return glm::translate(glm::mat4(1.0f), m); }
	glm::mat4 rotate(float r) { return glm::rotate(glm::mat4(1.0f), glm::radians(r), glm::vec3(0.0f, 0.0f, 1.0f)); }
	glm::mat4 scale(glm::vec3 s) { return glm::scale(glm::mat4(1.0f), s); } // return glm::translate(temp, glm::vec3(s.x / 2, s.y / 2, s.z / 2));


	void virtual addLink(Object o) {
		link.emplace_back(new Object(o));
	}

	std::string virtual writeJSON() {
		return "";
	}

private:
	
};

#endif