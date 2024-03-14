#pragma once

#include <memory>
#include <raylib.h>
#include <vector>
#include <chrono>


struct Segment {
	int x;
	int y;
};

#include "food.hpp"

class Snake {
	int dir = 1;
	bool update_forced;

	int prev_tip_pos_x;
	int prev_tip_pos_y;

	std::vector<Segment> body;
	std::chrono::time_point<std::chrono::system_clock> last_update;

  public:
	bool dead = false;

	
	Snake();

	void reset();
	void draw();
	void update();
	void grow();
	void attempt_eat(std::unique_ptr<Food>& f);
};
