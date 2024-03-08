#pragma once

#include <memory>
#include <vector>
#include <chrono>


struct Segment {
	int x;
	int y;
};

#include "food.hpp"

class Snake {
	int dir = 1;
	int last_dir = 1;

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
