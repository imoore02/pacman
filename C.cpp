#include "main.h"
#include "C.h"

C::C() {
	_circle = new sf::CircleShape(18);
	_circle->setTexture(&_ghostTexture);
	cTexture = new sf::IntRect(64, 222, 32, 32);
	_circle->setTextureRect(*cTexture); // Set the texture _circle to match the shape size
	_attackTime = 9;
	_startingPosition.x = CELL_SIZE * 11.5 * 5;
	_startingPosition.y = CELL_SIZE * 14 * 5 + 2;
	_circle->setPosition(_startingPosition);
  _velocity = {0.f, -1.f};
	_targetPosition = {CELL_SIZE * 13 * 5, CELL_SIZE * 11 * 5};
}

void C::renderCharacter(sf::RenderWindow *window){
	window->draw(*_circle);
}
