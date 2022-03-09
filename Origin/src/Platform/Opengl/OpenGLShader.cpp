
#include "OGpch.h"

#include "OpenGLShader.h"

#include "Origin/Utility/FileSystem/FileStream.h"

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>


namespace Origin {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		if (type == "geometry") return GL_GEOMETRY_SHADER;
		ORIGIN_ASSERT(false, "{0} is an unsupported shader type!", type);
		return 0;
	}

	static std::string ShaderTypeFromGLenum(GLenum type) {
		if (type == GL_VERTEX_SHADER) return "VERTEX";
		if (type == GL_FRAGMENT_SHADER) return "FRAGMENT";
		if (type == GL_GEOMETRY_SHADER) return "GEOMETRY";
		ORIGIN_ASSERT(false, "{0} is an unsupported shader type!", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const char * name, const char * vertex_path, const char* fragment_path)
		: m_vertexPath(vertex_path), m_fragmentPath(fragment_path), m_name(name){

		Reference<FileStream> vertexShaderFile = FileStream::Create(vertex_path);
		Reference<FileStream> fragmentShaderFile = FileStream::Create(fragment_path);

		std::unordered_map<GLenum, std::string> shaderSources;

		shaderSources[GL_VERTEX_SHADER] = vertexShaderFile->Read();
		shaderSources[GL_FRAGMENT_SHADER] = fragmentShaderFile->Read();

		m_ID = Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const char* path)
		: m_vertexPath(path), m_fragmentPath(path), m_name(File::GetName(path)) {

		Reference<FileStream> shaderFile = FileStream::Create(path);

		std::string parsedShader = shaderFile->Read();

		auto& shaders = PreProcess(parsedShader);

		m_ID = Compile(shaders);

	
	}

	void OpenGLShader::Reload() {
		ORIGIN_WARN("Shader: {0} is beign reloded!", GetName());
		Reference<FileStream> shaderFile = FileStream::Create(m_vertexPath.c_str());

		std::string parsedShader = shaderFile->Read();

		auto& shaders = PreProcess(parsedShader);
		uint32_t program = Compile(shaders);
		if (program == 0) {
			ORIGIN_ERROR("Shader: {0} could not be reloded!", GetName());
			return;
		}
		ORIGIN_INFO("Shader: {0} was succesfuly reloded!", GetName());

		m_ID = program;
	}


	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ID);
	}

	std::string OpenGLShader::GetName() const {
		return m_name;
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
		if (m_uniformMap.find(name) != m_uniformMap.end()) {
			return m_uniformMap[name];
		}
		uint32_t uniform_location = glGetUniformLocation(m_ID, name.c_str());
		m_uniformMap.insert({ name, uniform_location });
		return m_uniformMap[name];
	}

	uint32_t OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
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

				ORIGIN_ASSERT(false, "[{0} SHADER ERROR] {1}", ShaderTypeFromGLenum(value.first), infoLog.data());
				return 0;
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

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
			return 0;
		}
		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
			glDetachShader(program, id);
		}
		return program;
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