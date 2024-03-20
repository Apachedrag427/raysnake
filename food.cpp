#include "food.hpp"
#include "config.hpp"

#include <vector>
#include <raylib.h>

Food::Food() {
	spawn();
}

void Food::spawn() {
	x = GetRandomValue(0, GRID_SIZE-1);
	y = GetRandomValue(0, GRID_SIZE-1);
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
