#pragma once

#include "Common.hpp"

struct Position
{
	int x, y;
};

class Map
{
public:
	Map();
	~Map();

	std::vector<json> tilesAround(sf::Vector2i i_position);
	std::vector<sf::FloatRect> physicsTilesAround(sf::Vector2i i_position);

	void render(sf::RenderTarget* i_target);

private:
	json m_mapFile;

	const std::array<const char*, 2> m_physicsTiles =
	{
		"grass",
		"stone"
	};

	const std::array<sf::Vector2i, 9> m_neighborOffsets =
	{
		sf::Vector2i(-1,  0),
		sf::Vector2i(-1, -1),
		sf::Vector2i( 0, -1),
		sf::Vector2i( 1, -1),
		sf::Vector2i( 1,  0),
		sf::Vector2i( 0,  0),
		sf::Vector2i(-1,  1),
		sf::Vector2i( 0,  1),
		sf::Vector2i( 1,  1),
	};
};
