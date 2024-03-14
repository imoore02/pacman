// This is an abstract class for ghosts that inherits from characters and it provides the individual ghosts like irene with required variables and functions
#ifndef GHOSTS_H
#define GHOSTS_H

#include "main.h"
#include "Characters.h"
#include "Maze.h"

class Ghosts: public Characters {
  protected:
    sf::CircleShape* _circle; // base of the ghosts sprite
    sf::Texture _ghostTexture;  // texture on the ghosts
    sf::Vector2f _moveDir; // direction to be faced by the ghosts
    sf::Vector2f _targetPosition; // the next position ghosts should head to
    sf::Clock _attackClock; // helps do a "wave attack" feature
    float _attackTime; // is the tume they should spawn out of the cage
    sf::Vector2f _startingPosition; // where in cage
    sf::Vector2f _previousPosition;
	  sf::IntRect* _blueTexture; // for blue eat mode
	  bool isDead;

  public:
    Ghosts(); // constructor
    virtual void renderCharacter(sf::RenderWindow *window); // render the ghost 
    sf::Sprite* getGhostSprite(); // returns the circle of ghost
    sf::Vector2f getDirection(){return _velocity;}
    // moveGhost is called by game to move the individual ghost as needed
    void moveGhost(const std::vector<std::vector<Cell>>& cells, float deltaTime, sf::RenderWindow* window);
    sf::CircleShape* getCircle(){return _circle;}
    sf::Vector2i getCellPosition(sf::Vector2f screenPos); // converts from screen to cell
    sf::Vector2f getScreenPosition(sf::Vector2i cellPos); // converts from cell to screen
	void setBlueMode(bool blueMode, sf::CircleShape* _circle, sf::IntRect* texture); // when pacman eats energiser
	virtual sf::IntRect* getTexture() {
		return _blueTexture;
	}
	void setDead(bool dead);
	bool getDead() { return isDead; }
};

#endif