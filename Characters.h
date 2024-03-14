// This is an abstract class which provides inherited pacman and ghosts classes with some shared variables and a render function

#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "main.h"

class Characters {
  protected:
		float _speed;
		float _dt; // the time for movement
		sf::Vector2f _velocity;
  public:
		// To be overridden by ghosts and pacman to render themselves, takes window as parameter
    virtual void renderCharacter(sf::RenderWindow* window) = 0;
};

#endif
