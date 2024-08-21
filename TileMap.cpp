#include "TileMap.h"

void TileMap::loadTile(const tmx::Layer::Ptr& layer, const auto& tilesets, const auto& tileSize, const auto& tileCountX, const auto& tileCountY)
{
	const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
	const auto& imageWidth = tilesetTextures.at(layer->getName()).getSize().x / tileSize.x;

	for (unsigned y = 0; y < tileCountY; ++y) {
		for (unsigned x = 0; x < tileCountX; ++x) {
			
			const tmx::TileLayer::Tile& tile = tileLayer.getTiles()[y * tileCountX + x];
			
			if (tile.ID != 0) {
				
				const tmx::Tileset* tileset = nullptr;

				for (const auto& ts : tilesets) {
					if (tile.ID >= ts.getFirstGID() && tile.ID < ts.getFirstGID() + ts.getTileCount()) {
						tileset = &ts;
						break;
					}
				}

				if (!tileset)	continue;

				auto tileID = tile.ID - tileset->getFirstGID();
				auto tileWidth = tileset->getTileSize().x;
				auto tileHeight = tileset->getTileSize().y;

				auto tu = tileID % imageWidth;
				auto tv = tileID / imageWidth;

				sf::VertexArray quad(sf::Quads, 4);

				quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
				quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
				quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
				
				quad[0].texCoords = sf::Vector2f(tu * tileWidth, tv * tileHeight);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileWidth, tv * tileHeight);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileWidth, (tv + 1) * tileHeight);
				quad[3].texCoords = sf::Vector2f(tu * tileWidth, (tv + 1) * tileHeight);

				vertices.push_back(std::make_pair(layer->getName(), quad));

			}

		}
	}
}

void TileMap::loadObject(const tmx::Layer::Ptr& layer)
{
	const tmx::ObjectGroup& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();

	for (const auto& object : objectLayer.getObjects()) {
		objects.push_back(object);
	}

}


bool TileMap::loadMap(const std::string& filePath)
{
	return map.load(filePath);
}

bool TileMap::load()
{
	const auto& layers = map.getLayers();
	const auto& tilesets = map.getTilesets();

	if (tilesets.empty()) {
		std::cerr << "No tilesets found in the map" << std::endl;
		return false;
	}

	std::unordered_map<std::string, std::string> layerToTileset;

	for (auto& ts : tilesets) {
		std::cout << ts.getName() << std::endl;
		layerToTileset[ts.getName()] = ts.getImagePath();
	}


	for (auto& layer : layers) {
		
		if (!tilesetTextures[layer->getName()].loadFromFile(layerToTileset[layer->getName()])) {
			std::cerr << "Failed to load tileset texture: " << tilesets.front().getImagePath() << std::endl;
			return false;
		}
	}

	const auto& tileSize = map.getTileSize();
	const auto& tileCountX = map.getTileCount().x;
	const auto& tileCountY = map.getTileCount().y;

	const auto& imageWidth = tilesetTextures.begin()->second.getSize().x / tileSize.x;

	for (auto& layer : layers) {
		switch (layer->getType()) {
			case tmx::Layer::Type::Tile:
				loadTile(layer, tilesets, tileSize, tileCountX, tileCountY);
				break;
			case::tmx::Layer::Type::Object:
				loadObject(layer);
				break;
			default:
				std::cerr << "ERROR::TILEMAP::LOAD::Erro ao carregar camadas, tipo de conjunto não definido.\n";
				return false;
		}
	}

	tileMapSize = map.getTileSize();
	mapCount = map.getTileCount();

	return true;

}

void TileMap::drawLayer(std::string layerName, sf::RenderTarget& target, sf::RenderStates states) const
{
	const sf::Texture& texture = tilesetTextures.at(layerName);
	states.texture = &texture;

	for (const auto& pair : vertices)
		if (pair.first == layerName) target.draw(pair.second, states);

}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& layer : map.getLayers())
		drawLayer(layer->getName(), target, states);
}

tmx::Vector2u TileMap::getMapSize() const
{
	return tmx::Vector2u(tileMapSize.x*mapCount.x, tileMapSize.y*mapCount.y);
}

const std::vector<tmx::Object>& TileMap::getObjects() const
{
	return objects;
}