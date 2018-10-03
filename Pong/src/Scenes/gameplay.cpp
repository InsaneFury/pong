#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/buttons.h"

namespace pong {
	namespace gameplay {
		using namespace game;

		Player player1;
		Player player2;

		//Control sensibility
		static float speed = 10.0f;

		// Rectangle Size - Players Size
		static Vector2 rectangleSize = { 20,100 };

		static Sound pong;

		struct Ball {
			Vector2 position;
			Vector2 speed;
			int moveSpeed;
			float radius = 10.0f;
			bool active = false;
		};

		static Ball ball;

		static Color midLine = GRAY;
		static Color tutorial = GRAY;

		buttons::BTN help;

		static int lineThick = 3; //Rec line
		static float timer;

		void init() {
			#pragma region players
			//Player 1
			player1.position.x = 50;
			player1.position.y = (float)screenHeight / 2;
			player1.size.x = rectangleSize.x;
			player1.size.y = rectangleSize.y;
			player1.score = 0;
			player1.speed = 800;
			player1.color = SKYBLUE;
			player1.color.a = 120;

			//Player 2
			player2.position.x = (float)screenWidth - 50;
			player2.position.y = (float)screenHeight / 2;
			player2.size.x = rectangleSize.x;
			player2.size.y = rectangleSize.y;
			player2.score = 0;
			player2.speed = 800;
			player2.color = RED;
			player2.color.a = 120;
			#pragma endregion

			#pragma region ball
			//Ball
			ball.position = { (float)screenWidth / 2,(float)screenHeight / 2 };
			ball.moveSpeed = 400;
			#pragma endregion

			buttons::createButton(help, 40, 40, (float)(GetScreenWidth() / 2 - 40 / 2), (float)(GetScreenHeight() - 50), 3, 30, SKYBLUE, GRAY, WHITE);

			midLine.a = 120;

			//FrameCounter
			timer = GetFrameTime();

			pong = LoadSound("res/Sound/pop.ogg");
		}

		void update() {
			timer += GetFrameTime();
			#pragma region players
			//Player1 Movement
			if (IsKeyDown(KEY_W)) { 
				player1.position.y -= player1.speed * GetFrameTime();
			}
			if ((player1.position.y - player1.size.y / 10) <= 0) {
				player1.position.y = player1.size.y / 10; 
			}

			if (IsKeyDown(KEY_S)) { 
				player1.position.y += player1.speed * GetFrameTime(); 
			}
			if ((player1.position.y + player1.size.y + 5) >= screenHeight){
				player1.position.y = screenHeight - player1.size.y - 5;
			}

			//Player2 Movement
			if (IsKeyDown(KEY_UP)) {
				player2.position.y -= player2.speed * GetFrameTime();
			}
			if ((player2.position.y - player2.size.y / 10) <= 0) {
				player2.position.y = player2.size.y / 10;
			}

			if (IsKeyDown(KEY_DOWN)) {
				player2.position.y += player2.speed * GetFrameTime();
			}
			if ((player2.position.y + player2.size.y + 5) >= screenHeight) {
				player2.position.y = screenHeight - player2.size.y - 5;
			}
			#pragma endregion
			
			#pragma region ball
			// Ball launching logic
			if (!ball.active)
			{
				if (IsKeyPressed(KEY_SPACE))
				{
					ball.active = true;
					ball.speed = { (float)ball.moveSpeed , (float)ball.moveSpeed };
				}
			}

			// Ball movement logic
			if (ball.active)
			{
				ball.position.x += ball.speed.x * GetFrameTime();
				ball.position.y += ball.speed.y * GetFrameTime();
			}
			else
			{
				ball.position = { (float)screenWidth / 2,(float)screenHeight / 2 };
			}

			// Collision ball vs walls & Score
			if ((ball.position.y - ball.radius) <= 0) ball.speed.y *= -1;
			if ((ball.position.y + ball.radius) >= screenHeight) ball.speed.y *= -1;

			if ((ball.position.x + ball.radius) >= screenWidth)
			{
				player1.score++;
				ball.speed = { 0, 0 };
				ball.active = false;
			}
			else if ((ball.position.x + ball.radius) <= 0) {
				player2.score++;
				ball.speed = { 0, 0 };
				ball.active = false;
			}

			// Collision logic: ball vs player
			if (CheckCollisionCircleRec(ball.position, ball.radius,
				Rectangle{
					player1.position.x - player1.size.x / 2, player1.position.y, player1.size.x, player1.size.y
				}))
			{
				player1.color.a = 255;
				#ifdef AUDIO
				#define AUDIO
					PlaySound(pong);
				#endif // !AUDIO
				
				timer = 0;

				if (ball.speed.x != 0)
				{
					ball.speed.x *= -1;
					ball.speed.y = (ball.position.y - player1.position.y) / (player1.size.y / 2) * ball.moveSpeed;
				}
			}
			else if (timer > 0.1) {
				player1.color.a = 120;
			}

			if (CheckCollisionCircleRec(ball.position, ball.radius,
				Rectangle{
					player2.position.x + player2.size.x / 2, player2.position.y, player2.size.x, player2.size.y
				}))
			{
				player2.color.a = 255;
				#ifdef AUDIO
				#define AUDIO
					PlaySound(pong);
				#endif // !AUDIO
				timer = 0;

				if (ball.speed.x != 0)
				{
					ball.speed.x *= -1;
					ball.speed.y = (ball.position.y - player2.position.y) / (player2.size.y / 2) * ball.moveSpeed;
				}
			}
			else if (timer > 0.1) {
				player2.color.a = 120;
			}

			if (player1.score >= 7 || player2.score >= 7) {
				actualScene = Gameover;
			}
			#pragma endregion

			//Tutorial textFX
			Vector2 mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, help.size))
			{
				tutorial.a = 255;
			}
			else {
				tutorial.a = 0;
			}

			buttons::isMouseOverButton(help);

		}

		void draw() {
			// Draw Score & Texts
			DrawText(FormatText("%4i", player2.score), screenWidth / 2 - 40, 20, 50, RED);
			DrawText(FormatText("%4i", player1.score), screenWidth / 2 - 105, 20, 50, SKYBLUE);
			DrawText("Move with W/S & UP/DOWN keys", screenWidth / 2 - 150, screenHeight - 130, 20, tutorial);
			DrawText("Press SPACE to start the round", screenWidth / 2 - 150, screenHeight - 100, 20, tutorial);
			DrawRectangle(screenWidth / 2, 0, 2, screenHeight, midLine);

			// Draw player bar
			DrawRectangle((float)player1.position.x, (float)player1.position.y, (float)player1.size.x, (float)player1.size.y, player1.color);
			DrawRectangle((float)player2.position.x, (float)player2.position.y, (float)player2.size.x, (float)player2.size.y, player2.color);
			DrawCircleV(ball.position, ball.radius, SKYBLUE);

			//Draw buttons
			buttons::draw(help,"?");
		}

		void deInit() {
		#ifdef AUDIO
		#define AUDIO
			UnloadSound(pong);
		#endif // !AUDIO
		}
	}
}

