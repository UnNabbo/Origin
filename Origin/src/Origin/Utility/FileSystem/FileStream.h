#pragma once

#include "Origin/Core.h"

#include "Files.h"

namespace Origin {
	struct ORIGIN_API FileStream {
	public:
		FileStream(const char* path);
		~FileStream();

		std::string& Read();


	private:
		const char* m_path;
		std::string m_content;

	};
}