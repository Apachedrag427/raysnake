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

int ms_since(std::chrono::time_point<std::chrono::system_clock> last_update) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update).count();
}

void Snake::update() {
	int pre = dir;
	if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && dir != 3) {
		dir = 1;
	} else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && dir != 4) {
		dir = 2;
	} else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && dir != 1) {
		dir = 3;
	} else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && dir != 2) {
		dir = 4;
	}


	int elapsed_ms = ms_since(last_update);
	bool direction_changed = pre != dir;
	
	if (elapsed_ms <= 100 && !direction_changed) {
		return;
	}
	last_update = std::chrono::system_clock::now();


	for (int i = body.size(); i >= 1; i--) {
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}

	Segment* head = &body[0];

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
