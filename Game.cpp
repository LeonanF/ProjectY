#include "Game.h"
#include <iostream>

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "TopDown", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

	if (!this->textLayer1.loadFromFile("Textures/background/background_layer_1.png"))
		std::cout << "ERROR::GAME::INITWINDOW::Erro ao carregar textura.";

	this->layer1.setTexture(this->textLayer1);

	this->layer1.setScale(
		static_cast<float>(this->window->getSize().x) / this->layer1.getLocalBounds().width,
		static_cast<float>(this->window->getSize().x) / this->layer1.getLocalBounds().height
	);
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
	this->updateInput();
}

void Game::updateInput()
{

	this->player->setIsWalking(false);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->player->move("Left");
		this->player->setIsWalking(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->player->move("Right");
		this->player->setIsWalking(true);
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && this->player->getOnGround())
		this->player->jump();
	
}

void Game::render()
{

	//Limpa o frame atual
	this->window->clear();

	//Renderiza o novo frame
	this->window->draw(this->layer1);
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
