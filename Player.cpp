#include "Player.h"

Player::Player(sf::Vector2f startPosition)
	: playerScale(1.5f), playerWidth(58), playerHeight(35), playerSpeed(5.f)
{
	if (!playerTexture.loadFromFile("Textures/character/char_idle.png")) {
		std::cerr << "ERROR::PLAYER::Falha ao inicializar textura.\n";
		exit(EXIT_FAILURE);
	};

	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(startPosition.x, startPosition.y);
	playerSprite.setTextureRect(sf::IntRect(0,0,58,35));
	playerSprite.setScale(playerScale, playerScale);

}

void Player::move(Direction dir)
{
	switch (dir) {
		case Direction::Left:
			playerSprite.move(sf::Vector2f(-playerSpeed,0));
		break;
		case Direction::Right:
			playerSprite.move(sf::Vector2f(playerSpeed, 0));
			break;
	}
}

void Player::render(sf::RenderTarget& target) const
{
	target.draw(playerSprite);
}