#pragma once
#include "Origin/Core.h"

#include "glm/glm.hpp"

namespace Origin {

	class ORIGIN_API Shader {
	public:
		static Shader* Create(const char* vertex_path, const char* fragment_path);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniform(std::string name, int x) = 0;
		virtual void UploadUniform(std::string name, bool x) = 0;
		virtual void UploadUniform(std::string name, double x) = 0;
		virtual void UploadUniform(std::string name, float x) = 0;
		virtual void UploadUniform(std::string name, glm::vec3 vec) = 0;
		virtual void UploadUniform(std::string name, glm::vec4 vec) = 0;
		virtual void UploadUniform(std::string name, glm::mat4 mat) = 0;

	};
}