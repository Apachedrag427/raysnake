#pragma once
#include <random>

struct Segment;

class Food {
	std::uniform_int_distribution<> dist;
	std::random_device rd;
	std::mt19937 gen;
	

  public:
	int x;
	int y;

	Food();

	void spawn();
	void spawn(std::vector<Segment>& blacklist);

	void draw();
};


#include "snake.hpp"
