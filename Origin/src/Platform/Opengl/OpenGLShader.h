#pragma once

#include "Origin/Core.h"

#include "Origin/Renderer/Shader.h"



namespace Origin {

	class ORIGIN_API OpenGLShader : public Shader {
	public:
		OpenGLShader(const char* vertex_path, const char* fragment_path);

		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		uint32_t CreateShader(uint32_t id, const std::string& shader) const;

		virtual int SetUniform(int x) const override;
		virtual bool SetUniform(bool x) const override;
		virtual double SetUniform(double x) const override;
		virtual float SetUniform(float x) const override;
	private:
		uint32_t m_ID;
		std::string m_vertex_path;
		std::string m_fragment_path;

	};

}