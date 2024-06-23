#pragma once

#include "SFML/Graphics.hpp"

class Game
{
private:
	
	sf::RenderWindow window;
	sf::View camera;
	sf::Clock timer;
	sf::Image icon;

	void pollEvents();
	void handleInput();
	void update();
	void render();

public:

	Game();
	~Game();

	void run();

};

