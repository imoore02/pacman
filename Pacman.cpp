#include "main.h"
#include "Characters.h"
#include "Pacman.h"

void Pacman::updateCharacterPosition(sf::Keyboard::Key key) {
    _velocity.y = 0.f;
    _velocity.x = 0.f;

    if (key == sf::Keyboard::Right){
   			_velocity.x += _speed * _dt;
			if (_velocity.x == 0 && _velocity.y == 0){
				std::cout << "hmm movement failed" << std::endl;
			}
	}
    else if (key == sf::Keyboard::Left){
 			_velocity.x += -_speed * _dt;
			if (_velocity.x == 0 && _velocity.y == 0){
				std::cout << "hmm movement failed" << std::endl;
			}
	}
    else if (key == sf::Keyboard::Down){
 			_velocity.y += _speed * _dt;
			if (_velocity.x == 0 && _velocity.y == 0){
				std::cout << "hmm movement failed" << std::endl;
			}
	}
    else if (key == sf::Keyboard::Up){
 			_velocity.y += -_speed * _dt;
			if (_velocity.x == 0 && _velocity.y == 0){
				std::cout << "hmm movement failed" << std::endl;
			}
	}
}



sf::Vector2f Pacman::getVelocity(){
	return _velocity;
}

void Pacman::setVelocity(sf::Vector2f newVelocity){
	_velocity = newVelocity;
}


void Pacman::moveCharacter(){
	_pacwoman->move(_velocity);
}

Pacman::Pacman(){
	_velocity.x = CELL_SIZE * 13.5 * 5;
	_velocity.y = CELL_SIZE * 23 * 5 + 2; 
	_speed = 100.f;
	_pacwoman = new sf::CircleShape((CELL_SIZE / 2) * 5 - 4); //to span half the cellsize
	_alive = true;
	_numLives = 3;
}

void Pacman::initCharacter(){
	_pacwoman->setFillColor(sf::Color(255, 105, 180));
	_pacwoman->setPosition(_velocity.x, _velocity.y);
}

void Pacman::renderCharacter(sf::RenderWindow *window){
	window->draw(*_pacwoman);
}

void Pacman::setBlueMode(bool blueMode){
	if (blueMode == true)
		_pacwoman->setFillColor(sf::Color(173, 216, 230));
	else
		_pacwoman->setFillColor(sf::Color(255, 105, 180));
}