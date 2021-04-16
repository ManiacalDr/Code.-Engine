// Made by Gregory Watts
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "renderer.h"
#include "sprite.h"

void _ReportError(int ln, const std::string str) {
	GLuint err = glGetError();
	if (!err) return;
	const GLubyte* glerr = gluErrorString(err);
	printf("\n******************************************\n%d: %s: GLError %d: %s\n", ln, str.c_str(), err, glerr);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void KeyboardCB(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		Renderer::updateCam(glm::translate(glm::mat4(1.0f), glm::vec3(0.0,Renderer::speed,0.0)));
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		Renderer::updateCam(glm::translate(glm::mat4(1.0f), glm::vec3(-Renderer::speed, 0.0, 0.0)));
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		Renderer::updateCam(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -Renderer::speed, 0.0)));
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		Renderer::updateCam(glm::translate(glm::mat4(1.0f), glm::vec3(Renderer::speed, 0.0, 0.0)));
	}
}

void glfwErrorCB(int error, const char* description) {
	fputs(description, stderr);
}

void Renderer::initialize() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	reportError("gen");

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	reportError("data");

	ProgramID = LoadShaders("shadervertex.txt", "shaderfragment.txt");
	TextID = LoadShaders("textvertex.txt", "textfragment.txt");
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

void Renderer::updateCam(glm::mat4 update)
{
	cam = glm::vec3(update * glm::vec4(cam,1.0f));
}

Renderer::Renderer()
{
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return; // This might need to return an error code of some sort, failed to initlize;
	}

	//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Open a window and create its OpenGL context

	glfwSetErrorCallback(glfwErrorCB);

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
	if (FT_New_Face(ft, "C:/Windows/Fonts/arial.ttf", 0, &face)) // This line only works for windows, could need to add something for apple 
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;// This might need to return an error code of some sort, failed to initlize;
	}

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

	// Gen and bind textures
	glGenTextures(16, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture (This is going to be called for every sprite we plan to use)
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("assets/textures/failed.jpg", &width, &height, &nrChannels, 3);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	reportError("TextureLoad");

	initialize();

	glfwSetKeyCallback(window, KeyboardCB);//must be called after creating window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//must be called after creating window
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// set uniforms of main program
	glUseProgram(ProgramID);
	glUniform1i(glGetUniformLocation(ProgramID, "atexture"), 0);
	glUniform3f(glGetUniformLocation(ProgramID, "aColor"), 1.0f, 1.0f, 1.0f);
	MVP = glGetUniformLocation(ProgramID, "mvp");

	glm::mat4 p = glm::ortho(-(1080.0f / 2.0f), 1080.0f / 2.0f,
		768.0f / 2.0f, -(768.0f / 2.0f),
		-1000.0f, 1000.0f);
	glm::mat4 v = lookAt(cam, glm::vec3(cam.x, cam.y, -(cam.z+10)), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 m = glm::scale(glm::mat4(1.0), glm::vec3(500.0f,500.0f,500.0f));
	mvp = p * v * m;

	glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);
	// set uniforms of text
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	glUseProgram(TextID);
	glUniformMatrix4fv(glGetUniformLocation(TextID, "projection"), 1, GL_FALSE, &projection[0][0]);

	reportError("First");
}

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

void Renderer::render(Scene& scene) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
	
	if (mode = Renderer::GAME) {
		glUseProgram(ProgramID);
		// bind Texture
		for (int i = 0; i < numTextures; i++) {
			glBindTexture(GL_TEXTURE_2D, texture[i]);

			// render 
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	if (mode = Renderer::EDITOR) {
		glUseProgram(ProgramID);
	}

	glfwSwapBuffers(window);
	glfwPollEvents();

	if (glfwWindowShouldClose(window)) { finish = false; }
	//reportError("render");
}

Renderer::~Renderer()
{
	// Cleanup VBO
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &textVBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &textVAO);
	glDeleteProgram(ProgramID);
	glDeleteProgram(TextID);

	// Close OpenGL window and terminate GLFW
	//glfwTerminate();
	reportError("clean");
}