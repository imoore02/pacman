// This is the header file for Game.cpp which has the game loop and the revelant functions outside of the individual classes

#ifndef GAME_H
#define GAME_H

// including relevant files
#include "main.h"
#include "Maze.h"
#include "Pacman.h"
#include "Irene.h"
#include "P.h"
#include "B.h"
#include "C.h"
#include "UnitTest.h"

class Game{
	private:
		sf::RenderWindow* window;
		sf::Event a;
		Maze *maze;   
		Pacman *pacman;
		Ghosts *ghosts[4];
		UnitTest *unitTest;
		sf::Font* font;
		sf::Text *scoreText;
		int score;
		int highScore;
		int blueMode;
		bool isGameOver;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::seconds blueModeTime;
		sf::Text *startText;
	public:
		Game(std::string windowTitle); //The constructor of the Game class, which takes window as a parameter.
		~Game(); // Deconstructor
		void runGame(); // Has the game loop
		void setUpGame(); // Set the initial state of the game
		void eventPolling(); // Handles input events durign the game to close window
		void renderGame(); // Renders the game
		//handleWallCollision offsets pacman back into the lane if it's overlapping with a wall
		void handleWallCollision(sf::RenderWindow* window, sf::CircleShape* pacman, std::vector<std::vector<Cell>>& cells);
		bool checkWallCollision(sf::CircleShape shape1, sf::RectangleShape shape2);
		bool checkPelletCollision(sf::CircleShape shape1, sf::CircleShape shape2);
		//Pacman's pellet collision makes pacman's score go higher
		void handlePelletCollision(sf::CircleShape* pacman, std::vector<std::vector<Cell>>& cells);
		// Runs the ghost's function moveGhosts for each ghost type
		void moveGhosts(std::vector<std::vector<Cell>>& cells, float deltaTime);
		//Pacman colliding with ghost triggers game over unless in blue mode
		void handleGhostCollision(sf::CircleShape* pacman);
		void gameOver();
		int getHighScore();
		void updateHighScore(int score);
		void blueModeTimer();
		void gameWon();
};

#endif