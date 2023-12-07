#pragma once

#include "SFML/Graphics.hpp"
#include "Pet.h"

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
	sf::Texture attackTexture;
	sf::RenderWindow& gameWindow;
	Pet* fox;

	//Variáveis
	int currentStaticFrame;
	int currentMovingFrame;
	int currentJumpingFrame;
	int currentAttackingFrame;

	sf::Clock updateTimer;
	sf::Time deltaTime;
	sf::Time attackTimer;
	sf::Time attackCooldown;
	int windowSizeX;
	int groundHeight;
	float playerScale;

	float attackDamage;
	float attackMultiplier;

	float switchStaticFrameInterval;
	float switchMovingFrameInterval;
	float switchJumpingFrameInterval;
	float switchAttackingFrameInterval;

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
	bool isAttacking;
	bool canAttack;
	bool overFall;

	//Funções privadas
	void initSprite();
	void initTexture();
	void initVariables();
	void initPet();
	void isTouchingBorderWindow();
	void updateTextures();
	void updateCooldown();
	void gravity();

public:

	Player(sf::RenderWindow& window, int groundH);
	~Player();

	//Funções públicas
	void update();
	void render(sf::RenderTarget& target);
	void move(std::string direction,  sf::View& gameView);
	void jump();
	void attack();
	bool getOnGround();
	bool getIsAttacking();
	void setIsWalking(bool isWalking);
	sf::FloatRect getPlayerBounds();
};

