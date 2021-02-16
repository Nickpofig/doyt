// std
#include <iostream>

// GLFW declaration
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// engine
#include "core.h"

static unsigned int compile_shader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char *raw_source = source.c_str();
	glShaderSource(id, 1, &raw_source, nullptr);
	glCompileShader(id);

	int is_compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == GL_FALSE)
	{
		int log_length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
		char *log = (char*)alloca(log_length * sizeof(char));
		glGetShaderInfoLog(id, log_length, &log_length, log);
		std::cout << "Failed to compile" << type << " shader!" << std::endl;
		std::cout << log << std::endl;

		return 0;
	}

	return id;
}

static unsigned int create_shader_program
(
	const std::string& vertex_shader_soruce, 
	const std::string& fragment_shader_source
)
{
	unsigned int program = glCreateProgram();
	unsigned int vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_soruce);
	unsigned int fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}


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

	// Trianlge test data
	float vertex_positions[6] = 
	{
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	std::string vertex_shader_source = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";


	std::string fragment_shader_source = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertex_positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	unsigned int shader_program = create_shader_program(
		vertex_shader_source, 
		fragment_shader_source
	);
	glUseProgram(shader_program); 

	// Loops until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}