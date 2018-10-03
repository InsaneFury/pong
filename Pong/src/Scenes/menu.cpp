#include "menu.h"
#include "Logic/game.h"
#include "Utility/buttons.h"

namespace pong {
	namespace menu {
		using namespace game;

		Rectangle rec;

		buttons::BTN play;
		buttons::BTN credits;
		buttons::BTN quit;

		//Line pos
		Vector2 startPos;
		Vector2 endPos;

		int lineThick; //Rec line
		float thick; //Simple line

		void init() {

			buttons::createButton(play, 80, 400, (float)(GetScreenWidth() / 2 - 200), (float)(GetScreenHeight() - 350), 5, 40, GRAY, SKYBLUE, WHITE);
			buttons::createButton(credits, 80, 400, (float)(GetScreenWidth() / 2 - 200), (float)(GetScreenHeight() - 260), 5, 40, GRAY, SKYBLUE, WHITE);
			buttons::createButton(quit, 80, 400, (float)(GetScreenWidth() / 2 - 200), (float)(GetScreenHeight() - 170), 5, 40, GRAY, SKYBLUE, WHITE);

			rec.height = 150;
			rec.width = 400;
			rec.x = GetScreenWidth() / 2 - rec.width / 2;
			rec.y = GetScreenHeight() / 2 - rec.height;

			startPos = { (float)(rec.x) , (float)(GetScreenHeight() - 80) };
			endPos = { (float)(rec.x + 400) , (float)(GetScreenHeight() - 80) };

			lineThick = 5; //Rec line
			thick = 4; //Simple line
		}

		void update(bool &endGame) {
			Vector2 mousePoint = GetMousePosition();

			buttons::isMouseOverButton(play);
			if (CheckCollisionPointRec(mousePoint, play.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
				}
			}
			buttons::isMouseOverButton(credits);
			if (CheckCollisionPointRec(mousePoint, credits.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Credits;
				}
			}

			buttons::isMouseOverButton(quit);
			if (CheckCollisionPointRec(mousePoint, quit.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					endGame = true;
				}
			}
		}

		void draw() {
			ClearBackground(WHITE);

			//Draw UI
			DrawRectangleLinesEx(rec, lineThick, SKYBLUE);
			DrawText("PONG", rec.x + rec.x / 6, rec.y + 30, 100, GRAY);
			DrawLineEx(startPos, endPos, thick, SKYBLUE);

			//Draw buttons
			buttons::draw(play, "PLAY");
			buttons::draw(credits, "CREDITS");
			buttons::draw(quit, "QUIT");
			DrawText("v1.0", screenWidth - 50, screenHeight - 20, 20, GRAY);
		}
	}
}

