#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"

class Game
{
private:
	
	sf::RenderWindow* window;
	Player* player;
	sf::Sprite layer1;
	sf::Sprite layer2;
	sf::Sprite layer3;
	sf::Texture textLayer1;


	void initWindow();
	void initPlayer();
	void initVariables();
	void pollEvents();
	void update();
	void updateInput();
	void render();

public:

	Game();
	~Game();

	void run();

};

