#include "OGpch.h"

#include "FileSystem.h"

namespace Origin {
	File::File(const char* path) {

	}

	File::~File() {

	}

	File* File::Open(const char * path) {
		return new File(path);
	}

}