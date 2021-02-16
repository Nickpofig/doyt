// std
#include <iostream>

// GLFW declaration
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// engine
#include "core.h"

int main()
{
	doyt::initialize();

	std::cout << "Doyt!" << std::endl;

	if (!glfwInit())
	{
		doyt::panic("GLFW failed to initialize!");
	}

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	int monitor_x       = 0, 
	    monitor_y       = 0, 
		monitor_width   = 0, 
		monitor_height  = 0;
	
	glfwGetMonitorWorkarea(monitor, &monitor_x, &monitor_y, &monitor_width, &monitor_height);
	
	// Creates a window
	GLFWwindow *window = glfwCreateWindow(
		monitor_width, 
		monitor_height, 
		"Hello World", 
		monitor,
		NULL
	);
	
	std::cout << "x: " << monitor_x 
	          << ", y: " << monitor_y 
	          << ", width: " << monitor_width 
	          << ", height: " << monitor_height 
	<< std::endl;
	
	glfwSetWindowMonitor(
		window, 
		monitor, 
		monitor_x, 
		monitor_y, 
		monitor_width, 
		monitor_height, 
		GLFW_DONT_CARE
	);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

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