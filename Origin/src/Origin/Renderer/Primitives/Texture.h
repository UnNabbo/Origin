#pragma once

#include "Origin/Core/Core.h"

namespace Origin {
	class ORIGIN_API Texture {
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot) const = 0;
	};

	class ORIGIN_API Texture2D : public Texture {
	public:
		virtual ~Texture2D() = default;

		static AssetRef<Texture2D> Create(const std::string& path);
	};
}