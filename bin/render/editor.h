#ifndef EDITOR_H
#define EDITOR_H
#include "object.hpp"
#include "sprite.h"

class Editor
{
public:
	Editor();
	~Editor();
	//std::vector<Object*> objects;
	Object* selection;
	Object* editable;
	Scene* scene;

	void setScene(Scene* scn) {
		scene = scn;
	};

	void makeSelection(Object* sel) { selection = sel; removeEditable(); }
	void makeEditable(Object* edt) { editable = edt; removeSelection(); }
	void removeSelection() { selection = NULL; }
	void removeEditable() { editable = NULL; }
	void render();

private:
};

#endif