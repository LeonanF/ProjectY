#include "Game.h"
#include <iostream>
#include <random>

void Game::initTexture()
{
	if (!this->textureLayer1.loadFromFile("Textures/background/background_layer_1.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->textureLayer2.loadFromFile("Textures/background/background_layer_2.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->textureLayer3.loadFromFile("Textures/background/background_layer_3.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->groundTexture.loadFromFile("Textures/tiles/tiles4.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->groundTexture2.loadFromFile("Textures/tiles/tiles3.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->groundTexture3.loadFromFile("Textures/tiles/tiles2.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->shopTexture.loadFromFile("Textures/decorations/shop.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

}

void Game::initSprite()
{
	this->layer1[0].setTexture(this->textureLayer1);
	this->layer1[1].setTexture(this->textureLayer1);
	this->layer1[1].setPosition(layer1[0].getPosition().x - window->getSize().x, 0);

	this->layer2[0].setTexture(this->textureLayer2);
	this->layer2[1].setTexture(this->textureLayer2);
	this->layer2[1].setPosition(layer2[0].getPosition().x - window->getSize().x, 0);

	this->layer3[0].setTexture(this->textureLayer3);
	this->layer3[1].setTexture(this->textureLayer3);
	this->layer3[1].setPosition(layer3[0].getPosition().x - window->getSize().x, 0);

	// Calcular a proporção das texturas
	float scaleX = static_cast<float>(this->window->getSize().x) / this->layer1[1].getLocalBounds().width;
	float scaleY = static_cast<float>(this->window->getSize().y) / this->layer1[1].getLocalBounds().height;


	float scale = std::min(scaleX, scaleY);

	for (int i = 0; i < 2; i++) {
		this->layer1[i].setScale(scale, scale);
		this->layer2[i].setScale(scale, scale);
		this->layer3[i].setScale(scale, scale);
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 2);

	for (int i = 0; i < ceil((this->window->getSize().x * 2)/72); i++) {
		sf::Sprite ground;
		
		if(i== ceil((this->window->getSize().x * 2) / 72) -1 || i==0)
			ground.setTexture(this->groundTexture3);
		else if(dist(gen)==0)
			ground.setTexture(this->groundTexture2);
		else
			ground.setTexture(this->groundTexture);
		
		ground.setScale(2.f, 2.f);
		ground.setPosition((-windowSizeX)+(i*72), this->window->getSize().y - ground.getGlobalBounds().height);

		this->ground.push_back(ground);
	}

	auto lastGround = ceil((this->window->getSize().x * 2) / 72)-1;
	this->ground[lastGround].setTextureRect(sf::IntRect(48, 0, 48, 24));

	auto shopScale = 3.2f;

	this->shop.setTexture(this->shopTexture);
	this->shop.setScale(shopScale, shopScale);
	this->shop.setTextureRect(sf::IntRect(0, 0, 118, 120));
	this->shop.setPosition(-this->windowSizeX/2, this->window->getSize().y-this->shop.getGlobalBounds().height-this->ground[0].getGlobalBounds().height);

}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "ProjectY", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

	if (!this->icon.loadFromFile("logo-icon.png")) {
		std::cout << "ERROR::GAME::INITWINDOW::Erro ao carregar icone.";
	}

	
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	int windowSizeX = this->window->getSize().x;

	this->camera = new sf::View(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y));
	this->camera->setCenter(this->window->getSize().x / 2.0f, this->window->getSize().y / 2.0f);
	this->camera->move(-windowSizeX, 0);
}

void Game::initPlayer()
{
	this->player = new Player(*this->window, this->ground[0].getGlobalBounds().height);
}

void Game::initVariables()
{
	this->windowSizeX = this->window->getSize().x;
	this->switchShopFrameInterval = 0.125f;
	this->currentShopFrame = 0.f;
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
	this->window->setView(*this->camera);
	this->pollEvents();
	this->player->update();
	this->updateInput();
	this->updateShopTexture();
}

void Game::updateInput()
{

	this->player->setIsWalking(false);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->player->move("Left", *this->camera);
		this->player->setIsWalking(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->player->move("Right", *this->camera);
		this->player->setIsWalking(true);
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && this->player->getOnGround())
		this->player->jump();
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && !this->player->getIsAttacking()) {
		this->player->attack();
	}

}

void Game::updateShopTexture()
{
	auto elapsedTime = this->timer.getElapsedTime().asSeconds();

	if (elapsedTime >= this->switchShopFrameInterval) {
		this->shop.setTextureRect(sf::IntRect(this->currentShopFrame * 118, 0, 118, 120));

		this->currentShopFrame = (this->currentShopFrame + 1) % 6;

		this->timer.restart();
	}

}


void Game::render()
{

	//Limpa o frame atual
	this->window->clear();

	//Renderiza o novo frame
	this->window->draw(this->layer1[0]);
	this->window->draw(this->layer1[1]);
	this->window->draw(this->layer2[0]);
	this->window->draw(this->layer2[1]);
	this->window->draw(this->layer3[0]);
	this->window->draw(this->layer3[1]);

	for(auto ground : this->ground)
		this->window->draw(ground);
	
	this->window->draw(this->shop);

	this->player->render(*this->window);
	

	//Exibe o novo frame
	this->window->display();

}

Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initTexture();
	this->initSprite();
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
