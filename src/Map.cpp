#include "Map.hpp"

Map::Map()
{
	std::ifstream f("resources/data/map.json");
	m_mapFile = json::parse(f);
}

Map::~Map()
{
}

std::vector<json> Map::tilesAround(sf::Vector2i i_position)
{
	std::vector<json> output;
	sf::Vector2i tileLocation(round(static_cast<float>(i_position.x) / CELL_SIZE), round(static_cast<float>(i_position.y) / CELL_SIZE));

	for (sf::Vector2i offset : this->m_neighborOffsets)
	{
		std::stringstream sstr;
		sstr << std::to_string(tileLocation.x + offset.x) << ';' << std::to_string(tileLocation.y + offset.y);
		std::string checkLocation = sstr.str();

		if (this->m_mapFile.contains(checkLocation))
		{
			output.push_back(this->m_mapFile[checkLocation]);
		}
	}

	return output;
}

std::vector<sf::FloatRect> Map::physicsTilesAround(sf::Vector2i i_position)
{
	std::vector<sf::FloatRect> output;

	for (auto& tile : this->tilesAround(i_position))
	{
		for (const char* type : this->m_physicsTiles)
		{
			if (tile["type"] == type)
			{
				output.push_back(sf::FloatRect(tile["position"][0] * CELL_SIZE, tile["position"][1] * CELL_SIZE, CELL_SIZE, CELL_SIZE));
			}
		}
	}

	return output;
}

void Map::render(sf::RenderTarget* i_target)
{
	sf::FloatRect viewRect
	(
		i_target->getView().getCenter().x - (i_target->getView().getSize().x / 2),
		i_target->getView().getCenter().y - (i_target->getView().getSize().y / 2),
		i_target->getView().getSize().x,
		i_target->getView().getSize().y
	);

	for (auto& tile : m_mapFile)
	{
		if (!(tile["position"][0] >= (viewRect.left - CELL_SIZE) / CELL_SIZE &&
			tile["position"][0] < (viewRect.left + viewRect.width) / CELL_SIZE &&
			tile["position"][1] >= (viewRect.top - CELL_SIZE) / CELL_SIZE &&
			tile["position"][1] < (viewRect.top + viewRect.height) / CELL_SIZE))
			continue;

		sf::Sprite s;
		s.setTexture(assets[tile["type"]][tile["variant"]]);
		s.setPosition(tile["position"][0] * CELL_SIZE, tile["position"][1] * CELL_SIZE);
		i_target->draw(s);
	}
}