#include "main.h"
#include "Ghosts.h"
#include "Maze.h"

Ghosts::Ghosts() {
  _speed = 10000.f;
	_ghostTexture.loadFromFile("sprites.png");
	_velocity.x = CELL_SIZE * 13.5 * 5; // starting velocity 
	_velocity.y = CELL_SIZE * 23 * 5 + 2;
	_previousPosition = {CELL_SIZE * 13 * 5, CELL_SIZE * 11 * 5};
	_blueTexture = new sf::IntRect(64, 126, 32, 32);
	isDead = false;
}


void Ghosts::moveGhost(const std::vector<std::vector<Cell>>& cells, float deltaTime, sf::RenderWindow* window) {

	//Making ghost wait for it's specified time and then spawning
	if (_attackClock.getElapsedTime().asSeconds() < _attackTime) {
		return;
	}
	else if (_circle->getPosition() == _startingPosition) {
		_circle->setPosition(CELL_SIZE * 13 * 5, CELL_SIZE * 11 * 5);
	}

	// Ghost past window then wrap it to the other end
	sf::Vector2f position = _circle->getPosition();
  float radius = _circle->getRadius();
  // Get the size of the window
  sf::Vector2u windowSize = window->getSize();

	if (position.x + radius < 0) {
		// Circle is outside the left wall, wrap it to the right
		_circle->setPosition(windowSize.x + radius, position.y);
		_targetPosition = {getScreenPosition({MAP_WIDTH - 6 , 0}).x, position.y};
		std::cout << "Taking shortcut left to right" << std::endl;
	} else if (position.x - radius > windowSize.x) {
		// Circle is outside the right wall, wrap it to the left
		_circle->setPosition(-radius, position.y);
		_targetPosition = {getScreenPosition({6, 0}).x, position.y};
		std::cout << "Taking shortcut right to left" << std::endl;
	}

	//Reached a target, so need a new one
	sf::Vector2f dist = _circle->getPosition() - _targetPosition;

	if (std::sqrt(dist.x*dist.x + dist.y*dist.y) < 1 || _circle->getPosition() == _previousPosition) // aka close enough to last target so we need next target
	{
		sf::Vector2f potentialMoveDir;

		sf::Vector2i currentPosition = getCellPosition(_targetPosition);
		for (int i = 0; i < 10; i++) //so it doesnt go endlessly
		{
			int randomNum = rand() % 4;
			switch (randomNum) {
				case 0:
					potentialMoveDir = sf::Vector2f (0, -1);
					break;
				case 1:
					potentialMoveDir = sf::Vector2f(0, 1);
					break;
				case 2:
					potentialMoveDir = sf::Vector2f (-1, 0);
					break;
				case 3:
					potentialMoveDir = sf::Vector2f(1, 0);
					break;
			}

			// we know that it passed empty cells to get here so can go backwards
			if (potentialMoveDir == -_moveDir) {
				continue;
			}

			// doing checks for potential target and then setting move direction and potential target
			sf::Vector2i potentialTarget = currentPosition + (sf::Vector2i)potentialMoveDir; //static cast
			if (cells[potentialTarget.y][potentialTarget.x].cellType == cell_type::Empty ||
				cells[potentialTarget.y][potentialTarget.x].cellType == cell_type::Pellet || 
				cells[potentialTarget.y][potentialTarget.x].cellType == cell_type::Energizer)
			{
				_moveDir = potentialMoveDir;
				_targetPosition = getScreenPosition(potentialTarget);
				break;
			}
			else {
				continue;
			}
		}	
	}
	// for the next checking:
	_previousPosition = _circle->getPosition();

	// checking if distance is small enough that it wont spawn to set velocity
	if (std::sqrt(dist.x*dist.x + dist.y * dist.y) < _speed * deltaTime ) {
	 	_velocity = _moveDir * std::sqrt(dist.x*dist.x + dist.y * dist.y);
	} else {
		_velocity = _moveDir*_speed*deltaTime;
	}
	_circle->move(_velocity);
}


void Ghosts::renderCharacter(sf::RenderWindow *window){
	if (isDead == true) {
		_circle->setTextureRect(sf::IntRect(256, 160, 32, 32));
	}
	window->draw(*_circle);
}


sf::Vector2i Ghosts::getCellPosition(sf::Vector2f screenPos) {
	sf::Vector2i cellPos;
	cellPos.x = floor(screenPos.x/CELL_SIZE/5); //flooring because int
	cellPos.y = floor(screenPos.y/CELL_SIZE/5);
	return cellPos;
}

sf::Vector2f Ghosts::getScreenPosition(sf::Vector2i cellPos) {
	sf::Vector2f screenPos;
	screenPos.x = CELL_SIZE*cellPos.x*5; // *5 because scaling
	screenPos.y = CELL_SIZE*cellPos.y*5;
	return screenPos;
}

void Ghosts::setBlueMode(bool blueMode, sf::CircleShape* _circle, sf::IntRect* texture){
	if (blueMode == true)
		_circle->setTextureRect(sf::IntRect(256, 126, 32, 32));
	else
		_circle->setTextureRect(*texture);
}

void Ghosts::setDead(bool dead){
	if (dead == true)
		isDead = true;
	else 
		isDead = false;
}