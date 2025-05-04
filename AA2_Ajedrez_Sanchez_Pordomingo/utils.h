#pragma once
#include "Library.h"
struct Position
{
	int x;
	int y;
};

struct Pieces {
	bool active;
	bool moved;
	char piece;
	Position pos;
};