
#ifndef GLUI_CONFIG_H
#define GLUI_CONFIG_H

#include <string>
#include <map>

// Initial window size
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// Window and application title
#define WINDOW_TITLE "GLUI Test"

// directories to be automatically mounted
static const std::map<std::string, std::string> directory_mounts = {
		{"shaders/", "/shaders"}
};

// required shaders to be automatically loaded
static const std::string shaders [] = {
	"gui"
};

#endif //GLUI_CONFIG_H
