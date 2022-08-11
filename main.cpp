#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "TextureManager.h"
#include "Random.h"
#include "Tile.h"
#include "Board.h"
using std::ifstream;

int main()
{
    ifstream inFile("boards/config.cfg");
    string lineFromFile;
    getline(inFile, lineFromFile);
    int numColumns = stoi(lineFromFile);
    getline(inFile, lineFromFile);
    int numRows = stoi(lineFromFile);
    getline(inFile, lineFromFile);
    int numMines = stoi(lineFromFile);

    sf::RenderWindow window(sf::VideoMode(numColumns * 32, numRows * 32 + 88), "Mindsweeper");
    Board game(numColumns, numRows, numMines);
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if (event.mouseButton.button == sf::Mouse::Left)
                    game.Left(x, y);
                else
                    game.Right(x, y);
            }
            window.clear();
            game.Show(window);
            window.display();
        }

        window.clear();
        game.Show(window);
        window.display();
    }

    TextureManager::Clear();
    return 0;
}