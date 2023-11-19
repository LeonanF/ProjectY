#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"

class Game
{
private:
	
	sf::RenderWindow* window;
	Player* player;
	sf::Sprite layer1[2];
	sf::Sprite layer2[2];
	sf::Sprite layer3[2];
	std::vector<sf::Sprite> ground;
	sf::Sprite shop;
	sf::Texture shopTexture;
	sf::Texture groundTexture;
	sf::Texture groundTexture2;
	sf::Texture groundTexture3;
	sf::Texture textureLayer1;
	sf::Texture textureLayer2;
	sf::Texture textureLayer3;
	sf::View* camera;
	sf::Clock timer;

	int windowSizeX;
	float switchShopFrameInterval;
	int currentShopFrame;

	void initTexture();
	void initSprite();
	void initWindow();
	void initPlayer();
	void initVariables();
	void pollEvents();
	void update();
	void updateInput();
	void updateShopTexture();
	void render();

public:

	Game();
	~Game();

	void run();

};

