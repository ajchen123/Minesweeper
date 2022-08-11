#pragma once
#include <vector>
using std::vector;

class Tile
{
public:
	bool mine;
	bool flag;
	bool shown;
	int adjMines;
	vector<Tile*> adjTiles;

	Tile();
};

