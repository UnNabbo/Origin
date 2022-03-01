
#include "OGpch.h"

#include "OpenGLShader.h"


#include "Origin/Utility/FileSystem/FileStream.h"

#include <glm/gtc/type_ptr.hpp>

namespace Origin {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		ORIGIN_ASSERT(false, "{0} is an unsupported shader type!", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const char * vertex_path, const char* fragment_path)
		: m_vertex_path(vertex_path), m_fragment_path(fragment_path){

		FileStream vertex_shader_file(vertex_path);
		FileStream fragment_shader_file(fragment_path);

		std::unordered_map<GLenum, std::string> shaderSources;

		shaderSources[GL_VERTEX_SHADER] = vertex_shader_file.Read();
		shaderSources[GL_FRAGMENT_SHADER] = fragment_shader_file.Read();

		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const char* path)
		: m_vertex_path(path), m_fragment_path(path) {

		FileStream shader_file(path);

		std::string parsed_shader = shader_file.Read();

		auto shaders = PreProcess(parsed_shader);

		Compile(shaders);
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

	uint32_t OpenGLShader::CreateShader(uint32_t type, const std::string& shaderSrc) const {
		uint32_t shader = glCreateShader(type);
		const char* src = shaderSrc.c_str();

		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		int result = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (!result) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			ORIGIN_ASSERT(true, "[SHADER ERRPR] {0}", infoLog.data());
		}
		return shader;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs;
		glShaderIDs.reserve(shaderSources.size());
		for (auto& value : shaderSources) {
			uint32_t shader = glCreateShader(value.first);
			const std::string& src = value.second;

			const GLchar* srcCstr = src.c_str();
			glShaderSource(shader, 1, &srcCstr, nullptr);
			glCompileShader(shader);

			GLint result = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (!result) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				ORIGIN_ASSERT(false, "[SHADER ERRPR] {0}", infoLog.data());
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

		m_ID = program;
		// Link our program
		glLinkProgram(program);

		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs) {
				glDeleteShader(id);

			}

			// Use the infoLog as you see fit.
			ORIGIN_ASSERT(true, "[Shader Error] Could not link program: {0}", infoLog.data());
			// In this simple program, we'll just leave

		}
		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
			glDetachShader(program, id);
		}
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#Type";
		size_t typeTokenLenght = strlen(typeToken);
		size_t pos = src.find_first_of(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = src.find_first_of("\r\n", pos);
			ORIGIN_ASSERT(eol == std::string::npos, "Systax Error");
			size_t begin = pos + typeTokenLenght + 1;
			std::string type = src.substr(begin, eol - begin);
			ORIGIN_ASSERT(ShaderTypeFromString(type), "Invalid shader type specifed");


			size_t nextLinePos = src.find_first_of("\r\n", eol);
			pos = src.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
		}
		return shaderSources;
	}
}