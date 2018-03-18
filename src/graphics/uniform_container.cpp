#include "uniform_container.h"
#include "shader.h"

namespace glui {
	void UniformContainer::SetUniform (std::string name, glm::mat4& val) {
		mat4Uniforms.insert(std::pair<std::string, glm::mat4&>(name, val));
	}
	void UniformContainer::SetUniform (std::string name, glm::vec4& val) {
		vec4Uniforms.insert(std::pair<std::string, glm::vec4&>(name, val));
	}
	void UniformContainer::SetUniform (std::string name, glm::vec3& val) {
		vec3Uniforms.insert(std::pair<std::string, glm::vec3&>(name, val));
	}
	void UniformContainer::SetUniform (std::string name, glm::vec2& val) {
		vec2Uniforms.insert(std::pair<std::string, glm::vec2&>(name, val));
	}
	void UniformContainer::SetUniform (std::string name, int& val) {
		intUniforms.insert(std::pair<std::string, int&>(name, val));
	}
	void UniformContainer::SetUniform (std::string name, float& val) {
		floatUniforms.insert(std::pair<std::string, float&>(name, val));
	}
	void UniformContainer::BindUniforms (Shader *shader) {
		for (auto const& pair : mat4Uniforms) {
			glUniformMatrix4fv(shader->GetUniformPosition(pair.first), 1, GL_FALSE, &pair.second[0][0]);
		}
		for (auto const& pair : vec4Uniforms) {
			glUniform4f(shader->GetUniformPosition(pair.first), pair.second.x, pair.second.y, pair.second.z, pair.second.y);
		}
		for (auto const& pair : vec3Uniforms) {
			glUniform3f(shader->GetUniformPosition(pair.first), pair.second.x, pair.second.y, pair.second.z);
		}
		for (auto const& pair : vec2Uniforms) {
			glUniform2f(shader->GetUniformPosition(pair.first), pair.second.x, pair.second.y);
		}
		for (auto const& pair : intUniforms) {
			glUniform1i(shader->GetUniformPosition(pair.first), pair.second);
		}
		for (auto const& pair : floatUniforms) {
			glUniform1f(shader->GetUniformPosition(pair.first), pair.second);
		}
	}
};
