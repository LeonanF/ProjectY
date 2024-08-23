#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

enum Direction{
	Right,
	Left
};

class Player
{
private:

	//SFML
	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	//Variáveis
	int playerWidth;
	int playerHeight;
	float playerScale;
	float playerSpeed;

public:
	Player(sf::Vector2f);

	void move(Direction);
	void render(sf::RenderTarget&) const;

};