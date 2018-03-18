
#ifndef GLUI_CAMERA_H
#define GLUI_CAMERA_H

#include <external/glm/ext.hpp>
#include "config.h"

namespace glui {
	class Camera {
	public:
		inline Camera () {

		}
		inline static void Size (float width, float height) {
			proj = glm::ortho(0.0f, width, height, 0.0f, 0.0f, 100.0f); //glm::ortho(0, width, height, 0, 0, 100);
			view = glm::lookAt(
					glm::vec3(0, 0, 0), // Camera is at (0,0,0), in World Space
					glm::vec3(0, 0, -1), // and looks at the origin
					glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		}
		inline static glm::mat4x4& GetProjection () {
			return proj;
		}
		inline static glm::mat4x4& GetView () {
			return view;
		}
	private:
		static glm::mat4 proj;
		static glm::mat4 view;
	};
};


#endif //GLUI_CAMERA_H
