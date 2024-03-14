// This is the header file for Maze.cpp which deals with cells and the ascii map to help render

#ifndef MAZE_H
#define MAZE_H

#include "main.h"

// Types of cell
enum cell_type
{
	Door,
	Empty,
	Energizer,
	Pellet,
	Wall
};

// Cell details
struct Cell {
	char c;
	int position_x;
	int position_y;
	cell_type cellType;
	sf::RectangleShape* rectangle;
	sf::CircleShape* circle;
};

// Handles maze data and wall and door and cells
class Maze {
	private:
		std::vector<std::string> mazeData;
		sf::Texture wallTexture;
		sf::Texture doorTexture;
		std::vector<std::vector<Cell>> cells;

	public:
		Maze(); // constructor
		void convertMaptoCells(); // to get map in readable format
		void renderSetUp(sf::RenderWindow* window); // takes window to render the set up maze
		void renderMaze(sf::RenderWindow* window); // takes window to render the maze
		~Maze(); // deconstructor
		std::vector<std::vector<Cell>>& getCells() { // just a real quick function to return cells
      return cells;
		}
		void setCellType(int x, int y, cell_type newType); // to help identify each type of cell for collision in future
};

#endif