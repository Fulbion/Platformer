#pragma once

#include <SFML/Graphics.hpp>

#include "Common.hpp"
#include "Map.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	inline sf::Vector2f getPosition() const { return this->m_position; }
	inline sf::Vector2f getSize() const { return this->m_hitbox.getSize(); }
	inline sf::FloatRect getRect() const { return this->m_hitbox; }

	inline void setPosition(float i_x, float i_y) { m_position.x = i_x; m_position.y = i_y; }
	inline void setSize(float i_width, float i_height) { m_hitbox.width = i_width; m_hitbox.height = i_height; }

	virtual void update(const float& i_deltaTime, Map& i_map) = 0;
	virtual void render(sf::RenderTarget* i_target) = 0;

protected:
	sf::Vector2f m_position;
	sf::FloatRect m_hitbox;
	sf::Sprite m_sprite;
};
