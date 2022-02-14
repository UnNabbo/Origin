#pragma once

#include "Origin/Core.h"

#include "stdint.h"

namespace Origin {

	class ORIGIN_API VertexBuffer {
	public:
		static VertexBuffer* Create();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(float* data, uint32_t size) = 0;
	};


	class ORIGIN_API IndexBuffer {
	public:

		static IndexBuffer* Create();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(uint32_t* data, uint32_t size) = 0;
	};
}