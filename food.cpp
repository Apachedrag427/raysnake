#include "food.hpp"
#include "config.hpp"

#include <random>
#include <raylib.h>

Food::Food() : dist(0, GRID_SIZE - 1), gen(rd()) {
	spawn();
}

void Food::spawn() {
	x = dist(gen);
	y = dist(gen);
}

void Food::spawn(std::vector<Segment>& blacklist) {
loop:
	spawn();
	for (Segment& seg : blacklist) {
		if (x == seg.x && y == seg.y)
			goto loop;
	}
}

void Food::draw() {
	DrawRectangle(x * CELL_WIDTH, y * CELL_WIDTH, CELL_WIDTH, CELL_HEIGHT, RED);
}
