// === REMARK ===
// Well, this is my kind of a ...build system.
//
// I basically do not like and don't want to waste my time in learning a "modern" build system.
// That is why, I wrote, basically, a simple terminal command supplier.    :D
// And it clearly not an actual build system. yet.
//
// Maybe, I will upgrade it later on, but for now - it does its job.    :I
//
// And, honestly, I am not even sure what I want from it (besides stupid simplicity)    :/
// ==============


// Just to remove Windows annoying stuff    -_-
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void panic(const char *message, ...)
{
	va_list args;
	va_start(args, message);
	fprintf(stderr, "[Builder]");
	vfprintf(stderr, message, args);
	fflush(stderr);
	va_end(args);
	exit(EXIT_FAILURE);
}

void ignore_until_newline(const char *input, int length, int *index)
{
	do
	{
		if (input[*index] == '\n') return;
		(*index)++;
	}
	while(*index < length);
}

void ignore_comment(const char *input, int length, int *index)
{
	do
	{
		if (input[*index] != '#') return;
		ignore_until_newline(input, length, index);
	}
	while(*index < length);
}

char* read_label(char *input, int length, int *index)
{
	char *result = calloc(length - *index, sizeof(char));

	int result_index = 0;
	int is_previous_newline = 0;

	// Skips first '@' label character.
	(*index)++;

	for (; *index < length; (*index)++)
	{
		if (input[*index] == '\n') is_previous_newline = 1;
		else if (input[*index] == '@' && is_previous_newline) continue;
		else if (is_previous_newline) break;
		else 
		{
			result[result_index] = input[*index];
			result_index++;
			is_previous_newline  = 0;
		}
	}

	// Makes sure we wont lose last read character.
	(*index)--; 

	// Trims result buffer.
	result = realloc(result, result_index + 1);
	result[result_index] = '\0';

	return result;
}

int execute_next_command(char *input, int input_length, int *input_index)
{
	char *label = NULL;
	char *output = calloc(input_length, sizeof(char));
	if (!output) panic("Could not allocate output!\n");


	int output_index = 0;

	int is_previous_newline    = 1;
	int is_previous_whitespace = 0;
	int is_current_whitespace;

	for (; *input_index < input_length; (*input_index)++)
	{
		is_current_whitespace = 0;

		if      (input[*input_index] == '\n') is_current_whitespace = 1;
		else if (input[*input_index] == '\t') is_current_whitespace = 1;
		else if (input[*input_index] == '\r') is_current_whitespace = 1;
		else if (input[*input_index] == ' ' ) is_current_whitespace = 1;
		else if (input[*input_index] == '#' && is_previous_newline) 
		{
			ignore_comment(input, input_length, input_index);
			continue;
		}
		else if (input[*input_index] == '@' && is_previous_newline)
		{
			label = read_label(input, input_length, input_index);
			continue;
		}
		// Checks for a command separation
		else if (input[*input_index] == '=' && is_previous_newline)
		{
			ignore_until_newline(input, input_length, input_index);
			break;
		}
		else 
		{
			output[output_index] = input[*input_index];
			output_index++;
		}
		
		if (is_current_whitespace && !is_previous_whitespace) 
		{
			output[output_index] = ' ';
			output_index++;
		}

		is_previous_whitespace = is_current_whitespace;
		is_previous_newline       = input[*input_index] == '\n';
	}


	// Trims the output (a.k.a the builded command)
	output = realloc(output, output_index + 1);
	output[output_index] = '\0';
	if (!output) panic("Could not reallocate output!\n");

	// Prints the builded command
	if (label) printf("~>%s\n", label);
	printf("%s\n", output);
	fflush(stdout);

	// Executes the builded command
	int error_code = system(output);
	
	free(output);

	return error_code;
}


int main(int argc, char **argv)
{
	char *filename     = NULL;
	int is_sub_process = 0;

	for (int i = 1; i < argc; i++)
	{
		filename = argv[i];
	}

	if (!filename) 
	{
		panic("No build file has been provided!\n");
	}
	
	
	FILE *build_file  = fopen(filename, "r");
	char *read_buffer = NULL;
	long  read_buffer_length;

	if (build_file)
	{
		fseek (build_file, 0, SEEK_END);
		read_buffer_length = ftell (build_file);
		fseek (build_file, 0, SEEK_SET);
		
		// allocate space for build file content
		read_buffer = calloc (read_buffer_length, sizeof(char));

		if (read_buffer)
		{
			fread (read_buffer, 1, read_buffer_length, build_file);
		}
		else
		{
			panic("Could allocate buffer to read file: %s\n!", filename);
		}

		fclose (build_file);
	}
	else 
	{
		panic("Could not read file: %s\n!", filename);
	}

	int read_buffer_index = 0;
	int error_code        = EXIT_SUCCESS;

	for (int number = 1; read_buffer_index < read_buffer_length; number++)
	{
		error_code = execute_next_command(read_buffer, read_buffer_length, &read_buffer_index);
		if (error_code) 
		{
			break;
		}
	}
	
	free(read_buffer);

	return error_code;
}