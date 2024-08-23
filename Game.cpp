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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		player->move(Direction::Right);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		player->move(Direction::Left);

}

void Game::update()
{
}

void Game::render()
{
	window.clear();
	player->render(window);
	window.setView(camera);
	tilemap.draw(window, sf::RenderStates::Default);
	window.display();
}

Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "ProjectY", sf::Style::Fullscreen), zoomViewFactor(0.75f)
{
	window.setVerticalSyncEnabled(true);

	if (!tilemap.loadMap("./assets/maps/Mapa.tmx")) {
		std::cerr << "ERROR::GAME::LOADMAP\n";
		exit(EXIT_FAILURE);
	}

	if (!tilemap.load()) {
		std::cerr << "ERROR::GAME::LOADTILEMAP\n";
		exit(EXIT_FAILURE);
	}

	camera = sf::View(sf::FloatRect(0, 0, tilemap.getMapSize().x>window.getSize().x ? window.getSize().x : tilemap.getMapSize().y, tilemap.getMapSize().y>window.getSize().y ? window.getSize().y : tilemap.getMapSize().y));
	camera.zoom(zoomViewFactor);
	camera.setCenter(window.getSize().x / (2 / zoomViewFactor), tilemap.getMapSize().y - window.getSize().y / (2 / zoomViewFactor));
	
	player = std::make_unique<Player>(sf::Vector2f(0, tilemap.getMapSize().y - window.getSize().y / (2 / zoomViewFactor)));

}

Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen()) {
		pollEvents();
		handleInput();
		update();
		render();
	}
}
