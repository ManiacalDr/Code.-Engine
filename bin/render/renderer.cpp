// Made by Gregory Watts
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "windows.h"
#include "renderer.h"
#include "sprite.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

/// Helper function to report OpenGL errors
void _ReportError(int ln, const std::string str) {
	GLuint err = glGetError();
	if (!err) return;
	const GLubyte* glerr = gluErrorString(err);
	printf("\n******************************************\n%d: %s: GLError %d: %s\n", ln, str.c_str(), err, glerr);
}

/// Defines the error callback
void glfwErrorCB(int error, const char* description) {
	fputs(description, stderr);
}

/// Defines the Keyboard callback in OpenGL
void Renderer::KeyboardCB(int key, int scancode, int action, int mods) {
	static float speed = 1.0;
	Object* sprite = new Object();
	if (key == GLFW_KEY_UNKNOWN) return; // Don't accept unknown keys
	if (action == GLFW_PRESS)
		pressed[key] = true;
	else if (action == GLFW_RELEASE)
		pressed[key] = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	switch (mode)
	{
	case RenderMode::GAME:
		if (key == GLFW_KEY_PERIOD && (action == GLFW_PRESS)) {
			
		}
		if (key == GLFW_KEY_G && (action == GLFW_REPEAT || action == GLFW_PRESS))
			mode = RenderMode::EDITOR;
		if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			//std::cout << "Hit W";
			playerMove("W");
			scene->playerSprite->position = scene->playerSprite->translate(glm::vec3(0.0, speed, 0.0)) * glm::vec4(scene->playerSprite->position, 1.0);
			glm::mat4 update = glm::translate(glm::mat4(1.0f), scene->playerSprite->position);
		}
		if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			//std::cout << "Hit A";
			playerMove("A");
			scene->playerSprite->position = scene->playerSprite->translate(glm::vec3(-speed, 0.0, 0.0)) * glm::vec4(scene->playerSprite->position, 1.0);
			glm::mat4 update = glm::translate(glm::mat4(1.0f), scene->playerSprite->position);
		}
		if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			//std::cout << "Hit S";
			playerMove("S");
			scene->playerSprite->position = scene->playerSprite->translate(glm::vec3(0.0, -speed, 0.0)) * glm::vec4(scene->playerSprite->position, 1.0);
			glm::mat4 update = glm::translate(glm::mat4(1.0f), scene->playerSprite->position);
		}
		if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			//std::cout << "Hit D";
			playerMove("D");
			scene->playerSprite->position = scene->playerSprite->translate(glm::vec3(speed, 0.0, 0.0)) * glm::vec4(scene->playerSprite->position, 1.0);
			glm::mat4 update = glm::translate(glm::mat4(1.0f), scene->playerSprite->position);
		}
		break;
	case RenderMode::EDITOR:
		if (key == GLFW_KEY_G && (action == GLFW_REPEAT || action == GLFW_PRESS))
			mode = RenderMode::GAME;
		if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {//Moves player with playerMove function
			//std::cout << "Hit W";
			glm::mat4 update = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, speed, 0.0));
			updateCam(update);
			// This is not the best solution, slows down editor camera movement with large number of objects
			for (auto i = scene->objects.begin(); i != scene->objects.end(); i++) {
				Sprite* tmpSprite = dynamic_cast<Sprite*>(*i);
				if (tmpSprite != nullptr) {
					tmpSprite->position = glm::vec3(update * glm::vec4(tmpSprite->position, 1.0));
				}
			}
		}
		if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			//std::cout << "Hit A";
			glm::mat4 update = glm::translate(glm::mat4(1.0f), glm::vec3(-speed, 0.0, 0.0));
			updateCam(update);
			// This is not the best solution, slows down editor camera movement with large number of objects
			for (auto i = scene->objects.begin(); i != scene->objects.end(); i++) {
				Sprite* tmpSprite = dynamic_cast<Sprite*>(*i);
				if (tmpSprite != nullptr) {
					tmpSprite->position = glm::vec3(update * glm::vec4(tmpSprite->position, 1.0));
				}
			}
		}
		if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			glm::mat4 update = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -speed, 0.0));
			updateCam(update);
			// This is not the best solution, slows down editor camera movement with large number of objects
			for (auto i = scene->objects.begin(); i != scene->objects.end(); i++) {
				Sprite* tmpSprite = dynamic_cast<Sprite*>(*i);
				if (tmpSprite != nullptr) {
					tmpSprite->position = glm::vec3(update * glm::vec4(tmpSprite->position, 1.0));
				}
			}
			//std::cout << "Hit S";
		}
		if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			glm::mat4 update = glm::translate(glm::mat4(1.0f), glm::vec3(speed, 0.0, 0.0));
			updateCam(update);
			// This is not the best solution, slows down editor camera movement with large number of objects
			for (auto i = scene->objects.begin(); i != scene->objects.end(); i++) {
				Sprite* tmpSprite = dynamic_cast<Sprite*>(*i);
				if (tmpSprite != nullptr) {
					tmpSprite->position = glm::vec3(update * glm::vec4(tmpSprite->position, 1.0));
				}
			}
			//std::cout << "Hit D";
		}
		if (key == GLFW_KEY_R && action == GLFW_PRESS) {
			cam = glm::vec3(0.0);
		}
		break;
	case RenderMode::MENU:
		break;
	default:
		break;
	}
	v = lookAt(cam, glm::vec3(cam.x, cam.y, -(cam.z + 10)), glm::vec3(0.0, 1.0, 0.0));
}

