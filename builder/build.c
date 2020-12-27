#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void panic(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
	exit(-1);
}

int main(int argc, char** argv)
{
	if (argc <= 1) 
	{
		panic("No build file has been provided!");
	}
	
	char *filename    = argv[1];
	FILE *build_file  = fopen(filename, "r");
	char *read_buffer = NULL;
	long  read_buffer_length;

	if (build_file)
	{
		fseek (build_file, 0, SEEK_END);
		read_buffer_length = ftell (build_file);
		fseek (build_file, 0, SEEK_SET);
		
		// allocate space for build file content
		read_buffer = calloc (1, read_buffer_length);

		if (read_buffer)
		{
			fread (read_buffer, 1, read_buffer_length, build_file);
		}
		else
		{
			panic("Could allocate buffer to read file: %s\n", filename);
		}

		fclose (build_file);
	}
	else 
	{
		panic("Could not read file: %s\n", filename);
	}

	for (long index = 0; index < read_buffer_length; index++)
	{
		if      (read_buffer[index] == '\n') read_buffer[index] = ' ';
		else if (read_buffer[index] == '\t') read_buffer[index] = ' ';
		else if (read_buffer[index] == '\r') read_buffer[index] = ' ';
	}

	// prints build command
	printf(
		"====== Running build command ======\n"
		"%s\n"
		"===================================\n"
		, 
		read_buffer
	);
	_flushall();

	// executes build command
	system(read_buffer);
}