#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"

class Game
{
private:
	
	sf::RenderWindow* window;
	Player* player;

	void initWindow();
	void initPlayer();
	void initVariables();
	void pollEvents();
	void update();
	void render();

public:

	Game();
	~Game();

	void run();

};

