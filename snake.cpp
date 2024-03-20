#include <memory>
#include <raylib.h>
#include <chrono>

#include "snake.hpp"
#include "food.hpp"
#include "config.hpp"


Snake::Snake() {
	reset();
}


int ms_since(std::chrono::time_point<std::chrono::system_clock> last_update) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update).count();
}


float lerp(float a, float b, float alpha) {
	return a + alpha * (b - a);
}

void Snake::draw() {
	float progress = ms_since(last_update) / 100.0f;
	for (int i = 0; i < body.size(); i++) {
		Segment* segment = &body[i];
		if (i < body.size() - 1) {
			DrawRectangleRec({
				lerp((float)body[i + 1].x * CELL_WIDTH, (float)segment->x * CELL_WIDTH, progress),
				lerp((float)body[i + 1].y * CELL_WIDTH, (float)segment->y * CELL_WIDTH, progress),
				CELL_WIDTH, CELL_HEIGHT
			}, GREEN);
		} else {
			DrawRectangleRec({
				lerp((float)prev_tip_pos_x * CELL_WIDTH, (float)segment->x * CELL_WIDTH, progress),
				lerp((float)prev_tip_pos_y * CELL_WIDTH, (float)segment->y * CELL_WIDTH, progress),
				CELL_WIDTH, CELL_HEIGHT
			}, GREEN);
		}
	}
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

	if (direction_changed && elapsed_ms < 50) {
		for (int i = 0; i < body.size(); i++) {
			if (i == body.size() - 1) {
				body[i].x = prev_tip_pos_x;
				body[i].y = prev_tip_pos_y;
			} else {
				body[i].x = body[i+1].x;
				body[i].y = body[i+1].y;
			}
		}
	}
	
	if (elapsed_ms <= 100 && !direction_changed) {
		return;
	}
	last_update = std::chrono::system_clock::now();


	prev_tip_pos_x = body[body.size()-1].x;
	prev_tip_pos_y = body[body.size()-1].y;

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
