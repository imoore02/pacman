// A type of ghost

#ifndef P_H
#define P_H

#include "main.h"
#include "Ghosts.h"

class P: public Ghosts {
	private:
		sf::IntRect* pTexture;
 	public:
		P();
		void renderCharacter(sf::RenderWindow *window) override;
		sf::IntRect* getTexture() override { return pTexture; }
};

#endif