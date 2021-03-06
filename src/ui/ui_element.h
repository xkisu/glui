
#ifndef GLUI_UI_ELEMENT_H
#define GLUI_UI_ELEMENT_H

#include <vec4.hpp>
#include <vec3.hpp>
#include <vec2.hpp>

#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "graphics/shader.h"
#include "graphics/uniform_container.h"
#include "util/color.h"

namespace glui {
	class UIElement {
	public:
		std::list<UIElement> children;
		Shader * shader;
		Color * color = new Color();

		inline UIElement() {
			SetPosition(0,0);
			SetZIndex(0);
			SetSize(100, 100);
		}

		inline ~UIElement () {
			delete color;
		}

		inline void SetPosition(int x, int y) {
			position.x = x;
			position.y = y;

			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
		}

		inline void SetZIndex(int depth) {
			position.z = depth;
		}

		inline glm::vec3& GetPosition () {
			return position;
		}

		inline void SetSize (int width, int height) {
			size.x = width;
			size.y = height;

			vertices[1].x = size.x;

			vertices[2].x = size.x;
			vertices[2].y = size.y;

			vertices[3].y = size.y;

			UpdateVBO();
		}

		inline glm::vec2& GetSize () {
			return size;
		}

		inline void Draw () {

			// model = glm::translate(model, glm::vec3(.8f, .1f, 0));
			shader->uniforms->SetUniform("model", model);
			glm::vec4 colorVec = color->GetVector();
			shader->uniforms->SetUniform("color", colorVec);

			shader->Bind();

			glBindVertexArray(vao);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(
					0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
			);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

			// Draw the triangle !
			// glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

			glDrawElements(
					GL_TRIANGLES,      // mode
					indices.size(),    // count
					GL_UNSIGNED_INT,   // type
					(void*)0           // element array buffer offset
			);

			glDisableVertexAttribArray(0);
		}
	private:
		glm::vec3 position;
		glm::vec2 size;

		std::vector<glm::vec3> vertices = {
			{0, 0, 0},
			{10, 0, 0},
			{10, 10, 0},
			{0, 10, 0}
		};

		std::vector<unsigned int> indices = {
				3, 1, 0,
				1, 3, 2
		};

		glm::mat4 model = glm::mat4(1.0f);

		GLuint vao = GL_FALSE;
		GLuint vbo = GL_FALSE;
		GLuint ebo = GL_FALSE;

		inline void UpdateVBO () {
			if(vao == GL_FALSE) {
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);

				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec3 ) * vertices.size(), &vertices[0], GL_STATIC_DRAW );

				glGenBuffers(1, &ebo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0] , GL_STATIC_DRAW);
			}else {
				glBindVertexArray(vao);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			}
		}
	};
};


#endif //GLUI_UI_ELEMENT_H
