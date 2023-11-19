#include "Player.h"
#include "iostream"

void Player::initSprite()
{
	this->playerSprite.setTexture(this->staticTexture);
	this->playerSprite.setScale(this->playerScale, this->playerScale);

	const auto playerBounds = this->playerSprite.getGlobalBounds();

	this->playerSprite.setPosition(this->gameWindow.getSize().x / 3.f - windowSizeX, this->gameWindow.getSize().y - playerBounds.height * 1.2f);
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

	if (!this->attackTexture.loadFromFile("Textures/character/char_attack.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura.";
}

void Player::initVariables()
{
	this->playerScale = 2.5f;

	this->switchStaticFrameInterval = 0.083f;
	this->switchMovingFrameInterval = 0.125f;
	this->switchAttackingFrameInterval = 0.083f;
	this->switchJumpingFrameInterval = 0.120f;

	this->currentStaticFrame = 0;
	this->currentMovingFrame = 0;
	this->currentJumpingFrame = 0;
	this->currentAttackingFrame = 0;

	this->frameHeight = 35;
	this->frameWidth = 56;
	this->jumpFrameHeight = 41;

	this->windowSizeX = this->gameWindow.getSize().x;

	this->movespeed = 5.0f;
	this->jumpHeight = 15.f;
	this->jumpImpulse = 0.f;
	this->gravityForce = 0.25f;

	this->deltaTime = this->updateTimer.restart();
	this->attackCooldown = sf::seconds(2.f);
	this->attackTimer = sf::milliseconds(0.f);

	this->onGround = false;
	this->needToCorrectPosition = true;
	this->isWalking = false;
	this->isAttacking = false;
	this->canAttack = true;

}

void Player::isTouchingBorderWindow()
{
	sf::FloatRect spriteBounds = this->playerSprite.getGlobalBounds();
	sf::Vector2u windowSize = this->gameWindow.getSize();

	if (spriteBounds.top + spriteBounds.height > windowSize.y - this->groundHeight) {
		this->jumpImpulse = 0.f;
		this->onGround = true;
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, windowSize.y - spriteBounds.height - this->groundHeight);
	}

	if (spriteBounds.left + (spriteBounds.width / 3.9f) < -1920)
		this->speedMultiplier.moveLeft = 0.f;
	else
		this->speedMultiplier.moveLeft = -1.f;

	if (spriteBounds.left + (spriteBounds.width / 1.3f) > windowSize.x)
		this->speedMultiplier.moveRight = 0.f;
	else
		this->speedMultiplier.moveRight = 1.f;

}

void Player::updateTextures()
{
	auto elapsedTime = this->timer.getElapsedTime().asSeconds();

	if (this->isAttacking) {
		if (elapsedTime >= this->switchAttackingFrameInterval) {

			this->playerSprite.setTexture(this->attackTexture);

			this->playerSprite.setTextureRect(sf::IntRect(currentAttackingFrame * this->frameWidth, -10, this->frameWidth, this->frameHeight + 10));

			this->currentAttackingFrame = (this->currentAttackingFrame + 1) % 6;

			if(!this->onGround)
				this->currentJumpingFrame = (this->currentJumpingFrame + 1) % 16;

			this->timer.restart();
		}
		
		if (this->currentAttackingFrame == 5) {
			this->currentAttackingFrame = 0;
			this->isAttacking = false;
			this->updateTimer.restart();
		}
	}
	else if (!this->onGround) {
		this->overFall = true;
		if (elapsedTime >= this->switchJumpingFrameInterval) {

			this->playerSprite.setTexture(this->jumpTexture);
			
			if (this->currentJumpingFrame < 15) {
				this->playerSprite.setTextureRect(sf::IntRect(currentJumpingFrame * this->frameWidth, 0, this->frameWidth, this->jumpFrameHeight));

				this->currentJumpingFrame = (this->currentJumpingFrame + 1) % 16;
				this->timer.restart();
			}
		}
	}
	else if (this->onGround && this->overFall) {
		if (currentJumpingFrame == 15) {
			if (elapsedTime >= this->switchJumpingFrameInterval*2) {

				this->playerSprite.setTextureRect(sf::IntRect(currentJumpingFrame * this->frameWidth, 0, this->frameWidth, this->jumpFrameHeight));

				this->overFall = false;
				this->timer.restart();
			}
		}
	}
	else if (this->isWalking) {
		if (elapsedTime >= this->switchMovingFrameInterval) {
			
			this->playerSprite.setTexture(this->movingTexture);
			this->playerSprite.setTextureRect(sf::IntRect(currentMovingFrame * this->frameWidth, -10, this->frameWidth, this->frameHeight+10));

			this->currentMovingFrame = (currentMovingFrame + 1) % 8;
			this->timer.restart();

		}
	}
	else if (elapsedTime >= this->switchStaticFrameInterval) {

			this->currentStaticFrame = (currentStaticFrame + 1) % 6;
			this->timer.restart();

			this->playerSprite.setTexture(this->staticTexture);
			this->playerSprite.setTextureRect(sf::IntRect(currentStaticFrame * this->frameWidth, -10, this->frameWidth, this->frameHeight+10));
		}
}

void Player::updateCooldown()
{

	if (!this->canAttack) {
		this->attackTimer += this->deltaTime;
		if (attackTimer > this->attackCooldown) {
			this->canAttack = true;
			attackTimer = sf::Time::Zero;
		}
	}

}

void Player::gravity()
{
	if (!this->onGround) {
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, this->playerSprite.getPosition().y - this->jumpImpulse);
		this->jumpImpulse -= this->gravityForce;
	}


}

