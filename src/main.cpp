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

	Shader * shader = new Shader("gui");

	UIElement * element = new UIElement();
	element->shader = shader;
	element->SetPosition(100, 100);
	element->color->SetG(255);



	int width, height;

	do {
		window->Poll();

		glfwGetFramebufferSize(window->window, &width, &height);
		glViewport(0, 0, width, height);
		Camera::Size((float)width, (float)height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->globalUniforms->SetUniform("proj", Camera::GetProjection());
		shader->globalUniforms->SetUniform("view", Camera::GetView());

		element->Draw();
	} while (!window->ShouldClose());

	delete element;
	delete shader;
	delete window;

	PHYSFS_deinit();

	return 0;
}