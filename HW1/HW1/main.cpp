#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"
#include "Shader.h"

using namespace std;
int degree_to_rotate = 1;
float animal_degree = 1;
int tower_degree = 1;
bool tower_rotate = false;
float animal_speed = 1;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
unsigned int modelVAO(Object& model);
void drawModel(const string& target, unsigned int& shaderProgram, const glm::mat4& M, const glm::mat4& V, const glm::mat4& P);

// Objects to display
Object rectangleModel("obj/rectangle.obj");
Object triangleModel("obj/triangle.obj");
Object clockModel("obj/clock.obj");
Object clockHandModel("obj/clock_hand.obj");
Object rabbitModel("obj/rabbit.obj");
Object tortoiseModel("obj/tortoise.obj");

unsigned int rectangleVAO, triangleVAO, clockVAO, clockHandVAO, rabbitVAO, tortoiseVAO;
int windowWidth = 800, windowHeight = 600;

int main()
{
	// Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFE_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "HW1", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD\n";
		return -1;
	}

	// VAO, VBO
	rectangleVAO = modelVAO(rectangleModel);
	triangleVAO = modelVAO(triangleModel);
	clockVAO = modelVAO(clockModel);
	clockHandVAO = modelVAO(clockHandModel);
	rabbitVAO = modelVAO(rabbitModel);
	tortoiseVAO = modelVAO(tortoiseModel);

	// Shaders
	Shader shader("vertexShader.vert", "fragmentShader.frag");
	glUseProgram(shader.program);

	// TODO: Enable depth test, face culling
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Display loop
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	double lastTime = glfwGetTime();
	int numFrames = 0;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate time per frame
		double currentTime = glfwGetTime();
		numFrames++;
		// If last cout was more than 1 sec ago
		if (currentTime - lastTime >= 1.0)
		{
			// Print and reset timer
			cout << 1000.0 / numFrames << " ms/frame\n";
			numFrames = 0;
			lastTime += 1.0;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		degree_to_rotate++;
		if (tower_rotate) {
			tower_degree++;
		}
		animal_degree += animal_speed;
		// TODO: Create model, view, and perspective matrix
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 30.0f, 50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

		// TODO: Draw base of clock tower
		glm::mat4 base(1.0f);
		base = glm::translate(base, glm::vec3(0.0f, -10.0f, -3.0f));
		base = glm::scale(base, glm::vec3(20.0f, 1.0f, 21.0f));
		drawModel("rectangle", shader.program, base, view, perspective);

		// TODO: Draw body of clock tower
		base = glm::scale(base, glm::vec3(1 / 20.0f, 1 / 1.0f, 1 / 21.0f));
		glm::mat4 body = glm::translate(base, glm::vec3(0.0f, 15.0f, 3.0f));
		body = glm::scale(body, glm::vec3(4.5f, 10.0f, 3.5f));
		body = glm::rotate(body, glm::radians(tower_degree * 0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		drawModel("rectangle", shader.program, body, view, perspective);
		// TODO: Draw roof of clock tower
		body = glm::scale(body, glm::vec3(1 / 4.5f, 1 / 10.0f, 1 / 3.5f));
		glm::mat4 roof = glm::translate(body, glm::vec3(-0.2f, 11.25f, -0.35f));
		roof = glm::scale(roof, glm::vec3(5.0f, 4.0f, 3.3f));
		drawModel("triangle", shader.program, roof, view, perspective);

		// TODO: Draw clock on the clock tower
		glm::mat4 clock = glm::translate(body, glm::vec3(0.0f, 4.5f, 4.3f));
		clock = glm::scale(clock, glm::vec3(0.013f, 0.013f, 0.013f));
		clock = glm::rotate(clock, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		drawModel("clock", shader.program, clock, view, perspective);

		// TODO: Draw minute hand on the clock 
		clock = glm::rotate(clock, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		clock = glm::scale(clock, glm::vec3(1 / 0.013f, 1 / 0.013f, 1 / 0.013f));
		glm::mat4 min = glm::translate(clock, glm::vec3(0.0f, 0.0f, 0.6f));
		min = glm::scale(min, glm::vec3(0.8f, 0.7f, 1.0f));
		min = glm::rotate(min, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		min = glm::rotate(min, glm::radians(animal_degree * 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		drawModel("clock hand", shader.program, min, view, perspective);

		// TODO: Draw hour hand on the clock
		glm::mat4 hour = glm::translate(clock, glm::vec3(0.0f,0.0f,0.25f));
		hour = glm::rotate(hour, glm::radians(-180.0f), glm::vec3(0.0f,1.0f,0.0f));
		hour = glm::rotate(hour, glm::radians(animal_degree * (1/60.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		hour = glm::scale(hour, glm::vec3(1.0f,0.6f,0.6f));
		drawModel("clock hand", shader.program, hour, view, perspective);

		// TODO: Draw rabbit revolves around the clock tower (not (0, 0, 0))
		glm::mat4 rabbit = glm::translate(base, glm::vec3(0.0f, 10.0f, 3.0f));
		rabbit = glm::rotate(rabbit,glm::radians(animal_degree * (-0.7f)), glm::vec3(0.0f,1.0f,0.0f));
		rabbit = glm::translate(rabbit, glm::vec3(15.0f, -9.0f, 3.0f));
		rabbit = glm::scale(rabbit, glm::vec3(0.08f, 0.08f, 0.08f));
		drawModel("rabbit", shader.program, rabbit, view, perspective);

		// TODO: Draw tortoise revolves around the clock tower (not (0, 0, 0))
		glm::mat4 turtle = base;
		turtle = glm::rotate(turtle, glm::radians(animal_degree * (-0.35f)), glm::vec3(0.0f, 1.0f, 0.0f));
		turtle = glm::translate(turtle, glm::vec3(18.0f, 1.5f, 0.0f));
		turtle = glm::scale(turtle, glm::vec3(0.2f, 0.2f, 0.2f));
		turtle = glm::rotate(turtle, glm::radians(-180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		turtle = glm::rotate(turtle, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		turtle = glm::rotate(turtle, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		drawModel("tortoise", shader.program, turtle, view, perspective);

		// TODO: Control speed and rotation


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// TODO:
//	 1. press 1 to double the rotation speed
//   2. press 2 to halve the rotation speed
//   3. press 3 to rotate the clock tower
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		animal_speed *= 2;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		animal_speed /= 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		if (tower_rotate) {
			tower_rotate = false;
		}
		else {
			tower_rotate = true;
		}
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
}

unsigned int modelVAO(Object& model)
{
	unsigned int VAO, VBO[3];
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model.positions.size()), &(model.positions[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model.normals.size()), &(model.normals[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model.texcoords.size()), &(model.texcoords[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}

void drawModel(const string& target, unsigned int& shaderProgram, const glm::mat4& M, const glm::mat4& V, const glm::mat4& P)
{
	unsigned int mLoc, vLoc, pLoc;
	mLoc = glGetUniformLocation(shaderProgram, "M");
	vLoc = glGetUniformLocation(shaderProgram, "V");
	pLoc = glGetUniformLocation(shaderProgram, "P");
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));

	if (target == "rectangle")
	{
		glBindVertexArray(rectangleVAO);
		glDrawArrays(GL_TRIANGLES, 0, rectangleModel.positions.size());
	}
	else if (target == "triangle")
	{
		glBindVertexArray(triangleVAO);
		glDrawArrays(GL_TRIANGLES, 0, triangleModel.positions.size());
	}
	else if (target == "clock")
	{
		glBindVertexArray(clockVAO);
		glDrawArrays(GL_TRIANGLES, 0, clockModel.positions.size());
	}
	else if (target == "clock hand")
	{
		glBindVertexArray(clockHandVAO);
		glDrawArrays(GL_TRIANGLES, 0, clockHandModel.positions.size());
	}
	else if (target == "rabbit")
	{
		glBindVertexArray(rabbitVAO);
		glDrawArrays(GL_TRIANGLES, 0, rabbitModel.positions.size());
	}
	else if (target == "tortoise")
	{
		glBindVertexArray(tortoiseVAO);
		glDrawArrays(GL_TRIANGLES, 0, tortoiseModel.positions.size());
	}
	glBindVertexArray(0);
}