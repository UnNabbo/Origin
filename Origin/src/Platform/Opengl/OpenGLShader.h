#pragma once

#include "Origin/Core/Core.h"

#include "Origin/Renderer/Primitives/Shader.h"

#include <glad/glad.h>


namespace Origin {

	class ORIGIN_API OpenGLShader : public Shader {
	public:
		OpenGLShader(const char* vertex_path, const char* fragment_path);
		OpenGLShader(const char* path);

		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;


		virtual void UploadUniform(std::string name, int x) override;
		virtual void UploadUniform(std::string name, bool x) override;
		virtual void UploadUniform(std::string name, double x) override;
		virtual void UploadUniform(std::string name, float x) override;
		virtual void UploadUniform(std::string name, glm::vec3 vec) override;
		virtual void UploadUniform(std::string name, glm::vec4 vec) override;
		virtual void UploadUniform(std::string name, glm::mat4 mat) override;
	private:
		uint32_t CreateShader(uint32_t id, const std::string& shader) const;
		uint32_t GetUniformLocation(std::string name);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
	private:
		uint32_t m_ID;
		std::string m_vertex_path;
		std::string m_fragment_path;
		std::unordered_map<std::string, uint32_t> m_uniform_map;

	};

}