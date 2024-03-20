#include "snake.hpp"
#include "config.hpp"

#include <memory>
#include <raylib.h>
#include <rcamera.h>

const int textSpacing = 2;
void drawCenteredText(const char* text, int fontSize, Color color) {
	int width = MeasureText(text, fontSize);
	Vector2 dimensions = MeasureTextEx(GetFontDefault(), text, fontSize, textSpacing);
	Vector2 position = {(float)GetScreenWidth()/2 - dimensions.x/2, (float)GetScreenHeight()/2 - dimensions.y/2};
	DrawTextEx(GetFontDefault(), text, position, fontSize, 2, color);
}

const int FOOD_AMOUNT = 2;

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	
	InitWindow(GRID_WIDTH, GRID_HEIGHT, "Snake");

	Camera2D camera = { 0 };
	camera.target = (Vector2){ 0.0f, 0.0f };
	camera.offset = (Vector2){ 0.0f, 0.0f };//{ GRID_WIDTH/2.0f, GRID_HEIGHT/2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	std::unique_ptr<Snake> snek(new Snake());

	std::vector<std::unique_ptr<Food>> food;
	for (int i = 0; i < FOOD_AMOUNT; i++) {
		std::unique_ptr<Food> f(new Food());

		food.push_back(std::move(f));
	}

	while (!WindowShouldClose()) {
		if (!snek->dead) {
			snek->update();
			for (std::unique_ptr<Food>& f : food) {
				snek->attempt_eat(f);
			}

			BeginDrawing();

				ClearBackground(BLACK);

				BeginMode2D(camera);

					snek->draw();
					for (std::unique_ptr<Food>& f : food) {
						f->draw();
					}

				EndMode2D();

			EndDrawing();
		} else {
			if (IsKeyDown(KEY_SPACE)) {
				snek->reset();
			}

			BeginDrawing();

				ClearBackground(BLACK);
				drawCenteredText("Press SPACE to restart", 20, RED);

			EndDrawing();
		}
	}
}