Player::Player(sf::RenderWindow& window, int groundH)
	: gameWindow(window), groundHeight(groundH)
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
	this->updateCooldown();

	this->deltaTime = this->updateTimer.restart();

	if (timer.getElapsedTime().asSeconds() > this->switchJumpingFrameInterval * 4)
		this -> overFall = false;

	this->updateTextures();
	this->isTouchingBorderWindow();
	this->gravity();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}

void Player::move(std::string direction, sf::View& gameView)
{

	if (direction == "Left" && !this->isAttacking) {
		if (!this->isAttacking) {
			this->playerSprite.move(this->movespeed * this->speedMultiplier.moveLeft, 0);

			if (gameView.getCenter().x > -this->windowSizeX / 2 && this->playerSprite.getPosition().x < gameView.getCenter().x)
				gameView.move(this->movespeed * this->speedMultiplier.moveLeft, 0);

			this->playerSprite.setScale(-this->playerScale, this->playerScale);

			if (needToCorrectPosition) {
				this->playerSprite.setPosition(this->playerSprite.getPosition().x + this->frameWidth * 2.f, this->playerSprite.getPosition().y);
				this->needToCorrectPosition = false;
			}

		}
	}

	if (direction == "Right") {
		if (!this->isAttacking) {
			this->playerSprite.move(this->movespeed * this->speedMultiplier.moveRight, 0);

			if (gameView.getCenter().x<this->windowSizeX / 2 && this->playerSprite.getPosition().x > gameView.getCenter().x)
				gameView.move(this->movespeed * this->speedMultiplier.moveRight, 0);
			this->playerSprite.setScale(this->playerScale, this->playerScale);

			if (!needToCorrectPosition) {
				this->playerSprite.setPosition(this->playerSprite.getPosition().x - this->frameWidth * 2.f, this->playerSprite.getPosition().y);
				this->needToCorrectPosition = true;
			}
		}

	}
}

void Player::jump()
{
	this->jumpImpulse = this->jumpHeight;
	this->onGround = false;
	this->currentJumpingFrame = 0;
}

void Player::attack()
{
	if (this->canAttack) {
		this->isAttacking = true;
		this->canAttack = false;
	}
}

bool Player::getOnGround()
{
	return this->onGround;
}

bool Player::getIsAttacking()
{
	return this->isAttacking;
}

void Player::setIsWalking(bool isWalking)
{
	this->isWalking = isWalking;
}
