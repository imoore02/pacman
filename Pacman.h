#ifndef PACMAN_H
#define PACMAN_H

#include "main.h"
#include "Characters.h"

class Pacman: public Characters {
	private:
		bool _alive;
		int _numLives;
		sf::CircleShape* _pacwoman;
	public:
		Pacman();  // Add 'noexcept' here
		void setDt(float new_dt){ _dt = new_dt; }
		sf::CircleShape* getPacwoman(){ return _pacwoman; }
		void updateCharacter(sf::Event& a) {
			if (a.type == sf::Event::KeyPressed)
				printf("KEY PRESSED\n");
		}
		void updateCharacterPosition(sf::Keyboard::Key keyPressed);
		void initCharacter();
		void renderCharacter(sf::RenderWindow* window) override;
		void moveCharacter();
		sf::Vector2f getVelocity();
		void setVelocity(sf::Vector2f newVelocity);
		void setBlueMode(bool blueMode);
};

#endif