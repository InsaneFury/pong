#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace pong {
	namespace gameplay {
		struct Player {
			Vector2 position;
			Vector2 size;
			Color color;
			int score;
			int speed;
		};

		extern Player player1;
		extern Player player2;

		void init();
		void update();
		void draw();
		void deInit();
	}
}
#endif // !GAMEPLAY_H


