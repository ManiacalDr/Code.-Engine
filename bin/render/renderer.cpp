// Made by Gregory Watts
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "renderer.h"

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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	programID = LoadShaders("shadervertex.txt", "shaderfragment.txt");
	reportError("shader");

	GLuint pos, texCoord;
	// position attribute
	pos = glGetAttribLocation(programID, "aPos");
	if (pos < 0) std::cerr << "couldn't find vPosition in shader\n";
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(pos);
	// texture coord attribute
	texCoord = glGetAttribLocation(programID, "aTexCoord");
	if (texCoord < 0) std::cerr << "couldn't find texCoord in shader\n";
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(texCoord);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	reportError("init");
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

	window = glfwCreateWindow(1024, 768, "Code.", NULL, NULL);
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

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture (This is going to be called for every sprite we plan to use)
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 3);
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

	initialize();


	glfwSetKeyCallback(window, KeyboardCB);//must be called after creating window
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//must be called after creating window
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glUseProgram(programID);
	glUniform1i(glGetUniformLocation(programID, "atexture"), 0);
	glUniform3f(glGetUniformLocation(programID, "aColor"), 1.0f, 1.0f, 1.0f);
	reportError("First");
}

void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// bind Texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// render 
	glUseProgram(programID);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0,6);

	glfwSwapBuffers(window);
	glfwPollEvents();

	if (glfwWindowShouldClose(window)) { finish = false; }
	//reportError("render");
}

Renderer::~Renderer()
{
	// Cleanup VBO
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	reportError("clean");
}