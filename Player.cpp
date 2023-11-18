#include "Player.h"
#include "iostream"

void Player::initSprite()
{
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setScale(this->playerScale, this->playerScale);

	const auto playerBounds = this->playerSprite.getGlobalBounds();

	this->playerSprite.setPosition(0, this->gameWindow.getSize().y - playerBounds.height);

}

void Player::initTexture()
{
	if (this->playerTexture.loadFromFile("Textures/character/char_blue.png"))
		this->playerSprite.setTextureRect(sf::IntRect(0, 0, 53, 59));
	else
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura.";
}

void Player::initVariables()
{
	this->playerScale = 2.f;
	this->switchStaticFrameInterval = 0.083f;
	this->currentStaticFrame = 0;
	this->staticFrameHeight = 59;
	this->staticFrameWidth = 56;
}

void Player::updateTextures()
{
	auto elapsedTime = this->timer.getElapsedTime().asSeconds();

	if (elapsedTime >= this->switchStaticFrameInterval) {
		
		this->currentStaticFrame = (currentStaticFrame + 1) % 6;
		this->timer.restart();
		this->playerSprite.setTextureRect(sf::IntRect(this->currentStaticFrame * this->staticFrameWidth, 0, this->staticFrameWidth, this->staticFrameHeight));

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
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}
