#pragma once

namespace doyt 
{
	void panic(const char* message, ...);

	void print_glfw_error();

	void initialize();
}