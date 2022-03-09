#pragma once

#include "Origin/Utility/FileSystem/FileStream.h"

namespace Origin {

	class WindowsFileStream : public FileStream{
	public:
		WindowsFileStream(const char* path);
		virtual ~WindowsFileStream() = default;

		virtual std::string& Read() override;
		virtual std::string& GetPath() override { return m_path; };

	private:
		std::string m_content;
		std::string m_path;

	};

}