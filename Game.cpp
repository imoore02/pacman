#include "main.h"
#include "Maze.h"
#include "Pacman.h"
#include "Game.h"
#include "UnitTest.h"
#include <chrono>

using namespace sf;

//The constructor of the Game class, which takes window as a parameter.
Game::Game(std::string windowTitle){
	const int windowWidth = CELL_SIZE * MAP_WIDTH * 5;
	const int windowHeight = CELL_SIZE * MAP_HEIGHT * 5;
	window = new RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Close); 
	window->setFramerateLimit(120);
  window->setView(sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)));
	//creating maze
	maze = new Maze();
	//creating pacman
	pacman = new Pacman();

	unitTest = new UnitTest();

	//ghost = new Ghosts();
	ghosts[0] = new Irene();
	ghosts[1] = new P();
	ghosts[2] = new B();
	ghosts[3] = new C();

	//score details
	font = new sf::Font();
	font->loadFromFile("ARCADECLASSIC.TTF");

	scoreText = new sf::Text();
	scoreText->setFont(*font);
	scoreText->setCharacterSize(30);
	scoreText->setFillColor(sf::Color::White);
	scoreText->setPosition(CELL_SIZE * 5, CELL_SIZE - 8);
	startText = new sf::Text();
	score = 0;
	highScore = getHighScore();
	isGameOver = false;
	blueMode = false;
	blueModeTime = std::chrono::seconds(10);
}

//Starts the game loop
void Game::runGame(){

	sf::Clock		dt_clock;
	sf::Time		elapsed_time;

	setUpGame();

	if (window->isOpen())
	{
		while (window->pollEvent(a))
		{
			if (a.type == sf::Event::Closed)
				window->close();
		}
	startText->setFont(*font);
	startText->setCharacterSize(40);
	startText->setFillColor(sf::Color::White);
	startText->setPosition(CELL_SIZE * 49, CELL_SIZE * 30);
	startText->setString("Eat   the   pellets");
	window->draw(*startText);
	startText->setPosition(CELL_SIZE * 46, CELL_SIZE * 60);
	startText->setString("Avoid   the   ghosts");
	window->draw(*startText);
	startText->setPosition(CELL_SIZE * 30, CELL_SIZE * 90);
	startText->setString("Use   the   arrow   keys   to   naviagte");
	window->draw(*startText);
	startText->setPosition(CELL_SIZE * 20, CELL_SIZE * 120);
	startText->setString("Eat   the   energisers   to   kill   the   ghosts");
	window->draw(*startText);

	window->display();
	}
	sf::sleep(sf::seconds(5));

	//game loop
	while(window->isOpen())
	{
		pacman->setDt(dt_clock.restart().asSeconds());
		while (window->pollEvent(a))
		{
			switch (a.type)
			{
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::KeyPressed:
				{
					if (a.key.code == sf::Keyboard::Escape)
						window->close();
					break;
				}
				case sf::Event::Resized:
				{
					sf::FloatRect visibleArea(0, 0, a.size.width, a.size.height);
					window->setView(sf::View(visibleArea));
					break;
				}
       			default:
          			break;
			}
		}

		sf::Keyboard::Key pressed;
		pressed = a.key.code;
		pacman->updateCharacterPosition(pressed);
		pacman->getPacwoman()->move(pacman->getVelocity());

		float deltaTime = dt_clock.restart().asSeconds();
		moveGhosts(maze->getCells(), deltaTime);
		
		handleWallCollision(window, pacman->getPacwoman(), maze->getCells());
		handlePelletCollision(pacman->getPacwoman(), maze->getCells());
		handleGhostCollision(pacman->getPacwoman());
		renderGame();
		window->display();
		if (blueMode) {
			blueModeTimer();
		}
		updateHighScore(score);
		if (isGameOver){
			gameOver();
			window->close();
			break;
		}
		if (score >= 2760){
			gameWon();
			window->close();
			break;
		}
	}
} 

//Hnadles duration of blue mode
void Game::blueModeTimer() {
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::seconds elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
	unitTest->timeTest(elapsedTime);
    if (elapsedTime >= blueModeTime) {
        blueMode = false;
        pacman->setBlueMode(false);
        ghosts[0]->setBlueMode(false, ghosts[0]->getCircle(), ghosts[0]->getTexture());
        ghosts[1]->setBlueMode(false, ghosts[1]->getCircle(), ghosts[1]->getTexture());
        ghosts[2]->setBlueMode(false, ghosts[2]->getCircle(), ghosts[2]->getTexture());
        ghosts[3]->setBlueMode(false, ghosts[3]->getCircle(), ghosts[3]->getTexture());
		if (ghosts[0]->getDead()) {
			ghosts[0]->setDead(false);
		}
		if (ghosts[1]->getDead()) {
			ghosts[1]->setDead(false);
		}
		if (ghosts[2]->getDead()) {
			ghosts[2]->setDead(false);
		}
		if (ghosts[3]->getDead()) {
			ghosts[3]->setDead(false);
		}
		unitTest->timeTest(elapsedTime);
	}
}

