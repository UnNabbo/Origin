#include "OGpch.h"

#include "FileStream.h"

#include "Platform/Windows/WindowsFileStream.h"

#include "Platform/Platform.h"

namespace Origin {
	Reference<FileStream> FileStream::Create(const char* path) {
		switch (Platform::GetAPI()) {
			case Platform::PlatformAPI::None:    ORIGIN_ASSERT(false, "PlatformAPI cannot be PlatformAPI::None!"); return nullptr;
			case Platform::PlatformAPI::Windows:  return std::make_shared<WindowsFileStream>(path);
		}
	}
}