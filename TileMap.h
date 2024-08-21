#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{

private:	

	//Mapa
	tmx::Map map;

	//Texturas e camadas
	std::map<const std::unique_ptr<sf::Texture>, std::vector<sf::Vertex>> verticesByTexture;
	tmx::Vector2u tileMapSize;
	tmx::Vector2u mapCount;
	std::unordered_map<std::string, sf::Texture> tilesetTextures;
	std::vector<std::pair<std::string, sf::VertexArray>> vertices;
	
	//Objetos
	std::vector<tmx::Object> objects;
	void loadTile(const tmx::Layer::Ptr&, const auto&, const auto&, const auto&, const auto&);
	void loadObject(const tmx::Layer::Ptr&);

public:

	bool loadMap(const std::string&);
	bool load();
	void drawLayer(std::string, sf::RenderTarget&, sf::RenderStates) const;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
	tmx::Vector2u getMapSize() const;
	const std::vector<tmx::Object>& getObjects() const;

};