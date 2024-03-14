// A type of ghost

#ifndef B_H
#define B_H

#include "main.h"
#include "Ghosts.h"

class B: public Ghosts {
	private:
		sf::IntRect* bTexture;
  public:
    B();
	void renderCharacter(sf::RenderWindow *window) override;
	sf::IntRect* getTexture() override { return bTexture; }
};

#endif