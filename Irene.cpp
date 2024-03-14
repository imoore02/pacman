#include "main.h"
#include "Irene.h"

Irene::Irene() {
	_circle = new sf::CircleShape(18);
	_circle->setTexture(&_ghostTexture);
	ireneTexture = new sf::IntRect(64, 192, 32, 32);
	_circle->setTextureRect(*ireneTexture); // Set the texture _circle to match the shape size
	// CHERRY _circle->setTextureRect(sf::IntRect(64, 90, 32, 32)); // Set the texture _circle to match the shape size
  //_circle->setPosition(CELL_SIZE * 14.25 * 5, CELL_SIZE * 14 * 5 + 2); // Set the position of the sprite
	//_circle->setPosition(CELL_SIZE * 14.25 * 5, CELL_SIZE * 14 * 5); // Set the position of the sprite
	_attackTime = 7;
	_startingPosition.x = CELL_SIZE * 14.25 * 5;
	_startingPosition.y = CELL_SIZE * 14 * 5 + 2;
	_circle->setPosition(_startingPosition);
  _velocity = {0.f, -1.f};
	_targetPosition = {CELL_SIZE * 13 * 5, CELL_SIZE * 11 * 5};

}

void Irene::renderCharacter(sf::RenderWindow *window){
	window->draw(*_circle);
}