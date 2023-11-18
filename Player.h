#pragma once

#include "SFML/Graphics.hpp"

class Player
{
private:

	//Vari�veis da SFML
	sf::Clock timer;
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::RenderWindow& gameWindow;

	//Vari�veis
	int currentStaticFrame;
	float playerScale;
	float switchStaticFrameInterval;
	int staticFrameHeight;
	int staticFrameWidth;

	//Fun~��es privadas
	void initSprite();
	void initTexture();
	void initVariables();
	void updateTextures();

public:

	Player(sf::RenderWindow& window);
	~Player();

	//Fun��es p�blicas
	void update();
	void render(sf::RenderTarget& target);

};

