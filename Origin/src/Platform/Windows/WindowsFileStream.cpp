#include "OGpch.h"

#include "WindowsFileStream.h"

#include <fstream>
#include <shobjidl_core.h>

namespace Origin {
	WindowsFileStream::WindowsFileStream(const char* path) 
		: m_path(path) {}

	std::string& WindowsFileStream::Read() {
		if (!m_content.empty()) {
			return m_content;
		}

		ORIGIN_ASSERT(File::Exist(m_path.c_str()), "{0} does not exist", m_path);
		std::stringstream ss;
		std::ifstream file(m_path);
		if (file.is_open()) {
			std::string temp;
			while (std::getline(file, temp)) {
				ss << temp << "\n";
			}
		}


		file.clear();
		m_content = ss.str();
		return m_content;
	}
}