//Returns the high score
int Game::getHighScore(){
	int highScore = 0;
	std::ifstream inputFile("highscore.txt");
	if (inputFile.is_open()) {
		inputFile >> highScore;
		inputFile.close();
	}
	return highScore;
}

// Updating the high score
void Game::updateHighScore(int score){
	std::ofstream outputFile("highscore.txt");
	if (outputFile.is_open()) {
		outputFile << score;
		outputFile.close();
	}
}


// Set the initial state of the game
void Game::setUpGame(){
	pacman->initCharacter();
	maze->convertMaptoCells();
	maze->renderSetUp(window);
}


// Handles input events durign the game to close window
void Game::eventPolling(){
	while (window->pollEvent(a))
	{
		switch (a.type)
		{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				if (a.key.code == sf::Keyboard::Escape)
					window->close();
				break;
			default:
				break;
		}
	}
}

// Runs the ghost's function moveGhosts for each ghost type
void Game::moveGhosts(std::vector<std::vector<Cell>>& cells, float deltaTime)
{
	for (int i = 0; i < 4; i++) {
		ghosts[i]->moveGhost(cells, deltaTime, window);
	}
}

// Renders the game
void Game::renderGame(){
	window->clear(); 
	maze->renderMaze(window);
	window->draw(*(pacman->getPacwoman()));
	ghosts[0]->renderCharacter(window);
	ghosts[1]->renderCharacter(window);
	ghosts[2]->renderCharacter(window);
	ghosts[3]->renderCharacter(window);
	scoreText->setString("Score " + std::to_string(score) + "   " + "High Score " + std::to_string(highScore));
	window->draw(*scoreText);
}


// deconstructor
Game::~Game(){
	delete window;
}

// Function to check collision between two shapes
bool Game::checkWallCollision(sf::CircleShape shape1, sf::RectangleShape shape2) {
	bool collision = shape1.getGlobalBounds().intersects(shape2.getGlobalBounds());
    return collision;
}

// Handles collisions with the wall for the sprites
void Game::handleWallCollision(sf::RenderWindow* window, sf::CircleShape* pacwoman, std::vector<std::vector<Cell>>& cells) {
  sf::FloatRect pacwomanBounds = pacwoman->getGlobalBounds();
	sf::Vector2f position = pacwoman->getPosition();

  float radius = pacwoman->getRadius();
  // Get the size of the window
  sf::Vector2u windowSize = window->getSize();

	if (position.x + radius < 0) {
    // Circle is outside the left wall, wrap it to the right
    pacwoman->setPosition(windowSize.x + radius, position.y);
  } else if (position.x - radius > windowSize.x) {
    // Circle is outside the right wall, wrap it to the left
    pacwoman->setPosition(-radius, position.y);
  }

	// for pacman
	for (const auto& row : cells) {
		for (const auto& cell : row) {
			if (cell.cellType == Wall || cell.cellType == Door) {
				sf::FloatRect wallBounds = cell.rectangle->getGlobalBounds();
				//wallBounds.width += 2;
				//wallBounds.height += 2;

				// Calculate the overlap between pacman and the wall
				sf::FloatRect overlap;
				if (pacwomanBounds.intersects(wallBounds, overlap)) {
					// Calculate the desired offset to move Pacman outside the wall
					float offset = 2.0f;

					// Move pacman outside the wall with the desired offset
					if (overlap.width < overlap.height) {
						if (pacwomanBounds.left < wallBounds.left) {
								pacwoman->move(-overlap.width - offset, 0);
						} else {
								pacwoman->move(overlap.width + offset, 0);
						}
					} else {
						if (pacwomanBounds.top < wallBounds.top) {
								pacwoman->move(0, -overlap.height - offset);
						} else {
								pacwoman->move(0, overlap.height + offset);
						}
					}
				}
			}
		}
	}

	// Running 4 times for each of the 4 ghosts
	for (int i = 0; i < 4; i++) {
		for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell.cellType == Wall) {
                sf::FloatRect wallBounds = cell.rectangle->getGlobalBounds();
								sf::FloatRect ghostBounds = ghosts[i]->getCircle()->getGlobalBounds();

                // Calculate the overlap between pacman and the wall
                sf::FloatRect overlap;
                if (ghostBounds.intersects(wallBounds, overlap)) {
                    // Calculate the desired offset to move Pacman outside the wall
                    float offset = 0.5f;

                    // Move pacman outside the wall with the desired offset
                    if (overlap.width < overlap.height) {
                        if (ghostBounds.left < wallBounds.left) {
                            ghosts[i]->getCircle()->move(-overlap.width - offset, 0);
                        } else {
                            ghosts[i]->getCircle()->move(overlap.width + offset, 0);
                        }
                    } else {
                        if (ghostBounds.top < wallBounds.top) {
                            ghosts[i]->getCircle()->move(0, -overlap.height - offset);
                        } else {
                            ghosts[i]->getCircle()->move(0, overlap.height + offset);
                        }
                    }
                }
            }
        }
    }
	}
}