/// Defines the mouse callback for OpenGL
void Renderer::mouse_button_callback(int button, int action, int mods) {
	static float layer = 0.0;
	bool spriteHit = false, objHit = false;
	Object* sprite = new Object(), * object = new Object();
	double xpos, ypos;
	int width, height;
	std::vector<Object*>::iterator playerSprite = scene->sprites.end();

	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetWindowSize(window, &width, &height);

	glm::mat4 inverse = glm::inverse(v * p);

	glm::vec4 temp = glm::vec4((2.0f * ((float)(xpos - 0) / ((float)width))) - 1.0f, 1.0f - (2.0f * ((float)ypos / height)), 0, 1.0);
	glm::vec3 pos = temp * inverse;
	if (action == GLFW_PRESS) {
		pos += cam;

		//pos.w = 1.0 / pos.w;
		//pos.x *= pos.w;
		//pos.y *= pos.w;
		//pos.z *= pos.w;

		std::cout << std::endl << pos.x << " " << pos.y << std::endl;

		for (auto i = (*scene).sprites.begin(); i != (*scene).sprites.end(); i++) {
			if ((**i).ID == "PlayerStart")
				playerSprite = i;
			if (((**i).position.x < pos.x && (**i).position.x + (**i).scaleValue.x > pos.x) && ((**i).position.y < pos.y && (**i).position.y + (**i).scaleValue.y > pos.y)) {
				std::cout << "\nObject was hit\n";
				spriteHit = true;
				sprite = nullptr;
				sprite = *i;
			}
		}

		for (auto i = (*scene).objects.begin(); i != (*scene).objects.end(); i++) {
			if (((**i).position.x < pos.x && (**i).position.x + (**i).scaleValue.x > pos.x) && ((**i).position.y < pos.y && (**i).position.y + (**i).scaleValue.y > pos.y)) {
				std::cout << "\nObject was hit\n";
				objHit = true;
				object = nullptr;
				object = *i;
			}
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

				switch (mode)
				{
				case RenderMode::GAME:
					break;
				case RenderMode::EDITOR:
					if (spriteHit == true) {
						editor->makeEditable(sprite);
					}
					break;
				case RenderMode::MENU:
					
					break;
				default:
					break;
				}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
				switch (mode)
				{
				case RenderMode::GAME:
					break;
				case RenderMode::EDITOR:
					if (objHit == true) {
						if (object->ID == "Quit") {
							finish = false;
							break;
						}
						editor->makeSelection(object);
					}
					else if (spriteHit == true) {
						if (pressed[GLFW_KEY_LEFT_CONTROL]) {
							auto temp = std::find(scene->sprites.begin(), scene->sprites.end(), sprite);
							scene->sprites.erase(temp);
							editor->removeEditable();
						}
					}
					else if (objHit == false && (*editor).selection != NULL && (*editor).editable == NULL) {
						if ((*editor).selection->ID == "PlayerStart") {
							std::cout << "\n Set Player Position";
							if(playerSprite != scene->sprites.end())
								scene->sprites.erase(playerSprite);
							scene->playerStart = glm::vec3(pos.x , pos.y, 0.0f);
							std::cout << std::endl << pos.x - ((*editor).selection->scaleValue.x / 2) << " " << pos.y - ((*editor).selection->scaleValue.y / 2) << std::endl;
						}
						Sprite* tmpSprite = dynamic_cast<Sprite*>((*editor).selection);
						if (tmpSprite != nullptr) {
							layer -= 1;
							scene->sprites.emplace(scene->sprites.begin(),new Sprite(true,(*tmpSprite).name, (*tmpSprite).curFrame, (*tmpSprite).texture, glm::vec3(pos.x - ((*tmpSprite).scaleValue.x / 2), pos.y - ((*tmpSprite).scaleValue.y / 2), layer), 0.0f, (*tmpSprite).scaleValue, (*tmpSprite).ID));
						}
					}
					break;
				case RenderMode::MENU:
					if (objHit == true) {
						if (object->ID == "Start") {
							mode = RenderMode::GAME;
							scene->readSprites("assets/scenes/test");
						}
						if (object->ID == "Editor") {
							mode = RenderMode::EDITOR;
						}
						if (object->ID == "Quit") finish = false;
					}
					break;
				default:
					break;
				}
	}
}

/// Defines what should happen when the frame changes sizes. 
/// Is not currently used due to it causing issues in the editor.
void Renderer::framebuffer_size_callback(int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	// glViewport(0, 0, width, height);
	p = glm::ortho(-(width / 2.0f), width / 2.0f,
		-(height / 2.0f), (height / 2.0f),
		-1000.0f, 1000.0f);
}

/// Initializes the renderer, setting up VBO's, VAO's, shaders
/// and attribute locations inside the shaders.
void Renderer::initialize() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	reportError("gen");

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	reportError("data");

	ProgramID = LoadShaders("assets/shaders/shadervertex.txt", "assets/shaders/shaderfragment.txt");
	TextID = LoadShaders("assets/shaders/textvertex.txt", "assets/shaders/textfragment.txt");
	reportError("shader");

	GLuint pos, texCoord;
	// position attribute
	pos = glGetAttribLocation(ProgramID, "aPos");
	if (pos < 0) std::cerr << "couldn't find vPosition in shader\n";
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(pos);
	// texture coord attribute
	texCoord = glGetAttribLocation(ProgramID, "aTexCoord");
	if (texCoord < 0) std::cerr << "couldn't find texCoord in shader\n";
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(texCoord);
	
	//generate vao, vbo for text
	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glDepthFunc(GL_LESS); //depth-testing interprets a smaller value as "closer"
	reportError("init");
}

