#include "shader.h"
#include "uniform_container.h"

#include <physfs.h>
#include <systems/file_manager.h>

namespace glui {
	/* static std::string LoadShaderCode (std::string name) {
		std::string s = "/shaders/" + name;
		const char * path = s.c_str();
		if(!PHYSFS_exists(path)) {
			// throw std::runtime_error("vert doesn't exist!");
			return std::string("");
		}
		char *buf;
		PHYSFS_file *vertFile = PHYSFS_openRead(path);
		int len = PHYSFS_fileLength(vertFile);
		buf = new char[len+1];
		int length_read = PHYSFS_readBytes (vertFile, buf, len);
		buf[len] = '\0';
		PHYSFS_close(vertFile);

		return std::string(buf);
	} */

	Shader::Shader (std::string name) {
		std::string vert = FileManager::ReadFileText("/shaders/" + name + std::string(".vert"));
		std::string frag = FileManager::ReadFileText("/shaders/" + name + std::string(".frag"));

		if(vert.size() <= 0) {
			throw std::runtime_error("Vertex shader does not exist!");
		}
		if(frag.size() <= 0) {
			throw std::runtime_error("Fragment shader does not exist!");
		}

		LinkShader(vert, frag);
	}

	Shader::Shader (std::string vertCode, std::string fragCode, bool code = false) {
		if(code) {
			LinkShader(vertCode, fragCode);
		} else {
			std::string vert = FileManager::ReadFileText("/shaders/" + vertCode);
			std::string frag = FileManager::ReadFileText("/shaders/" + fragCode);

			LinkShader(vert, frag);
		}
	}

	Shader::~Shader () {
		if(program != GL_FALSE) {
			glUseProgram(0);
			glDeleteProgram(program);
		}
	}

	Shader * Shader::Load (std::string name) {
		auto iter = shaderCache.find(name);
		if (iter != shaderCache.end() ) {
			return iter->second;
		} else {
			Shader * shader = new Shader(name);
			shaderCache.insert(std::pair<std::string, Shader*>(name, shader));
		}
	}

	void Shader::Bind () {
		glUseProgram(program);
		globalUniforms->BindUniforms(this);
		uniforms->BindUniforms(this);
		activeShader = this;
	}

	void Shader::LinkShader (std::string vertCode, std::string fragCode) {
		uniforms = new UniformContainer();
		const char * vert = vertCode.c_str();
		const char * frag = fragCode.c_str();

		GLint success = 0;

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		int len = strlen(vert);
		glShaderSource(vertex_shader, 1, &vert, &len);
		glCompileShader(vertex_shader);

		if(ShaderCheckErrors(vertex_shader)) {
			throw std::runtime_error("Vertex shader failed to compile!");
		}

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		len = strlen(frag);
		glShaderSource(fragment_shader, 1, &frag, &len);
		glCompileShader(fragment_shader);

		if(ShaderCheckErrors(fragment_shader)) {
			throw std::runtime_error("Fragment shader failed to compile!");
		}

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		if(ProgramCheckErrors(program)) {
			throw std::runtime_error("Program failed to link!");
		}

		glDetachShader(program, vertex_shader);
		glDetachShader(program, fragment_shader);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	GLint Shader::GetUniformPosition (std::string uniform) {
		auto iter = uniform_location_cache.find(uniform);
		if (iter != uniform_location_cache.end() ) {
			// key 2 exists, do something with iter->second (the value)
			return iter->second;
		} else {
			auto location = glGetUniformLocation(program, uniform.c_str());
			uniform_location_cache.insert(std::pair<std::string, GLint>(uniform, location));
			return location;
		}

	}

	bool Shader::ShaderCheckErrors (GLuint shader) {
		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			std::string s(begin(errorLog), end(errorLog));

			fprintf(stderr, s.c_str());

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shader); // Don't leak the shader.
			return true;
		}

		return false;
	}

	bool Shader::ProgramCheckErrors (GLuint program) {
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)  {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			std::string s(begin(infoLog), end(infoLog));

			fprintf(stderr, s.c_str());

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return true;
		}
		return false;
	}
	UniformContainer * Shader::globalUniforms = new UniformContainer();
	Shader * Shader::activeShader;
	std::map<std::string, Shader*> Shader::shaderCache;
};
