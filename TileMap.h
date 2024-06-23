#pragma once

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{

private:

	sf::VertexArray m_vertices;
	sf::Texture m_tilesetTexture;
	tmx::Map& m_map;

	void loadTiles();



public:

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

	bool load(const std::string&, const std::string&);

	TileMap();

};

