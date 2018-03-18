
#include "file_manager.h"

namespace glui {
	std::string FileManager::ReadFileText (std::string name) {
		const char * path = name.c_str();

		if(!PHYSFS_exists(path)) {
			// throw std::runtime_error("vert doesn't exist!");
			return std::string("");
		}

		char *buf;
		PHYSFS_file *vertFile = PHYSFS_openRead(path);

		int len = PHYSFS_fileLength(vertFile);
		buf = new char[len+1];
		int length_read = PHYSFS_readBytes (vertFile, buf, len);
		buf[len] = '\0';

		PHYSFS_close(vertFile);

		return std::string(buf);
	}
};