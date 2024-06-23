#include "TileMap.h"

void TileMap::loadTiles()
{
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = m_tilesetTexture;
}

bool TileMap::load(const std::string&, const std::string&)
{
	return false;
}

TileMap::TileMap()
{

}
