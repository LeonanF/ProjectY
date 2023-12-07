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

	if (!this->popupTexture.loadFromFile("Textures/gui/popup.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->buttonTexture.loadFromFile("Textures/gui/button.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->sellerTexture.loadFromFile("Textures/portraits/seller.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->sellerTexture.loadFromFile("Textures/portraits/seller.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->lampTexture.loadFromFile("Textures/decorations/lamp.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	if (!this->signTexture.loadFromFile("Textures/decorations/sign.png"))
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	this->fenceTexture.resize(2);

	for (int i = 0; i < 2; i++) {
		std::string filePath= "Textures/decorations/fence_"+std::to_string(i+1)+".png";

		if (!this->fenceTexture[i].loadFromFile(filePath))
			std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	}

	this->grassTexture.resize(3);

	for (int i = 0; i < 3; i++) {
		std::string filePath = "Textures/decorations/grass_" + std::to_string(i + 1) + ".png";

		if (!this->grassTexture[i].loadFromFile(filePath))
			std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	}
	
	this->rockTexture.resize(3);

	for (int i = 0; i < 3; i++) {
		std::string filePath = "Textures/decorations/rock_" + std::to_string(i + 1) + ".png";

		if (!this->rockTexture[i].loadFromFile(filePath))
			std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura.";

	}
}

void Game::initSprite()
{

	//Background sprite
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

	//Ground sprite
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

	//Correção do último ground
	auto lastGround = ceil((this->window->getSize().x * 2) / 72)-1;
	this->ground[lastGround].setTextureRect(sf::IntRect(48, 0, 48, 24));

	//Shop sprite
	auto shopScale = 3.2f;

	this->shop.setTexture(this->shopTexture);
	this->shop.setScale(shopScale, shopScale);
	this->shop.setTextureRect(sf::IntRect(0, 0, 118, 120));
	this->shop.setPosition(-this->windowSizeX/2, this->window->getSize().y-this->shop.getGlobalBounds().height-this->ground[0].getGlobalBounds().height);

	this->initPopUp();

	//Decorations sprite

	std::uniform_int_distribution<> pos(50, 150);
	std::uniform_int_distribution<> grassType(0, 2);
	std::uniform_int_distribution<> rockType(0, 2);

	int i = -this->windowSizeX;

	while (i < this->windowSizeX) {
		
		sf::Sprite sprite;

		int randomDecoration = std::rand() % 7;
		if (randomDecoration == 0) {
			int textureIndex = rockType(gen);
			sprite.setTexture(this->rockTexture[textureIndex]);
		}
		else {
			int textureIndex = grassType(gen);
			sprite.setTexture(this->grassTexture[textureIndex]);
		}

		int actualPos = i+pos(gen);

		i = actualPos;


		sprite.setPosition(actualPos,this->window->getSize().y-this->ground[0].getGlobalBounds().height-sprite.getGlobalBounds().height);

		sprite.setScale(1.5f, 1.5f);

		this->decorations.push_back(sprite);

	}


}

void Game::initPopUp()
{
	if (!this->font.loadFromFile("Fonts/font.ttf"))
		std::cout << "ERROR::GAME::INITPOPUP::Erro ao carregar fonte.";

	sf::Vector2f popUpSize(this->shop.getGlobalBounds().width, 200);
	sf::FloatRect shopBounds(this->shop.getGlobalBounds());

	this->shopBackground.setSize(popUpSize);
	this->shopBackground.setTexture(&this->popupTexture);
	this->shopBackground.setPosition(shopBounds.left, shopBounds.top - popUpSize.y);

	sf::FloatRect backgroundBounds(this->shopBackground.getGlobalBounds());

	this->seller.setTexture(this->sellerTexture);
	this->seller.setScale(1.5f, 1.5f);
	this->seller.setPosition(backgroundBounds.left + this->seller.getGlobalBounds().width / 2.f, backgroundBounds.top + this->seller.getGlobalBounds().height / 2.f);

	sf::FloatRect sellerBounds(this->seller.getGlobalBounds());

	this->popUpText.setFont(this->font);
	this->popUpText.setString("Boas vindas, visitante!\nO que quer comprar? O que quer vender?");
	this->popUpText.setCharacterSize(16);
	this->popUpText.setFillColor(sf::Color::Black);
	this->popUpText.setPosition(this->shopBackground.getPosition().x+25, this->shopBackground.getPosition().y+25+sellerBounds.height+7.f);

	sf::Vector2f popUpButton(popUpSize.x / 5, popUpSize.y / 5);

	this->shopButton.setSize(popUpButton);
	this->shopButton.setTexture(&this->buttonTexture);
	this->shopButton.setPosition(backgroundBounds.left+backgroundBounds.width-popUpButton.x*1.5f, backgroundBounds.top+backgroundBounds.height-popUpButton.y*1.5f);

	this->buttonText.setFont(this->font);
	this->buttonText.setString(L"Espaço");
	this->buttonText.setCharacterSize(15);
	this->buttonText.setFillColor(sf::Color::White);

	float centerX = shopButton.getPosition().x + (shopButton.getSize().x - buttonText.getGlobalBounds().width) / 2.0f;
	float centerY = shopButton.getPosition().y + (shopButton.getSize().y - buttonText.getGlobalBounds().height) / 2.0f - 7.f;

	this->buttonText.setPosition(centerX, centerY);

}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "ProjectY", sf::Style::Fullscreen);
	this->window->setVerticalSyncEnabled(true);

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
	this->isOnShop = false;
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

	if (!(
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		)) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->player->move("Left", *this->camera);
			this->player->setIsWalking(true);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->player->move("Right", *this->camera);
			this->player->setIsWalking(true);
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && this->player->getOnGround())
		this->player->jump();
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && !this->player->getIsAttacking()) {
		this->player->attack();
	}

	sf::FloatRect playerBounds = this->player->getPlayerBounds();
	sf::FloatRect shopBounds = this->shop.getGlobalBounds();

	if (playerBounds.left > shopBounds.left && playerBounds.left + playerBounds.width < shopBounds.left + shopBounds.width)
		this->isOnShop = true;
	else
		this->isOnShop = false;
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

	for (auto decoration : this->decorations)
		this->window->draw(decoration);

	for(auto ground : this->ground)
		this->window->draw(ground);

	
	this->window->draw(this->shop);
	this->renderShopPopUp();

	this->player->render(*this->window);

	//Exibe o novo frame
	this->window->display();

}

void Game::renderShopPopUp()
{
	if (this->isOnShop) {
		this->window->draw(this->shopBackground);
		this->window->draw(this->popUpText);
		this->window->draw(this->shopButton);
		this->window->draw(this->buttonText);
		this->window->draw(this->seller);
	}
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
