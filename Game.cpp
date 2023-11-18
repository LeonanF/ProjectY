#include "Game.h"



void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "TopDown", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player(*this->window);
}

void Game::initVariables()
{
}

void Game::pollEvents()
{

	sf::Event ev;
	while (this->window->isOpen() && this->window->pollEvent(ev)) {
		if (ev.type == sf::Event::Closed)
			this->window->close();
		if (ev.KeyPressed && ev.key.code == sf::Keyboard::Escape)
			this->window->close();
	}

}

void Game::update()
{
	this->pollEvents();
	this->player->update();
}

void Game::render()
{

	//Limpa o frame atual
	this->window->clear();

	//Renderiza o novo frame
	this->player->render(*this->window);

	//Exibe o novo frame
	this->window->display();

}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}
