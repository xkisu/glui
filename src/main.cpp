#include <iostream>
#include <physfs.h>
#include <fstream>
#include <sstream>
#include <graphics/shader.h>

#include "graphics/window.h"
#include "graphics/uniform_container.h"
#include "graphics/camera.h"
#include "ui/ui_element.h"

using namespace glui;

int main () {
	std::cout<< "Hello!" <<std::endl;

	Window * window = new Window();


	if(PHYSFS_init(NULL) != 1) {
		throw std::runtime_error("Error initializing PHYSFS!");
	}


	PHYSFS_mount("shaders/", "/shaders", false);

	Shader * shader = new Shader("basic");
	UIElement * element = new UIElement();

	do {
		window->Poll();

		float ratio;
		int width, height;
		glfwGetFramebufferSize(window->window, &width, &height);
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Camera::Size((float)width, (float)height);

		shader->uniforms->SetUniform("proj", Camera::GetProjection());
		shader->uniforms->SetUniform("view", Camera::GetView());
		glm::mat4 model = glm::mat4(1.0f);
		// model = glm::translate(model, glm::vec3(.8f, .1f, 0));
		shader->uniforms->SetUniform("model", model);

		shader->Bind();

		element->Draw();
	} while (!window->ShouldClose());

	delete element;
	delete shader;
	delete window;

	PHYSFS_deinit();

	return 0;
}