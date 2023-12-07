#include "Pet.h"

void Pet::initVariables()
{
	this->frameHeight = 15;
	this->frameWidth = 32;
	this->currentIdleFrame = 0;
	this->currentMovingFrame = 0;
	this->currentSleepingFrame = 0;

	this->scale = 2.5f;

	this->switchIdleFrameInterval = 0.125f;
	this->switchMovingFrameInterval = 0.125f;
	this->switchBetweenIdleFrameInterval = 0;
	this->switchJumpingFrameInterval = 0.125f;
	this->gravityForce = 0.06f;
	this->jumpHeight = 3.f;
	this->jumpImpulse = 0.f;

	this->isOnGround = true;
	this->overFall = false;
}

void Pet::initTexture()
{
	if(!this->sleepingTexture.loadFromFile("Textures/pets/fox.png"))
		std::cout << "ERROR::PET::INITTEXTURE::Erro ao carregar textura!";

	if (!this->movingTexture.loadFromFile("Textures/pets/fox_moving.png"))
		std::cout << "ERROR::PET::INITTEXTURE::Erro ao carregar textura!";
	
	if (!this->idleTexture.loadFromFile("Textures/pets/fox_idle.png"))
		std::cout << "ERROR::PET::INITTEXTURE::Erro ao carregar textura!";

	if (!this->jumpingTexture.loadFromFile("Textures/pets/fox_jumping.png"))
		std::cout << "ERROR::PET::INITTEXTURE::Erro ao carregar textura!";

}

void Pet::initSprite()
{
	this->pet.setTexture(this->idleTexture);
	this->pet.setTextureRect(sf::IntRect(0,0,this->frameWidth, this->frameHeight));
	this->pet.setScale(this->scale, this->scale);
	this->pet.setPosition(this->initPosX-this->pet.getGlobalBounds().width, this->initPosY - this->pet.getGlobalBounds().height);
}

void Pet::updateTextures()
{
	auto elapsedTime = this->timer.getElapsedTime().asSeconds();

	if (!this->isOnGround) {
		this->overFall = true;
		if (elapsedTime >= this->switchJumpingFrameInterval) {

			this->pet.setTexture(this->jumpingTexture);
			if (this->currentJumpingFrame < 10) {
				this->currentJumpingFrame = (currentJumpingFrame + 1) % 11;
				this->timer.restart();
				this->pet.setTextureRect(sf::IntRect(currentJumpingFrame * this->frameWidth, 0, this->frameWidth, this->frameHeight + 3));
			}
		}
	} else if (this->isOnGround && this->overFall) {
		if (currentJumpingFrame == 10) {
			if (elapsedTime >= this->switchJumpingFrameInterval * 2) {

				this->pet.setTextureRect(sf::IntRect(currentJumpingFrame * this->frameWidth, 0, this->frameWidth, this->frameHeight+3));

				this->overFall = false;
				this->timer.restart();
			}
		}
	}
		else if (this->isWalking) {
		if (elapsedTime >= this->switchMovingFrameInterval) {

			this->currentMovingFrame = (currentMovingFrame + 1) % 8;
			this->timer.restart();

			this->pet.setTexture(this->movingTexture);
			this->pet.setTextureRect(sf::IntRect(currentMovingFrame * this->frameWidth, 0, this->frameWidth, this->frameHeight));
		}
	} else if (elapsedTime >= this->switchIdleFrameInterval) {

		if (currentIdleFrame == 4 && this->switchBetweenIdleFrameInterval!=8)
			this->switchBetweenIdleFrameInterval++;
		
		if (currentIdleFrame == 13)
			this->switchBetweenIdleFrameInterval = 0;

		if(this->switchBetweenIdleFrameInterval==8)
			this->currentIdleFrame = (currentIdleFrame + 1) % 14;
		else
			this->currentIdleFrame = (currentIdleFrame + 1) % 5;
		
		this->timer.restart();

		this->pet.setTexture(this->idleTexture);
		this->pet.setTextureRect(sf::IntRect(currentIdleFrame * this->frameWidth, 0, this->frameWidth, this->frameHeight));
	}

}

Pet::Pet(sf::FloatRect playerBounds, int groundH, sf::RenderWindow& gamewindow)
	: groundHeight(groundH), gamewindow(gamewindow)
{
	this->initPosX = playerBounds.getPosition().x;
	this->initPosY = this->gamewindow.getSize().y - this->groundHeight;
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Pet::~Pet()
{
}

void Pet::update(bool walking)
{
	this->updateTextures();
	this->isWalking = walking;
	this->gravity();
}

void Pet::render(sf::RenderTarget& window)
{
	window.draw(this->pet);
}

void Pet::move(float speed)
{
	this->pet.move(speed, 0);
}

void Pet::setPosition(int posX, std::string direction)
{
	if (direction == "Left") {
		this->pet.setPosition(posX + this->frameWidth * 2.f, this->pet.getPosition().y);
		this->pet.setScale(-this->scale, this->scale);
	}
	else {
		this->pet.setPosition(posX - this->frameWidth * 2.f, this->pet.getPosition().y);
		this->pet.setScale(this->scale, this->scale);
	}
}

void Pet::gravity()
{
	if (!this->isOnGround) {
		this->pet.setPosition(this->pet.getPosition().x, this->pet.getPosition().y - this->jumpImpulse);
		this->jumpImpulse -= this->gravityForce;
	} else
		this->pet.setPosition(this->pet.getPosition().x, this->gamewindow.getSize().y - this->groundHeight - this->pet.getGlobalBounds().height);
}

void Pet::jump()
{
	this->jumpImpulse = this->jumpHeight;
	this->isOnGround = false;
	this->currentJumpingFrame = 0;
}

void Pet::isOnFloor()
{
	this->isOnGround = true;
}
