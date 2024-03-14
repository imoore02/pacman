// A type of ghost

#ifndef IRENE_H
#define IRENE_H

#include "main.h"
#include "Ghosts.h"

class Irene: public Ghosts {
	private:
	    sf::IntRect* ireneTexture;
  public:
    Irene();
	void renderCharacter(sf::RenderWindow *window) override;
	sf::IntRect* getTexture() override { return ireneTexture; };
};

#endif