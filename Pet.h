#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Pet
{
private:

	//Variáveis privadas
	sf::Clock timer;
	sf::Sprite pet;
	sf::Texture idleTexture;
	sf::Texture movingTexture;
	sf::Texture sleepingTexture;
	sf::Texture jumpingTexture;
	sf::RenderWindow& gamewindow;

	int groundHeight;
	float initPosX;
	float initPosY;
	float scale;

	int currentIdleFrame;
	int currentMovingFrame;
	int currentSleepingFrame;
	int currentJumpingFrame;

	float jumpImpulse;
	float jumpHeight;

	float switchJumpingFrameInterval;
	float switchIdleFrameInterval;
	float switchMovingFrameInterval;
	float switchSleepingFrameInterval;
	int switchBetweenIdleFrameInterval;

	int frameWidth;
	int frameHeight;

	bool isWalking;
	bool isOnGround;
	bool overFall;
	float gravityForce;

	void initVariables();
	void initTexture();
	void initSprite();
	void updateTextures();
	void gravity();

public:

	//Construtor e destrutor
	Pet(sf::FloatRect playerBounds, int groundHeight, sf::RenderWindow& gamewindow);
	~Pet();

	//Funções públicas
	void jump();
	void isOnFloor();
	void move(float speed);
	void setPosition(int posX, std::string direction);
	void update(bool walk);
	void render(sf::RenderTarget& window);

};

