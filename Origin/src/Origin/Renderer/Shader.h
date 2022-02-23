#pragma once
#include "Origin/Core.h"

namespace Origin {

	class ORIGIN_API Shader {
	public:
		static Shader* Create(const char* vertex_path, const char* fragment_path);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual int SetUniform(int x) const = 0;
		virtual bool SetUniform(bool x) const = 0;
		virtual double SetUniform(double x) const = 0;
		virtual float SetUniform(float x) const = 0;

	};
}