/// Function to change the camera location based on a transfromation matrix.
void Renderer::updateCam(glm::mat4 update)
{
	cam = glm::vec3(update * glm::vec4(cam,1.0f));
	v = lookAt(cam, glm::vec3(cam.x, cam.y, -(cam.z + 10)), glm::vec3(0.0, 1.0, 0.0));
}

/// The Renderer constructor, sets up the OpenGL window, the text portion of the renderer,
/// calls initilize and sets up ImGui context
Renderer::Renderer()
{
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return; // This might need to return an error code of some sort, failed to initlize;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Open a window and create its OpenGL context

	window = glfwCreateWindow(1920, 1080, "Code.", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return; // This might need to return an error code of some sort, failed to initlize;
	}
	glewExperimental = true; // Needed in core profile

	glfwMakeContextCurrent(window); // Initialize GLEW

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;// This might need to return an error code of some sort, failed to initlize;
	}

	std::cout << "Running OpenGL Version " << glGetString(GL_VERSION)
		<< " using " << glGetString(GL_RENDERER) << "\n";

	//initlize freetype
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;// This might need to return an error code of some sort, failed to initlize;
	}
	FT_Face face;
#ifdef _WIN64
	if (FT_New_Face(ft, "C:/Windows/Fonts/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;// This might need to return an error code of some sort, failed to initlize;
	}
#endif
#ifdef __APPLE__
	if (FT_New_Face(ft, "C:/System/Library/Fonts/arial.ttf", 0, &face)) 
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;// This might need to return an error code of some sort, failed to initlize;
	}
#endif

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	initialize();

	// Setup Dear ImGui context
							//IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, KeyboardCB);//must be called after creating window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//must be called after creating window
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// set uniforms of main program
	glUseProgram(ProgramID);
	glUniform1i(glGetUniformLocation(ProgramID, "atexture"), 0);
	glUniform4f(glGetUniformLocation(ProgramID, "aColor"), 1.0f, 1.0f, 1.0f, 1.0f);
	COLOR = glGetUniformLocation(ProgramID, "aColor");
	MVP = glGetUniformLocation(ProgramID, "mvp");
	UV = glGetUniformLocation(ProgramID, "texcoords");

	p = glm::ortho(-(1080.0f / 2.0f), (1080.0f / 2.0f),
		-(768.0f / 2.0f), (768.0f / 2.0f),
		-1.0f, 10000.0f);
	v = lookAt(cam, glm::vec3(cam.x, cam.y, -(cam.z+10)), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 m = glm::mat4(1.0);
	mvp = p * v * m;

	glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);
	// set uniforms of text
	glUseProgram(TextID);
	glUniformMatrix4fv(glGetUniformLocation(TextID, "projection"), 1, GL_FALSE, &p[0][0]);

	reportError("First");
}

