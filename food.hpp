#pragma once

#include <vector>

struct Segment;

class Food {
  public:
	int x;
	int y;

	Food();

	void spawn();
	void spawn(std::vector<Segment>& blacklist);

	void draw();
};


#include "snake.hpp"
