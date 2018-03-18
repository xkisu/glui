
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

#include "config.h"

namespace glui {
	class UniformContainer;

	class Shader {
	public:
		UniformContainer * uniforms;
		static UniformContainer * globalUniforms;
		static Shader * activeShader;

		Shader (std::string name);
		Shader (std::string vert, std::string fragCode, bool code);
		~Shader();
		static Shader* Load(std::string name);

		void Bind ();
		GLint GetUniformPosition (std::string uniform);

		inline static void Initialize () {
			for(const std::string &shader : shaders)
				Load(shader);
		}
		inline static void Uninitialize () {
			for (auto it = shaderCache.cbegin(); it != shaderCache.cend() /* not hoisted */; /* no increment */) {
				delete it++->second;
				// shaderCache.erase(it++);    // or "it = m.erase(it)" since C++11
			}
		}
		inline static std::map<std::string, Shader*>& GetCache () {
			return shaderCache;
		};
	private:
		GLuint vertex_shader, fragment_shader, program;
		std::map<std::string, GLint> uniform_location_cache = {};
		static std::map<std::string, Shader*> shaderCache;

		void LinkShader (std::string vertCode, std::string fragCode);

		bool ShaderCheckErrors (GLuint shader);
		bool ProgramCheckErrors (GLuint program);
	};
};

#endif //GLUI_SHADER_H
