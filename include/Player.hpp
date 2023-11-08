#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
	Player();
	~Player();

	virtual void update(const float& i_deltaTime, Map& i_map) override;
	virtual void render(sf::RenderTarget* i_target) override;

private:
	bool wasJumpKeyPressed = false;
	bool wasOnGround = false;
	bool isOnGround = false;
	sf::Vector2f m_velocity;
};
