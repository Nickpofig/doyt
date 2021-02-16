#include <iostream>
#include <cstdarg>
#include <GLFW/glfw3.h>

namespace doyt 
{
	void handle_glfw_error(int code, const char *message)
	{
		std::cerr << "[Error:" << code << "] " << message << std::endl;
	}

	void panic(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		std::vprintf(message, args);
		va_end(args);
		exit(-1);
	}

	void initialize()
	{
		glfwSetErrorCallback(handle_glfw_error);
	}
}