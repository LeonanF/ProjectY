#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"

class Game
{
private:
	
	sf::RenderWindow* window;
	Player* player;
	sf::Sprite layer1[2];
	sf::Sprite layer2[2];
	sf::Sprite layer3[2];
	std::vector<sf::Sprite> ground;
	std::vector<sf::Sprite> decorations;
	sf::Sprite shop;
	sf::Texture shopTexture;
	sf::Texture groundTexture;
	sf::Texture groundTexture2;
	sf::Texture groundTexture3;
	sf::Texture textureLayer1;
	sf::Texture textureLayer2;
	sf::Texture textureLayer3;
	sf::Texture lampTexture;
	sf::Texture signTexture;
	std::vector<sf::Texture> grassTexture;
	std::vector<sf::Texture> fenceTexture;
	std::vector<sf::Texture> rockTexture;
	sf::View* camera;
	sf::Clock timer;
	sf::Image icon;
		
	// Variáveis da loja
	sf::RectangleShape shopBackground;
	sf::Texture popupTexture;
	sf::Font font;
	sf::Text popUpText;
	sf::RectangleShape shopButton;
	sf::Texture buttonTexture;
	sf::Text buttonText;
	sf::Sprite seller;
	sf::Texture sellerTexture;

	int windowSizeX;
	float switchShopFrameInterval;
	int currentShopFrame;

	bool isOnShop;

	void initTexture();
	void initSprite();
	void initPopUp();
	void initWindow();
	void initPlayer();
	void initVariables();
	void pollEvents();
	void update();
	void updateInput();
	void updateShopTexture();
	void render();
	void renderShopPopUp();

public:

	Game();
	~Game();

	void run();

};

