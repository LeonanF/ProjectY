#pragma once

#include "SFML/Graphics.hpp"

struct MoveMultiplier {
	float moveRight = 1.0f;
	float moveLeft = -1.0f;
};

class Player
{
private:

	//Variáveis da SFML
	sf::Clock timer;
	sf::Sprite playerSprite;
	sf::Texture staticTexture;
	sf::Texture movingTexture;
	sf::Texture jumpTexture;
	sf::RenderWindow& gameWindow;

	//Variáveis
	int currentStaticFrame;
	int currentMovingFrame;
	int currentJumpingFrame;

	float playerScale;

	float switchStaticFrameInterval;
	float switchMovingFrameInterval;
	float switchJumpingFrameInterval;

	int frameHeight;
	int frameWidth;
	int jumpFrameHeight;

	float jumpHeight;
	float jumpImpulse;
	float gravityForce;
	
	MoveMultiplier speedMultiplier;
	float movespeed;
	
	bool needToCorrectPosition;
	bool onGround;
	bool isWalking;


	//Funções privadas
	void initSprite();
	void initTexture();
	void initVariables();
	void isTouchingBorderWindow();
	void updateTextures();
	void gravity();

public:

	Player(sf::RenderWindow& window);
	~Player();

	//Funções públicas
	void update();
	void render(sf::RenderTarget& target);
	void move(std::string direction);
	void jump();
	bool getOnGround();
	void setIsWalking(bool isWalking);

};

