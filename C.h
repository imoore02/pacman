// A type of ghost

#ifndef C_H
#define C_H

#include "main.h"
#include "Ghosts.h"

class C: public Ghosts {
	private:
		sf::IntRect* cTexture;
 	 public:
		C();
		void renderCharacter(sf::RenderWindow *window) override;
		sf::IntRect* getTexture() override { return cTexture; }
};

#endif