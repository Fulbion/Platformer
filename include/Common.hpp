#pragma once

#include <iostream>
#include <any>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef unsigned int uint;

/// <summary>
/// This function checks the sign of a number.
/// </summary>
/// <typeparam name="T">Type of the number</typeparam>
/// <param name="i_num">Number to check</param>
/// <returns>1 if the number is positive, -1 if the number is negative</returns>
template<typename T>
inline int8_t sign(T i_num)
{
	return (0 < i_num) - (0 > i_num);
}

inline const char* IMAGE_ROOT_DIR = "resources/images/";

inline sf::Texture loadImage(const char* path)
{
	sf::Texture texture;
	texture.loadFromFile(path);
	return texture;
}

inline std::vector<sf::Texture> loadImages(const char* path)
{
	std::vector<sf::Texture> images;
	std::filesystem::path dir("resources/images/");
	dir /= path;
	for (const auto& entry : std::filesystem::directory_iterator(dir))
	{
		std::string actualPath = entry.path().string();
		actualPath.erase(std::remove(actualPath.begin(), actualPath.end(), '\"'), actualPath.end());
		images.push_back(loadImage(actualPath.c_str()));
	}
	return images;
}

constexpr uint8_t CELL_SIZE = 16;
constexpr float GRAVITY = 2.0f;
constexpr float ACCELERATION = 1.0f;

inline std::unordered_map<std::string, std::vector<sf::Texture>> assets =
{
	{ "player", loadImages("entities/player") },
	{ "grass", loadImages("tiles/grass") },
};
