#ifndef BUTTONS_H
#define BUTTONS_H
#include "raylib.h"

namespace pong {
	namespace buttons {

		struct BTN {
			Rectangle size;
			int strokeThick;
			int fontsize;
			Color textColor;
			Color color;
			Color strokeColor;
		};
		void createButton(BTN &button, int height, int width, int posX, int posY, int strokeThick, int fontSize, Color btnColor, Color strokeColor, Color textColor);
		void isMouseOverButton(BTN &button);
		void draw(BTN button, const char *text);

	}
}
#endif // !BUTTONS_H

