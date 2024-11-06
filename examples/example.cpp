// std
#include <iostream>
#include <vector>
#include <cmath>

// OpenGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

// GLUE
// tell glue to use glm::vec2
#define GLUE_VEC2_TYPE glm::vec2
#include <glue/glue.hpp>
#include "./helper.hpp"

const GLint WIDTH = 1600, HEIGHT = 900;
const char *window_title = "GLUE";

const char *vertex_source =
R"(
	#version 330 core
	layout (location = 0) in vec2 aPos;
	void main()
	{
		gl_Position = vec4(aPos, 0.0, 1.0);
	}
)";

const char *fragment_source =
R"(
	#version 330 core
	out vec4 FragColor;
	void main()
	{
		FragColor = vec4(1.0);
	}
)";

int main()
{
	// create window
	GLFWwindow *window = init_window(WIDTH, HEIGHT, window_title);
	if (nullptr == window)
	{
		return EXIT_FAILURE;
	}

	// initialise glew
	if (!init_glew())
	{
		return EXIT_FAILURE;
	}

	// define an interface
	glue::interface main_interface;

	// set its position
	main_interface.position =
	//                  norm                     abs
		glue::udmi2(glm::vec2(0.25f, 0.25f), glm::vec2(0, 0));

	// set its size
	main_interface.size =
	//                  norm                   abs
		glue::udmi2(glm::vec2(0.5f, 0.5f), glm::vec2(0, 0));

	// calculate its screen metrics
	main_interface.calculate_screen_metrics
	(
		glm::vec2(0, 0),
		WIDTH,
		HEIGHT
	);

	// define buffers
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// get the vertices of the interface
	std::vector<float> vertices = main_interface.get_vertices(WIDTH, HEIGHT);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	const std::vector<unsigned int> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// compile program
	unsigned int shader_program = create_shader_program(vertex_source, fragment_source);

	while (!glfwWindowShouldClose(window))
	{
		// clear
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// use program
		glUseProgram(shader_program);

		// draw interface
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return EXIT_SUCCESS;
}