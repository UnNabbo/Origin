#include "OGpch.h"

#include "Files.h"

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
		if (FILE* file = fopen(path, "r")) {
			fclose(file);
			return true;
		}
		return false;
	}

	
}
