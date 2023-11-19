#include "Player.h"
#include "iostream"

void Player::initSprite()
{
	this->playerSprite.setTexture(this->staticTexture);
	this->playerSprite.setScale(this->playerScale, this->playerScale);

	const auto playerBounds = this->playerSprite.getGlobalBounds();

	this->playerSprite.setPosition(0, this->gameWindow.getSize().y - playerBounds.height*2);

}

void Player::initTexture()
{
	if (this->staticTexture.loadFromFile("Textures/character/char_idle.png"))
		this->playerSprite.setTextureRect(sf::IntRect(0, 0, this->frameWidth, this->frameHeight));
	else
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura.";

	if (!this->movingTexture.loadFromFile("Textures/character/char_run.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura.";

	if (!this->jumpTexture.loadFromFile("Textures/character/char_jumpnfall.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura.";
}

void Player::initVariables()
{
	this->playerScale = 2.5f;

	this->switchStaticFrameInterval = 0.083f;
	this->switchMovingFrameInterval = 0.125f;
	this->switchJumpingFrameInterval = 0.118f;

	this->currentStaticFrame = 0;
	this->currentMovingFrame = 0;
	this->currentJumpingFrame = 0;

	this->frameHeight = 35;
	this->frameWidth = 56;
	this->jumpFrameHeight = 41;

	this->movespeed = 5.0f;
	this->jumpHeight = 15.f;
	this->jumpImpulse = 0.f;
	this->gravityForce = 0.25f;

	this->onGround = false;
	this->needToCorrectPosition = true;
	this->isWalking = false;
}

void Player::isTouchingBorderWindow()
{
	sf::FloatRect spriteBounds = this->playerSprite.getGlobalBounds();
	sf::Vector2u windowSize = this->gameWindow.getSize();

	if (spriteBounds.top + spriteBounds.height > windowSize.y) {
		this->jumpImpulse = 0.f;
		this->onGround = true;
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, windowSize.y - (spriteBounds.height));
	}
}

void Player::updateTextures()
{
	auto elapsedTime = this->timer.getElapsedTime().asSeconds();


	if (!this->onGround) {
		if (elapsedTime >= this->switchJumpingFrameInterval) {
			this->playerSprite.setTexture(this->jumpTexture);
			this->playerSprite.setTextureRect(sf::IntRect(currentJumpingFrame * this->frameWidth, 0, this->frameWidth, this->jumpFrameHeight));

			std::cout << "Pulo e queda: " << currentJumpingFrame << std::endl;

			this->currentJumpingFrame = (this->currentJumpingFrame + 1) % 16;
			this->timer.restart();
		}
	}
	else if (this->isWalking) {
		if (elapsedTime >= this->switchMovingFrameInterval) {
			
			this->playerSprite.setTexture(this->movingTexture);
			this->playerSprite.setTextureRect(sf::IntRect(currentMovingFrame * this->frameWidth, 0, this->frameWidth, this->frameHeight));

			this->currentMovingFrame = (currentMovingFrame + 1) % 8;
			this->timer.restart();

		}
	} else if (elapsedTime >= this->switchStaticFrameInterval) {

			this->currentStaticFrame = (currentStaticFrame + 1) % 6;
			this->timer.restart();

			this->playerSprite.setTexture(this->staticTexture);
			this->playerSprite.setTextureRect(sf::IntRect(currentStaticFrame * this->frameWidth, 0, this->frameWidth, this->frameHeight));
		}
}

void Player::gravity()
{
	if (!this->onGround) {
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, this->playerSprite.getPosition().y - this->jumpImpulse);
		this->jumpImpulse -= this->gravityForce;
	}


}

Player::Player(sf::RenderWindow& window)
	: gameWindow(window)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::update()
{
	this->updateTextures();
	this->isTouchingBorderWindow();
	this->gravity();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}

void Player::move(std::string direction)
{

	if (direction == "Left") {
		this->playerSprite.move(this->movespeed * this->speedMultiplier.moveLeft, 0);
		this->playerSprite.setScale(-this->playerScale, this->playerScale);

		if (needToCorrectPosition) {
			this->playerSprite.setPosition(this->playerSprite.getPosition().x+this->frameWidth*2.f, this->playerSprite.getPosition().y);
			this->needToCorrectPosition = false;
		}

	}

	if (direction == "Right") {
		this->playerSprite.move(this->movespeed * this->speedMultiplier.moveRight, 0);
		this->playerSprite.setScale(this->playerScale, this->playerScale);

		if (!needToCorrectPosition) {
			this->playerSprite.setPosition(this->playerSprite.getPosition().x - this->frameWidth*2.f , this->playerSprite.getPosition().y);
			this->needToCorrectPosition = true;
		}

	}
}

void Player::jump()
{
	this->jumpImpulse = this->jumpHeight;
	this->onGround = false;
}

bool Player::getOnGround()
{
	return this->onGround;
}

void Player::setIsWalking(bool isWalking)
{
	this->isWalking = isWalking;
}
