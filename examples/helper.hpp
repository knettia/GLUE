#pragma once

// std
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// stb
#include <stb_image.h>

bool init_glew()
{
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);

	return true;
}

GLFWwindow *init_window(const unsigned int WIDTH = 1600, const unsigned int HEIGHT = 900, const char *WINDOW_TITLE = "GLUE")
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << '\n';
		return nullptr;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	return window;
}

unsigned int compile_shader(unsigned int type, const char *source)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "Error: Shader Compilation Failed\n"
			<< infoLog << std::endl;
	}
	return shader;
}

unsigned int create_shader_program(const char *vertex_source, const char *fragment_source )
{
	unsigned int vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
	unsigned int fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
	unsigned int shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return shader_program;
}

unsigned int load_texture(const char* filename)
{
	unsigned int texture;
	glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

        if (data) {
                GLenum format = GL_RGB;
                switch (nrChannels) {
                        case 1:
                                format = GL_RED;
                                break;
                        case 3:
                                format = GL_RGB;
                                break;
                        case 4:
                                format = GL_RGBA;
                                break;
                        default:
                                std::cout << "Unsupported number of channels: " << nrChannels << std::endl;
                                stbi_image_free(data);
                        return 0;
                }

                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
        } else {
                std::cout << "Failed to load texture!" << std::endl;
        }

        stbi_image_free(data);
	return texture;
}