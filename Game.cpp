#include "Game.h"

void Game::pollEvents()
{

	sf::Event ev;

	while (window.isOpen() && window.pollEvent(ev)) {
		
		if (ev.type == sf::Event::Closed)
			window.close();

		if (ev.KeyPressed && ev.key.code == sf::Keyboard::Escape)
			window.close();

	}

}

void Game::handleInput()
{
}

void Game::update()
{
}

void Game::render()
{
	window.clear();
	window.display();
}

Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "ProjectY", sf::Style::Fullscreen)
{
}

Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen()) {
		pollEvents();
		update();
		render();
	}
}
