#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include <fstream>
#include "Random.h"
#include "TextureManager.h"
#include "Tile.h"
using std::string;
using std::vector;
using std::ifstream;

class Board
{
	vector<vector<Tile>> board;
	int row;
	int col;
	int totalMines;
	int mineCounter;
	bool over;
	int spacesToBeRevealed;
	bool debuger;
public:
	Board(int c, int r, int numMines);
	void Show(sf::RenderWindow& window);
	void TestBoard(string fileName);
	void Debug(sf::RenderWindow& window);
	void Left(int x, int y);
	void Right(int x, int y);
	void EndVictory();
	void EndDefeat();
	void Restart();
	bool IsOver();
};

