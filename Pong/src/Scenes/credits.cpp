#include "credits.h"
#include "Logic/game.h"
#include "Utility/buttons.h"
#include "menu.h"

namespace pong {
	namespace credits {
		using namespace game;

		buttons::BTN back;

		void init() {
			buttons::createButton(back, 80, 200, (float)(GetScreenWidth() / 2)+ 400, 
								 (float)(GetScreenHeight() - 100), 3, 30, SKYBLUE, GRAY, WHITE);
		}

		void update() {
			Vector2 mousePoint = GetMousePosition();
			buttons::isMouseOverButton(back);

			if (CheckCollisionPointRec(mousePoint, back.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					menu::init();
					actualScene = Menu;
				}
			}
		}

		void draw() {
			ClearBackground(WHITE);

			//Draw UI
			DrawText("CREDITS", GetScreenWidth() / 2 - MeasureText("CREDITS",100)/2, GetScreenHeight() / 2 - 300, 100, GRAY);
			DrawText("GAME PONG", GetScreenWidth() / 2 - MeasureText("GAME PONG", 30) / 2, GetScreenHeight() / 2 - 200, 30, SKYBLUE);
			DrawText("v0.15", GetScreenWidth() / 2 - MeasureText("v1.0", 25) / 2, GetScreenHeight() / 2 - 165, 25, GRAY);
			DrawText("LEAD PROGRAMMER", GetScreenWidth() / 2 - MeasureText("LEAD PROGRAMMER", 30) / 2, GetScreenHeight() / 2 - 130, 30, SKYBLUE);
			DrawText("IVAN CASTELLANO", GetScreenWidth() / 2 - MeasureText("IVAN CASTELLANO", 25) / 2, GetScreenHeight() / 2 - 95, 25, GRAY);
			DrawText("MUSIC & SFX", GetScreenWidth() / 2 - MeasureText("MUSIC & SFX", 30) / 2, GetScreenHeight() / 2 - 50, 30, SKYBLUE);
			DrawText("IVAN CASTELLANO", GetScreenWidth() / 2 - MeasureText("IVAN CASTELLANO", 25) / 2, GetScreenHeight() / 2 - 10, 25, GRAY);
			DrawText("PROGRAMS USED", GetScreenWidth() / 2 - MeasureText("PROGRAMS USED", 30) / 2, GetScreenHeight() / 2 +40, 30, SKYBLUE);
			DrawText("FL STUDIO", GetScreenWidth() / 2 - MeasureText("FL STUDIO", 25) / 2, GetScreenHeight() / 2 + 75, 25, GRAY);
			DrawText("VISUAL STUDIO C++", GetScreenWidth() / 2 - MeasureText("VISUAL STUDIO C++", 25) / 2, GetScreenHeight() / 2 + 110, 25, GRAY);
			DrawText("RAYLIB LIBRARY", GetScreenWidth() / 2 - MeasureText("RAYLIB LIBRARY", 25) / 2, GetScreenHeight() / 2 + 150, 25, GRAY);

			//Draw buttons
			buttons::draw(back, "Back");
		}
	}
}
