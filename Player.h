#pragma once

#include "SFML/Graphics.hpp"

class Player
{
private:

	//Variáveis da SFML
	sf::Clock timer;
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::RenderWindow& gameWindow;

	//Variáveis
	int currentStaticFrame;
	float playerScale;
	float switchStaticFrameInterval;
	int staticFrameHeight;
	int staticFrameWidth;

	//Fun~ções privadas
	void initSprite();
	void initTexture();
	void initVariables();
	void updateTextures();

public:

	Player(sf::RenderWindow& window);
	~Player();

	//Funções públicas
	void update();
	void render(sf::RenderTarget& target);

};

