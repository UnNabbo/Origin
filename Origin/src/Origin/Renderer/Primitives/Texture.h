#pragma once

#include "Origin/Core/Core.h"

namespace Origin {
	class ORIGIN_API Texture {
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, size_t size) = 0;

		virtual void Bind(uint32_t slot) const = 0;
	};

	class ORIGIN_API Texture2D : public Texture {
	public:
		virtual ~Texture2D() = default;


		static Reference<Texture2D> Create(uint32_t width, uint32_t height);
		static Reference<Texture2D> Create(const std::string& path);
	};
}