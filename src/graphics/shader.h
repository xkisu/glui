
#ifndef GLUI_SHADER_H
#define GLUI_SHADER_H

#include <vector>
#include <stdexcept>
#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <external/glm/ext.hpp>

namespace glui {
	class UniformContainer;

	class Shader {
	public:
		UniformContainer * uniforms;
		static UniformContainer * globalUniforms;

		Shader (std::string name);
		Shader (std::string vert, std::string fragCode, bool code);
		~Shader();
		void Bind ();
		GLint GetUniformPosition (std::string uniform);
	private:
		GLuint vertex_shader, fragment_shader, program;
		std::map<std::string, GLint> uniform_location_cache = {};

		void LinkShader (std::string vertCode, std::string fragCode);

		bool ShaderCheckErrors (GLuint shader);
		bool ProgramCheckErrors (GLuint program);
	};
};

#endif //GLUI_SHADER_H
