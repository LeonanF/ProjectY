#pragma once

#include "SFML/Graphics.hpp"
#include "TileMap.h"

class Game
{
private:
	
	//SFML
	sf::RenderWindow window;
	sf::View camera;
	sf::Clock timer;
	sf::Image icon;

	//Mapa
	TileMap tilemap;

	void pollEvents();
	void handleInput();
	void update();
	void render();

public:

	Game();
	~Game();

	void run();

};

