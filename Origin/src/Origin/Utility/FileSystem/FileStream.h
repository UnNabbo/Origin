#pragma once

#include "Origin/Core.h"

#include "Files.h"

namespace Origin {
	class ORIGIN_API FileStream {
	public:
		FileStream(const char* path);
		~FileStream();

		std::string& Read();
		std::string GetPath();

	private:
		std::string m_path;
		std::string m_content;
		bool m_IsOpen = false;
	};
}