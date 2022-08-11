#include "Board.h"

Board::Board(int columns, int rows, int numMines)
{
	row = rows;
	col = columns;
	totalMines = numMines;
	mineCounter = numMines;
	spacesToBeRevealed = columns * rows - numMines;
	int minesCreated = 0;
	over = false;
	debuger = false;
	for (int i = 0; i < columns; i++)
	{
		vector<Tile> a;
		board.push_back(a);
		for (int j = 0; j < rows; j++)
		{
			Tile t;
			board.at(i).push_back(t);
		}
	}
	for (int i = 0; i < columns; i++)
		for (int j = 0; j < rows; j++)
		{
			if (i > 0 && j > 0)
				board[i][j].adjTiles.push_back(&board[i - 1][j - 1]);
			if (i > 0)
				board[i][j].adjTiles.push_back(&board[i - 1][j]);
			if (i > 0 && j < rows - 1)
				board[i][j].adjTiles.push_back(&board[i - 1][j + 1]);
			if (j > 0)
				board[i][j].adjTiles.push_back(&board[i][j - 1]);
			if (j < rows - 1)
				board[i][j].adjTiles.push_back(&board[i][j + 1]);
			if (i < columns - 1 && j > 0)
				board[i][j].adjTiles.push_back(&board[i + 1][j - 1]);
			if (i < columns - 1)
				board[i][j].adjTiles.push_back(&board[i + 1][j]);
			if (i < columns - 1 && j < rows - 1)
				board[i][j].adjTiles.push_back(&board[i + 1][j + 1]);
		}
	while (minesCreated < mineCounter)
	{
		int x = Random::Int(0, columns - 1);
		int y = Random::Int(0, rows - 1);
		if (board.at(x).at(y).mine != true)
		{
			board.at(x).at(y).mine = true;
			if (x > 0 && y > 0)
				board[x - 1][y - 1].adjMines++;
			if (x > 0)
				board[x - 1][y].adjMines++;
			if (x > 0 && y < rows - 1)
				board[x - 1][y + 1].adjMines++;
			if (y > 0)
				board[x][y - 1].adjMines++;
			if (y < rows - 1)
				board[x][y + 1].adjMines++;
			if (x < columns - 1 && y > 0)
				board[x + 1][y - 1].adjMines++;
			if (x < columns - 1)
				board[x + 1][y].adjMines++;
			if (x < columns - 1 && y < rows - 1)
				board[x + 1][y + 1].adjMines++;
			minesCreated++;
		}
	}
}
void Board::Restart()
{
	mineCounter = totalMines;
	spacesToBeRevealed = col * row - totalMines;
	int minesCreated = 0;
	over = false;
	board.clear();
	for (int i = 0; i < col; i++)
	{
		vector<Tile> a;
		board.push_back(a);
		for (int j = 0; j < row; j++)
		{
			Tile t;
			board.at(i).push_back(t);
		}
	}
	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++)
		{
			if (i > 0 && j > 0)
				board[i][j].adjTiles.push_back(&board[i - 1][j - 1]);
			if (i > 0)
				board[i][j].adjTiles.push_back(&board[i - 1][j]);
			if (i > 0 && j < row - 1)
				board[i][j].adjTiles.push_back(&board[i - 1][j + 1]);
			if (j > 0)
				board[i][j].adjTiles.push_back(&board[i][j - 1]);
			if (j < row - 1)
				board[i][j].adjTiles.push_back(&board[i][j + 1]);
			if (i < col - 1 && j > 0)
				board[i][j].adjTiles.push_back(&board[i + 1][j - 1]);
			if (i < col - 1)
				board[i][j].adjTiles.push_back(&board[i + 1][j]);
			if (i < col - 1 && j < row - 1)
				board[i][j].adjTiles.push_back(&board[i + 1][j + 1]);
		}
	while (minesCreated < mineCounter)
	{
		int x = Random::Int(0, col - 1);
		int y = Random::Int(0, row - 1);
		if (board.at(x).at(y).mine != true)
		{
			board.at(x).at(y).mine = true;
			if (x > 0 && y > 0)
				board[x - 1][y - 1].adjMines++;
			if (x > 0)
				board[x - 1][y].adjMines++;
			if (x > 0 && y < row - 1)
				board[x - 1][y + 1].adjMines++;
			if (y > 0)
				board[x][y - 1].adjMines++;
			if (y < row - 1)
				board[x][y + 1].adjMines++;
			if (x < col - 1 && y > 0)
				board[x + 1][y - 1].adjMines++;
			if (x < col - 1)
				board[x + 1][y].adjMines++;
			if (x < col - 1 && y < row - 1)
				board[x + 1][y + 1].adjMines++;
			minesCreated++;
		}
	}
}
void Board::TestBoard(string fileName)
{
	mineCounter = 0;
	over = false;
	board.clear();
	//load board
	for (int i = 0; i < col; i++)
	{
		vector<Tile> a;
		board.push_back(a);
		for (int j = 0; j < row; j++)
		{
			Tile t;
			board.at(i).push_back(t);
		}
	}
	ifstream inFile(fileName);
	string lineFromFile;
	for (int i = 0; i < row; i++)
	{
		getline(inFile, lineFromFile);
		for (int j = 0; j < col; j++)
		{
			if (lineFromFile[j] == '1')
			{
				board[j][i].mine = true;
				++mineCounter;
				if (j > 0 && i > 0)
					board[j - 1][i - 1].adjMines++;
				if (j > 0)
					board[j - 1][i].adjMines++;
				if (j > 0 && i < row - 1)
					board[j - 1][i + 1].adjMines++;
				if (i > 0)
					board[j][i - 1].adjMines++;
				if (i < row - 1)
					board[j][i + 1].adjMines++;
				if (j < col - 1 && i > 0)
					board[j + 1][i - 1].adjMines++;
				if (j < col - 1)
					board[j + 1][i].adjMines++;
				if (j < col - 1 && i < row - 1)
					board[j + 1][i + 1].adjMines++;
			}
		}
	}
	for (int i = 0; i < col; i++) //populating adjTiles
		for (int j = 0; j < row; j++)
		{
			if (i > 0 && j > 0)
				board[i][j].adjTiles.push_back(&board[i - 1][j - 1]);
			if (i > 0)
				board[i][j].adjTiles.push_back(&board[i - 1][j]);
			if (i > 0 && j < row - 1)
				board[i][j].adjTiles.push_back(&board[i - 1][j + 1]);
			if (j > 0)
				board[i][j].adjTiles.push_back(&board[i][j - 1]);
			if (j < row - 1)
				board[i][j].adjTiles.push_back(&board[i][j + 1]);
			if (i < col - 1 && j > 0)
				board[i][j].adjTiles.push_back(&board[i + 1][j - 1]);
			if (i < col - 1)
				board[i][j].adjTiles.push_back(&board[i + 1][j]);
			if (i < col - 1 && j < row - 1)
				board[i][j].adjTiles.push_back(&board[i + 1][j + 1]);
		}
	spacesToBeRevealed = col * row - mineCounter;
}
void Board::Show(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < board.size(); ++i)
		for (unsigned int j = 0; j < board[0].size(); ++j)
		{
			if (board[i][j].shown == false) // unknown tile
			{
				sf::Sprite tile(TextureManager::GetTexture("tile_hidden"));
				tile.setPosition(i * 32.0f, j * 32.0f);
				window.draw(tile);
				if (board[i][j].flag == true)
				{
					sf::Sprite icon(TextureManager::GetTexture("flag"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
			}
			else // known tile
			{
				sf::Sprite tile(TextureManager::GetTexture("tile_revealed"));
				tile.setPosition(i * 32.0f, j * 32.0f);
				window.draw(tile);
				if (board[i][j].mine)
				{
					sf::Sprite icon(TextureManager::GetTexture("mine"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 1)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_1"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 2)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_2"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 3)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_3"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 4)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_4"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 5)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_5"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 6)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_6"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 7)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_7"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
				else if (board[i][j].adjMines == 8)
				{
					sf::Sprite icon(TextureManager::GetTexture("number_8"));
					icon.setPosition(i * 32.0f, j * 32.0f);
					window.draw(icon);
				}
			}
		}
	if (over == false)
	{
		sf::Sprite face(TextureManager::GetTexture("face_happy"));
		face.setPosition((board.size() - 2) * 16.0f, board[0].size() * 32.0f);
		window.draw(face);
	}
	else if (spacesToBeRevealed == 0)
	{
		sf::Sprite face(TextureManager::GetTexture("face_win"));
		face.setPosition((board.size() - 2) * 16.0f, board[0].size() * 32.0f);
		window.draw(face);
	}
	else
	{
		sf::Sprite face(TextureManager::GetTexture("face_lose"));
		face.setPosition((board.size() - 2) * 16.0f, board[0].size() * 32.0f);
		window.draw(face);
	}
	sf::Sprite debug(TextureManager::GetTexture("debug"));
	debug.setPosition((board.size() - 2) * 16.0f + 64 * 2.0f, board[0].size() * 32.0f);
	window.draw(debug);
	sf::Sprite test1(TextureManager::GetTexture("test_1"));
	test1.setPosition((board.size() - 2) * 16.0f + 64 * 3.0f, board[0].size() * 32.0f);
	window.draw(test1);
	sf::Sprite test2(TextureManager::GetTexture("test_2"));
	test2.setPosition((board.size() - 2) * 16.0f + 64 * 4.0f, board[0].size() * 32.0f);
	window.draw(test2);
	sf::Sprite test3(TextureManager::GetTexture("test_3"));
	test3.setPosition((board.size() - 2) * 16.0f + 64 * 5.0f, board[0].size() * 32.0f);
	window.draw(test3);
	
	int mineCount = mineCounter;

	if (mineCounter < 0)
	{
		sf::Sprite neg(TextureManager::GetTexture("digits"));
		neg.setTextureRect(sf::IntRect(210, 0, 21 , 32));
		neg.setPosition(0, board[0].size() * 32.0f);
		window.draw(neg);
		mineCount *= -1;
	}
	
	sf::Sprite hundreds(TextureManager::GetTexture("digits"));
	hundreds.setTextureRect(sf::IntRect(mineCount/100 * 21, 0, 21, 32));
	hundreds.setPosition(21, board[0].size() * 32.0f);
	window.draw(hundreds);

	sf::Sprite tens(TextureManager::GetTexture("digits"));
	tens.setTextureRect(sf::IntRect(mineCount % 100 / 10 * 21, 0, 21, 32));
	tens.setPosition(21*2, board[0].size() * 32.0f);
	window.draw(tens);

	sf::Sprite ones(TextureManager::GetTexture("digits"));
	ones.setTextureRect(sf::IntRect(mineCount % 10 * 21, 0, 21, 32));
	ones.setPosition(21*3, board[0].size() * 32.0f);
	window.draw(ones);

	if (debuger == true)
		Debug(window);
}
void Board::Debug(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < board.size(); ++i)
		for (unsigned int j = 0; j < board[0].size(); ++j)
		{
			if (board[i][j].mine == true)
			{
				sf::Sprite icon(TextureManager::GetTexture("mine"));
				icon.setPosition(i * 32.0f, j * 32.0f);
				window.draw(icon);
			}
		}
}
void Board::Left(int x, int y)
{
	if (x > (col - 2) * 16 && x < (col - 2) * 16 + 64
		&& y > row * 32 && y < row * 32 + 64) // clicks on face
		Restart();
	else if (x > (col - 2) * 16 + 64 * 2 && x < (col - 2) * 16 + 64 * 3
		&& y > row * 32 && y < row * 32 + 64 && over == false)
	{
		if (debuger)
			debuger = false;
		else
			debuger = true;
	}
	else if (x > (col - 2) * 16 + 64 * 3 && x < (col - 2) * 16 + 64 * 4
		&& y > row * 32 && y < row * 32 + 64)
		TestBoard("boards/testboard1.brd");
	else if (x > (col - 2) * 16 + 64 * 4 && x < (col - 2) * 16 + 64 * 5
		&& y > row * 32 && y < row * 32 + 64)
		TestBoard("boards/testboard2.brd");
	else if (x > (col - 2) * 16 + 64 * 5 && x < (col - 2) * 16 + 64 * 6
		&& y > row * 32 && y < row * 32 + 64)
		TestBoard("boards/testboard3.brd");
	else if (over == false && x / 32 < col && y / 32 < row)// clicks on game board and game is not over
	{
		int c = x / 32;
		int r = y / 32;
		if (board[c][r].mine)
		{
			EndDefeat();
			over = true;
		}
		else
		{
			std::queue<Tile*> tiles;
			tiles.push(&board[c][r]);
			while (!tiles.empty())
			{
				Tile* t = tiles.front();
				tiles.pop();
				if (t->flag == false && t->shown == false)
				{
					t->shown = true;
					spacesToBeRevealed--;
					if (t->adjMines == 0)
						for (unsigned int i = 0; i < t->adjTiles.size(); ++i)
							if (t->adjTiles[i]->mine == false && t->adjTiles[i]->shown == false)
								tiles.push(t->adjTiles[i]);
				}
			}
			if (spacesToBeRevealed == 0)
				EndVictory();
		}
	}
}
void Board::Right(int x, int y)
{
	int c = x / 32;
	int r = y / 32;
	if (c < col && r < row && board[c][r].shown == false && over == false)
	{
		if (board[c][r].flag == false)
		{
			board[c][r].flag = true;
			mineCounter--;
		}
		else
		{
			board[c][r].flag = false;
			mineCounter++;
		}
	}
}
void Board::EndVictory()
{
	int count = 0;
	for (unsigned int i = 0; i < board.size(); i++)
		for (unsigned int j = 0; j < board[0].size(); ++j)
		{
			if (board[i][j].mine)
				board[i][j].flag = true;
		}
	mineCounter = 0;
	over = true;
}
void Board::EndDefeat()
{
	for (unsigned int i = 0; i < board.size(); i++)
		for (unsigned int j = 0; j < board[0].size(); ++j)
		{
			if (board[i][j].mine)
				board[i][j].shown = true;
		}
	over = true;
}
bool Board::IsOver()
{
	return over;
}