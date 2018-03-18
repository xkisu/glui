
#ifndef GLUI_WINDOW_H
#define GLUI_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vec2.hpp>

namespace glui {
	class Window {

	public:
		glm::vec2 size;

		GLFWwindow * window;

		Window();
		void Poll();
		bool ShouldClose();
	private:
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};
};


#endif //GLUI_WINDOW_H