/// We used a seperate shader for rendering text, this fuction is responsible for swtiching shaders and correctly rendering dynamic
/// text on screen.
void Renderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state	
	glUseProgram(TextID);
	glUniform3f(glGetUniformLocation(TextID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(textVAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(ProgramID);
}

/// This function is used to render a frame of the current scene. Also renders elements according 
/// to render mode.
void Renderer::render(Scene* scene) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	static char buf[20] = "Name File Here";

	glUseProgram(ProgramID);

	for (auto i = scene->sprites.begin(); i != scene->sprites.end(); i++) {
		
			Sprite* tmpSprite = dynamic_cast<Sprite*>(*i);
			if (tmpSprite != nullptr) {
				if (tmpSprite->collider != nullptr)//Makes sure the rendered object is with the collider object at all times
				{
					tmpSprite->colliderTranslate();
				}
				mvp = p * v * tmpSprite->getModel();

				glUniformMatrix4x2fv(UV, 1, GL_FALSE, &(tmpSprite->curFrame[0][0]));
				glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);
				glBindTexture(GL_TEXTURE_2D, (*tmpSprite).texture);

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}

	}

	for (auto i = scene->objects.begin(); i != scene->objects.end(); i++) {
			Sprite* tmpSprite = dynamic_cast<Sprite*>(*i);
			if (tmpSprite != nullptr) {
				if (tmpSprite->collider != nullptr)
				{
					tmpSprite->colliderTranslate();
				}
				mvp = p * v * tmpSprite->getModel();
				if (tmpSprite)
					glUniformMatrix4x2fv(UV, 1, false, &(tmpSprite->curFrame[0][0]));
				glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);
				glBindTexture(GL_TEXTURE_2D, (*tmpSprite).texture);

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
	}
	static float val = 10;
	Object* sprite = new Object();
	switch (Renderer::mode)
	{
	case  RenderMode::MENU:
		RenderText("Code.", -505.0f, 322.0f, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));
		break;
	case RenderMode::GAME:
		if(scene->playerSprite == nullptr)
			RenderText("ERROR: Player Sprite not set", -400.0f, 0.0f, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));
		else {
			cam = glm::vec3(scene->playerSprite->position.x + scene->playerSprite->scaleValue.x / 2, scene->playerSprite->position.y + scene->playerSprite->scaleValue.y / 2, 10);
		}
		v = lookAt(cam, glm::vec3(cam.x, cam.y, -(cam.z + 10)), glm::vec3(0.0, 1.0, 0.0));
		break;
	case RenderMode::EDITOR:
		
		RenderText("left click to select sprite", 210.0f, 322.0f, 0.25f, glm::vec3(0.3, 0.7f, 0.9f));
		RenderText("Right click to edit sprite in scene", 210.0f, 322.0f - val, 0.25f, glm::vec3(0.3, 0.7f, 0.9f));
		RenderText("Ctrl + left click to remove sprite", 210.0f, 322.0f - val*2, 0.25f, glm::vec3(0.3, 0.7f, 0.9f));
		RenderText("hit R to reset camera", 210.0f, 322.0f - val*3, 0.25f, glm::vec3(0.3, 0.7f, 0.9f));
		RenderText("hit G to switch between game and editor", 210.0f, 322.0f - val*4, 0.25f, glm::vec3(0.3, 0.7f, 0.9f));

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Button("Save")) {
			int size = sizeof(buf) / sizeof(char);
			int i;
			std::string s = "assets/scenes/";
			for (i = 0; i < size; i++) {
				if(buf[i] != ' ')
					s = s + buf[i];
			}
			scene->saveSprites(s);
		}
		if (ImGui::Button("Load")) {
			int size = sizeof(buf) / sizeof(char);
			int i;
			std::string s = "assets/scenes/";
			for (i = 0; i < size; i++) {
				s = s + buf[i];
			}
			scene->readSprites(s);
		}
		ImGui::InputText("string", buf, (int)(sizeof(buf)/sizeof(*buf)));

		(*editor).render();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		break;
	default:
		break;
	}

	glfwSwapBuffers(window);
	glfwPollEvents();

	if (glfwWindowShouldClose(window)) { finish = false; }
	//reportError("render");
}

/// Helper funciton to appropriatly move player in the scene. 
void Renderer::playerMove(std::string key)
{
	if (scene->playerSprite != nullptr)
	{
		Sprite* tmpSprite = dynamic_cast<Sprite*>(scene->playerSprite);
		tmpSprite->playerControl(key);
	}

}

/// Renderer destructor call, deletes buffers and programs.
Renderer::~Renderer()
{
	// Cleanup VBO
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &textVBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &textVAO);
	glDeleteProgram(ProgramID);
	glDeleteProgram(TextID);

	glfwDestroyWindow(window);

	//ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	reportError("clean");
}