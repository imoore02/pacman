#define MAP_HEIGHT 31
#define MAP_WIDTH 28
#define CELL_SIZE 8

#include "main.h"
#include "Maze.h"


Maze::Maze(){
	//ascii map for rendering the maze;
	mazeData = {
        "||||||||||||||||||||||||||||",
        "|............||............|",
        "|.||||.|||||.||.|||||.||||.|",
        "|o||||.|||||.||.|||||.||||o|",
        "|.||||.|||||.||.|||||.||||.|",
        "|..........................|",
        "|.||||.||.||||||||.||.||||.|",
        "|.||||.||.||||||||.||.||||.|",
        "|......||....||....||......|",
        "||||||.||||| || |||||.||||||",
        "_____|.||||| || |||||.|_____",
        "_____|.||          ||.|_____",
        "_____|.|| |||--||| ||.|_____",
        "||||||.|| |      | ||.||||||",
        "      .   |      |   .      ",
        "||||||.|| |      | ||.||||||",
        "_____|.|| |||||||| ||.|_____",
        "_____|.||          ||.|_____",
        "_____|.|| |||||||| ||.|_____",
        "||||||.|| |||||||| ||.||||||",
        "|............||............|",
        "|.||||.|||||.||.|||||.||||.|",
        "|.||||.|||||.||.|||||.||||.|",
        "|o..||.......  .......||..o|",
        "|||.||.||.||||||||.||.||.|||",
        "|||.||.||.||||||||.||.||.|||",
        "|......||....||....||......|",
        "|.||||||||||.||.||||||||||.|",
        "|.||||||||||.||.||||||||||.|",
        "|..........................|",
        "||||||||||||||||||||||||||||"
    };
}

//moving through the ascii map and based on each character, initating data in a cell struct;
void Maze::convertMaptoCells(){
    // setting height and width for readability
	int height = mazeData.size();
	int width = mazeData[0].size();
	
	cells.resize(height, std::vector<Cell>(width)); //assigning memory for Cells array;

	//looping through and assigning cell types;
 	for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            Cell& cell = cells[row][col];
            cell.c = mazeData[row][col];
            
            // Assign cellType based on the character
            switch (cell.c) {
                case '|':
                    cell.cellType = Wall;
                    break;
				case '.':
                    cell.cellType = Pellet;
                    break;
				case 'o':
                    cell.cellType = Energizer;
                    break;
				case '-':
                    cell.cellType = Door;
                    break;
                case ' ':
                    cell.cellType = Empty;
                    break;
            }
        }
	}
}

//rendering the maze before the game loop starts; assinging shapes and rendering textures;
void Maze::renderSetUp(sf::RenderWindow* window)
{
	// variables 
    sf::Vector2u size = window->getSize();
    unsigned int newWidth = size.x;
	unsigned int newHeight = size.y;

    // Textures from external files
	wallTexture.loadFromFile("blue_square.png");
	doorTexture.loadFromFile("grey_square.jpeg");

	 for (std::size_t y = 0; y < cells.size(); y++) {
        for (std::size_t x = 0; x < cells[y].size(); x++) {

			cells[y][x].position_x = x;
			cells[y][x].position_y = y;

			// Assign cellType based on the character
			switch (cells[y][x].cellType) {
                case Wall:
					cells[y][x].rectangle = new sf::RectangleShape(sf::Vector2f(floor(newWidth/28), floor(newHeight/31)));
					cells[y][x].rectangle->setTexture(&wallTexture);
					cells[y][x].rectangle->setPosition(x * newWidth/28, y * newHeight/31);
                    break;
				case Pellet:
					cells[y][x].circle = new sf::CircleShape((CELL_SIZE / 6) * 5);
					cells[y][x].circle->setPosition((x * newWidth/28 + 16), (y * newHeight/31 + 16));
                    break;
				case Energizer:
					cells[y][x].circle = new sf::CircleShape((CELL_SIZE / 4) * 5);
					cells[y][x].circle->setFillColor(sf::Color(255, 182, 193));
					cells[y][x].circle->setPosition((x * newWidth/28 + 8), (y * newHeight/31 + 8));
                    break;
				case Door:
					cells[y][x].rectangle = new sf::RectangleShape(sf::Vector2f(floor(newWidth/28), floor(newHeight/31)));
					cells[y][x].rectangle->setTexture(&doorTexture);
					cells[y][x].rectangle->setPosition(x * newWidth/28, y * newHeight/31);
                    break;
                case Empty:
                    break;
            }
        }
    }
}


//moves through the cells array and renders the maze based on the cell type and textures;
void Maze::renderMaze(sf::RenderWindow* window)
{
    for (std::size_t y = 0; y < cells.size(); y++) {

        for (std::size_t x = 0; x < cells[y].size(); x++) {

			switch (cells[y][x].cellType) {
                case Wall:
					window->draw(*(cells[y][x].rectangle));
                    break;
				case Pellet:
					window->draw(*(cells[y][x].circle));
                    break;
				case Energizer:
					window->draw(*(cells[y][x].circle));
                    break;
				case Door:
					window->draw(*(cells[y][x].rectangle));
                    break;
                case Empty:
                    break;
            }
        }
    }
}

//change the cell type of a cell in the maze i.e. when pacman eats a pellet
void Maze::setCellType(int x, int y, cell_type newType) {
	cells[y][x].cellType = newType;
}