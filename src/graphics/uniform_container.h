
#ifndef GLUI_UNIFORM_CONTAINER_H
#define GLUI_UNIFORM_CONTAINER_H

#include <string>
#include <map>

#include <glm.hpp>
#include <vec3.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace glui {
	class Shader;

	class UniformContainer {
	public:
		void SetUniform (std::string name, glm::mat4& val) ;
		void SetUniform (std::string name, glm::vec4& val);
		void SetUniform (std::string name, glm::vec3& val);
		void SetUniform (std::string name, glm::vec2& val);
		void SetUniform (std::string name, int& val);
		void SetUniform (std::string name, float& val);
		void BindUniforms (Shader *shader);
	private:
		std::map<std::string, glm::mat4&> mat4Uniforms = {};
		std::map<std::string, glm::vec4&> vec4Uniforms = {};
		std::map<std::string, glm::vec3&> vec3Uniforms = {};
		std::map<std::string, glm::vec2&> vec2Uniforms = {};
		std::map<std::string, int&> intUniforms = {};
		std::map<std::string, float&> floatUniforms = {};
	};

};

#endif //GLUI_UNIFORM_CONTAINER_H
