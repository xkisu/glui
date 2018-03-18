
#ifndef GLUI_COLOR_H
#define GLUI_COLOR_H

#include <glm.hpp>

namespace glui {
	class Color {
	public:
		inline Color() {}
		inline Color(int newR, int newG, int newB) : r(newR), g(newG), b(newB), a(255) {}
		inline Color(int newR, int newG, int newB, int newA) : r(newR), g(newG), b(newB), a(newA) {}
		inline Color (int hex, bool alpha = false) {
			if(alpha) {
				r = ((hex >> 24) & 0xFF);  // Extract the RR byte
				g = ((hex >> 16) & 0xFF);  // Extract the RR byte
				b = ((hex >> 8) & 0xFF);   // Extract the GG byte
				a = ((hex) & 0xFF);        // Extract the BB byte
			} else {
				r = ((hex >> 16) & 0xFF);  // Extract the RR byte
				g = ((hex >> 8) & 0xFF);   // Extract the GG byte
				b = ((hex) & 0xFF);        // Extract the BB byte
				a = 255;
			}
		}

		inline int& SetR (int newR) {
			r = newR;
		}
		inline int& SetG (int newG) {
			g = newG;
		}
		inline int& SetB (int newB) {
			b = newB;
		}
		inline int& SetA (int newA) {
			a = newA;
		}

		inline int& GetR () {
			return r;
		}
		inline int& GetG () {
			return g;
		}
		inline int& GetB () {
			return b;
		}
		inline int& GetA () {
			return a;
		}

		inline glm::vec4 GetVector () {
			return glm::vec4(intToFloat(r), intToFloat(g), intToFloat(b), intToFloat(a));
		}
	private:
		int r, g, b, a = 0;

		inline float intToFloat (int i) {
			return ((i * 1.0f) / 255);
		}
	};
};

#endif //GLUI_COLOR_H
