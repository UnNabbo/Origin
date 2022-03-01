#include "OGpch.h"

#include "Files.h"

#include <filesystem>

namespace Origin {

	void File::Delete(const char* path) {
		int status = remove(path);
		ORIGIN_ASSERT(status, "Could not delete file in path, {0}", path);
	}

	void File::Move(const char* old_path, const char* new_path) {
		int status = rename(old_path, new_path);
		ORIGIN_ASSERT(status, "Could not move or rename file in path, {0}", old_path);
	}

	bool File::Exist(const char* path) {
		return Exist(path);
	}

	const char* File::GetName(const char* path) {
		std::filesystem::path fs_path = path;
		return fs_path.stem().string().c_str();
	}

	
}
