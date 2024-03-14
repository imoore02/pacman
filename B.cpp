#include "main.h"
#include "B.h"

B::B() {
	_circle = new sf::CircleShape(18);
	_circle->setTexture(&_ghostTexture);
	bTexture = new sf::IntRect(64, 126, 32, 32);
	_circle->setTextureRect(*bTexture); // Set the texture _circle to match the shape size
	_attackTime = 11;
	_startingPosition.x = CELL_SIZE * 13 * 5;
	_startingPosition.y = CELL_SIZE * 14 * 5 + 2;
	_circle->setPosition(_startingPosition);
  _velocity = {0.f, -1.f};
	_targetPosition = {CELL_SIZE * 13 * 5, CELL_SIZE * 11 * 5};
}

void B::renderCharacter(sf::RenderWindow *window){
	window->draw(*_circle);
}

