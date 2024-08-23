#pragma once

#include "SFML/Graphics.hpp"
#include "TileMap.h"
#include "Player.h"

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

	//Player
	std::unique_ptr<Player> player;

	void pollEvents();
	void handleInput();
	void update();
	void render();

	// Variáveis
	float zoomViewFactor;

public:

	Game();
	~Game();

	void run();

};