// Function to check collision between two shapes
bool Game::checkPelletCollision(sf::CircleShape shape1, sf::CircleShape shape2) {
	bool collision = shape1.getGlobalBounds().intersects(shape2.getGlobalBounds());
    return collision;
}

// Handling pellet collisions for pacman
void Game::handlePelletCollision(sf::CircleShape* pacwoman, std::vector<std::vector<Cell>>& cells) {
    sf::FloatRect pacwomanBounds = pacwoman->getGlobalBounds();

    for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell.cellType == Pellet) {
				sf::FloatRect overlap;
                sf::FloatRect pelletBounds = cell.circle->getGlobalBounds();
                if (pacwomanBounds.intersects(pelletBounds, overlap)) {
					cell.circle->setFillColor(sf::Color::Transparent);
					maze->setCellType(cell.position_x, cell.position_y, Empty);
					score += 10;
                }
            }
			else if (cell.cellType == Energizer) {
				sf::FloatRect overlap;
				sf::FloatRect energiserBounds = cell.circle->getGlobalBounds();
				if (pacwomanBounds.intersects(energiserBounds, overlap)) {
					cell.circle->setFillColor(sf::Color::Transparent);
					maze->setCellType(cell.position_x, cell.position_y, Empty);
					blueMode = true;
					startTime = std::chrono::steady_clock::now();
					score += 50;
					pacman->setBlueMode(true);
					ghosts[0]->setBlueMode(true, ghosts[0]->getCircle(), ghosts[0]->getTexture());
					ghosts[1]->setBlueMode(true, ghosts[1]->getCircle(), ghosts[1]->getTexture());
					ghosts[2]->setBlueMode(true, ghosts[2]->getCircle(), ghosts[2]->getTexture());
					ghosts[3]->setBlueMode(true, ghosts[3]->getCircle(), ghosts[3]->getTexture());
				}
			}
			if (score > highScore) {
				highScore = score;
			}
			//unitTest->testScore(score);
    }
  }
}

// Handling pacmans collision with the ghosts e.g. dying and setting ghosts to dead if blue mode
void Game::handleGhostCollision(sf::CircleShape* pacman) {
	for (int i = 0; i < 4; ++i) {
		Ghosts* ghost = ghosts[i];
		sf::FloatRect ghostBounds = ghost->getCircle()->getGlobalBounds();
		sf::FloatRect pacmanBounds = pacman->getGlobalBounds();
		sf::FloatRect overlap;
		if (pacmanBounds.intersects(ghostBounds, overlap)) {
			if (blueMode == false && ghost->getDead() == false){
				pacman->setFillColor(sf::Color::Transparent);
				isGameOver = true;
			} else if (blueMode == true && ghost->getDead() == false){
				ghost->getCircle()->setTextureRect(sf::IntRect(256, 160, 32, 32));
				ghost->setDead(true);
				score += 200;
			}
		}
	}
}

void Game::gameWon(){
	window->clear(sf::Color::Black);
	sf::Text gameWonText;
	gameWonText.setFont(*font);
	gameWonText.setString("Game Won!");
	gameWonText.setCharacterSize(64);
	gameWonText.setFillColor(sf::Color::White);
	gameWonText.setPosition(CELL_SIZE * 11 * 6, CELL_SIZE * 14 * 5 + 2);
	window->draw(gameWonText);
	window->display();
	sf::sleep(sf::seconds(3));
}

void Game::gameOver(){
	window->clear(sf::Color::Black);
	sf::Text gameOverText;
	gameOverText.setFont(*font);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(CELL_SIZE * 11 * 5, CELL_SIZE * 14 * 5 + 2);
	window->draw(gameOverText);
	window->display();
	sf::sleep(sf::seconds(3));
}