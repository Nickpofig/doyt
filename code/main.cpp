// C++ libraries
#include <iostream>

// C libraries
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"

// GLFW declaration
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void panic(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
	exit(-1);
}

int main()
{
	std::cout << "Doyt!" << std::endl;

	if (!glfwInit())
	{
		panic("GLFW failed to initialize!");
	}

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}