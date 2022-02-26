#include "OGpch.h"

#include "OpenGLShader.h"

#include "glad/glad.h"

#include "Origin/Utility/FileSystem/FileStream.h"

#include <glm/gtc/type_ptr.hpp>

namespace Origin {

	OpenGLShader::OpenGLShader(const char * vertex_path, const char* fragment_path)
		: m_vertex_path(vertex_path), m_fragment_path(fragment_path){

		FileStream vertex_shader_file(vertex_path);
		FileStream fragment_shader_file(fragment_path);

		std::string parsed_vertex_shader = vertex_shader_file.Read();
		std::string parsed_fragment_shader = fragment_shader_file.Read();


		uint32_t vertex_shader = CreateShader(GL_VERTEX_SHADER, parsed_vertex_shader);
		uint32_t fragment_shader = CreateShader(GL_FRAGMENT_SHADER, parsed_fragment_shader);

		
		m_ID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_ID, vertex_shader);
		glAttachShader(m_ID, fragment_shader);

		// Link our program
		glLinkProgram(m_ID);

		int isLinked = 0;
		glGetProgramiv(m_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_ID);
			// Don't leak shaders either.
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			// Use the infoLog as you see fit.
			ORIGIN_ASSERT(true, "[Shader Error] Could not link program: {0}", infoLog.data());
			// In this simple program, we'll just leave
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_ID, vertex_shader);
		glDetachShader(m_ID, fragment_shader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform(std::string name, int x) {
		glUseProgram(m_ID);
		uint32_t location = GetUniformLocation(name);
		glUniform1i(location, x);
	}

	void OpenGLShader::UploadUniform(std::string name, bool x) {
		glUseProgram(m_ID);
		uint32_t location = GetUniformLocation(name);
		glUniform1i(location, x);
	}

	void OpenGLShader::UploadUniform(std::string name, double x) {
		glUseProgram(m_ID);
		uint32_t location = GetUniformLocation(name);
		glUniform1d(location, x);
	}

	void OpenGLShader::UploadUniform(std::string name, float x) {
		glUseProgram(m_ID);
		uint32_t location = GetUniformLocation(name);
		glUniform1f(location, x);
	}

	void OpenGLShader::UploadUniform(std::string name, glm::vec3 vec) {
		glUseProgram(m_ID);
		uint32_t location = GetUniformLocation(name);
		glUniform3f(location, vec.x, vec.z, vec.y);
	}

	void OpenGLShader::UploadUniform(std::string name, glm::vec4 vec) {
		glUseProgram(m_ID);
		uint32_t location = GetUniformLocation(name);
		glUniform4f(location, vec.x, vec.z, vec.y, vec.z);
	}

	void OpenGLShader::UploadUniform(std::string name, glm::mat4 mat) {
		glUseProgram(m_ID);
		uint32_t location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(mat));
	}

	uint32_t OpenGLShader::GetUniformLocation(std::string name) {
		if (m_uniform_map.find(name) != m_uniform_map.end()) {
			return m_uniform_map[name];
		}
		uint32_t uniform_location = glGetUniformLocation(m_ID, name.c_str());
		m_uniform_map.insert({ name, uniform_location });
		return m_uniform_map[name];
	}

	uint32_t OpenGLShader::CreateShader(uint32_t type, const std::string& shader) const {
		uint32_t ID = glCreateShader(type);
		const char* src = shader.c_str();

		glShaderSource(ID, 1, &src, nullptr);
		glCompileShader(ID);

		int result = 0;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
		if (!result) {
			GLint maxLength = 0;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(ID, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(ID);

			ORIGIN_ASSERT(true, "[SHADER ERRPR] {0}", infoLog.data());
		}
		return ID;
	}
}