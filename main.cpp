#include "snake.hpp"
#include "config.hpp"

#include <memory>
#include <raylib.h>

const int textSpacing = 2;
void drawCenteredText(const char* text, int fontSize, Color color) {
	int width = MeasureText(text, fontSize);
	Vector2 dimensions = MeasureTextEx(GetFontDefault(), text, fontSize, textSpacing);
	Vector2 position = {(float)GetScreenWidth()/2 - dimensions.x/2, (float)GetScreenHeight()/2 - dimensions.y/2};
	DrawTextEx(GetFontDefault(), text, position, fontSize, 2, color);
}

const int FOOD_AMOUNT = 1;

int main() {
	InitWindow(GRID_WIDTH, GRID_HEIGHT, "Snake");

	SetTargetFPS(180);

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
				snek->draw();
				for (std::unique_ptr<Food>& f : food) {
					f->draw();
				}

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
