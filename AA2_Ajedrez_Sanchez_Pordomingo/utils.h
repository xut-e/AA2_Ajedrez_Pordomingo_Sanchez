#pragma once
#include "Library.h"
struct Position
{
	int x;
	int y;
};

struct Pieces {
	bool active;
	char piece;
	Position pos;
};