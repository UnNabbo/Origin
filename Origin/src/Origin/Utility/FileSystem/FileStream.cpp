#include "OGpch.h"

#include "FileStream.h"

#include <sstream>
#include <fstream>

namespace Origin {
	FileStream* File::Open(const char* path) {
		auto data = ResourceManager::Retrive(path);
		if (data) {
			return (FileStream*)data;
		}
		FileStream* file = new FileStream(path);
		ResourceManager::Load(path, (void*)file);
		return file;
	}

	FileStream::FileStream(const char* path) {
		m_path = path;
	}

	FileStream::~FileStream() {
		
	}

	std::string& FileStream::Read() {
		if (!m_content.empty()) {
			return m_content;
		}

		std::stringstream ss;
		std::ifstream file(m_path);
		if (file.is_open()) {
			std::string temp;
			while (std::getline(file, temp)) {
				ss << temp << "\n";
			}
		}

		m_content = ss.str();
		return m_content;
	}
}