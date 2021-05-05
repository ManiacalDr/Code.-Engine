//Made by Gregory Watts
#ifndef EDITOR_H
#define EDITOR_H
#include "object.hpp"
#include "sprite.h"

/// Editor class, stores the currently selected sprite/editabale sprite. 
/// Also stores the current scene.
class Editor
{
public:
	
	Object* selection = nullptr;
	Object* editable = nullptr;
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