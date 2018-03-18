
#ifndef GLUI_FILE_H
#define GLUI_FILE_H

#include <physfs.h>
#include <cstdio>
#include <stdexcept>

#include "config.h"

namespace glui {
	class FileManager {
	public:
		static inline void Initialize() {
			if(PHYSFS_init(NULL) != 1) {
				throw std::runtime_error("Error initializing PHYSFS!");
			}

			for (auto const& item : directory_mounts ) {
				PHYSFS_mount(item.first.c_str(), item.second.c_str(), false);
			}
		}

		static inline void Terminate () {
			PHYSFS_deinit();
		}

		static std::string ReadFileText (std::string file);
	private:
	};
};

#endif //GLUI_FILE_H
