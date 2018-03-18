
#ifndef GLUI_WINDOW_H
#define GLUI_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace glui {
	class Window {

	public:
		GLFWwindow * window;

		Window();
		void Poll();
		bool ShouldClose();
	};
};


#endif //GLUI_WINDOW_H
