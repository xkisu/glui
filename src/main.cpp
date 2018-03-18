#include <iostream>
#include <physfs.h>
#include <fstream>
#include <sstream>
#include <graphics/shader.h>

#include "graphics/window.h"
#include "graphics/uniform_container.h"
#include "graphics/camera.h"
#include "ui/ui_element.h"

#include "systems/file_manager.h"
#include "systems/renderer.h"

using namespace glui;

int main () {
	std::cout<< "Hello!" <<std::endl;

	Window * window = new Window();

	FileManager::Initialize();
	Renderer::Initialize();
	Shader::Initialize();

	UIElement * element = new UIElement();
	element->shader = Shader::Load("gui");
	element->SetPosition(100, 100);
	element->color->SetG(255);

	int width, height;

	do {
		window->Poll();

		glfwGetFramebufferSize(window->window, &width, &height);
		glViewport(0, 0, width, height);
		Camera::Size((float)width, (float)height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Shader::globalUniforms->SetUniform("proj", Camera::GetProjection());
		Shader::globalUniforms->SetUniform("view", Camera::GetView());

		element->Draw();
	} while (!window->ShouldClose());

	delete element;
	Shader::Uninitialize();
	Renderer::Uninitialize();
	delete window;

	FileManager::Terminate();

	return 0;
}