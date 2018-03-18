
#include <cstdio>
#include <stdexcept>
#include "window.h"
#include "config.h"

//Define an error callback
static void error_callback(int error, const char* description)  {
	fputs(description, stderr);
	_fgetchar();
}



namespace glui {
	Window::Window () {
		glfwSetErrorCallback(error_callback);

		if (glfwInit()) {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			// glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
			window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
			size = glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT);
			if (!window) {
				// Window or context creation failed
				glfwTerminate();
				throw std::runtime_error("Failed to initialize window");
				// fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
			} else {
				glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

				glfwMakeContextCurrent(window); // Initialize GLEW

				glewExperimental = true; // Needed in core profile
				if (glewInit() != GLEW_OK) {
					// fprintf(stderr, "Failed to initialize GLEW\n");
					throw std::runtime_error("Failed to initialize GLEW");
				}

				// get version info
				const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
				const GLubyte* version = glGetString(GL_VERSION); // version as a string
				printf("Renderer: %s\n", renderer);
				printf("OpenGL version supported %s\n", version);

				// tell GL to only draw onto a pixel if the shape is closer to the viewer
				glEnable(GL_DEPTH_TEST); // enable depth-testing
				glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

				glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
		} else {
			// fprintf( stderr, "Failed to initialize GLFW\n" );
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}
	void Window::Poll () {
		glfwPollEvents();
		glfwSwapBuffers(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	bool Window::ShouldClose () {
		return glfwWindowShouldClose(window);
	}

	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		size = glm::vec2(width, height);
	}
};