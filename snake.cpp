#include <memory>
#include <raylib.h>
#include <chrono>

#include "snake.hpp"
#include "food.hpp"
#include "config.hpp"


Snake::Snake() {
	reset();
}

void Snake::draw() {
	for (Segment& segment : body) {
		DrawRectangle(segment.x * CELL_WIDTH, segment.y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, GREEN);
	}
}

void Snake::update() {
	if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && last_dir != 3) {
		dir = 1;
	} else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && last_dir != 4) {
		dir = 2;
	} else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && last_dir != 1) {
		dir = 3;
	} else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && last_dir != 2) {
		dir = 4;
	}
	
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update).count() <= 100) {
		return;
	}
	last_update = std::chrono::system_clock::now();
	last_dir = dir;

	Segment* head = &body[0];

	for (int i = body.size(); i >= 1; i--) {
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}

	switch(dir) {
		case 1:
			head->x += 1;
			break;
		case 2:
			head->y += 1;
			break;
		case 3:
			head->x -= 1;
			break;
		case 4:
			head->y -= 1;
			break;
	}

	if (head->x < 0 || head->x > GRID_SIZE-1 || head->y < 0 || head->y > GRID_SIZE-1) {
		dead = true;
	}

	for (int i = 1; i < body.size(); i++) {
		if (head->x == body[i].x && head->y == body[i].y) {
			dead = true;
			break;
		}
	}
}

void Snake::attempt_eat(std::unique_ptr<Food>& f) {
	Segment head = body[0];
	if (head.x == f->x && head.y == f->y) {
		f->spawn(body);
		Segment last = body.back();
		body.push_back({last.x, last.y});
	}
}

void Snake::reset() {
	dead = false;
	body.clear();
	body.push_back({
		.x = GRID_SIZE/2,
		.y = GRID_SIZE/2
	});
	last_update = std::chrono::system_clock::now();
}
