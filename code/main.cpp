// std
#include <iostream>
#include <cstdarg>

// GLFW declaration
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void panic(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	std::vprintf(message, args);
	va_end(args);
	exit(-1);
}

void print_mouse_position(GLFWwindow* window, double x, double y)
{
	std::cout << "mouse: [" << x << ", " << y << "]" << std::endl;
}

int main()
{
	std::cout << "Doyt!" << std::endl;

	if (!glfwInit())
	{
		panic("GLFW failed to initialize!");
	}

	// Creates a window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, print_mouse_position);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	// Loops until the user closes the window
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