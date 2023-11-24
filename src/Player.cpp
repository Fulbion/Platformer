#include "Player.hpp"

Player::Player()
{
	this->m_sprite.setTexture(assets["player"][0]);
	this->m_hitbox.width = this->m_hitbox.height = CELL_SIZE;
}

Player::~Player()
{

}

void Player::update(const float& i_deltaTime, Map& i_map)
{
	this->m_hitbox.left = this->m_position.x;
	this->m_hitbox.top = this->m_position.y;
	
	// Horizontal movement
	this->m_velocity.x = 200 * (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	this->m_hitbox.left += this->m_velocity.x * i_deltaTime;
	
	for (sf::FloatRect tileRect : i_map.physicsTilesAround(sf::Vector2i(this->m_hitbox.left, this->m_hitbox.top)))
	{
		if (this->m_hitbox.intersects(tileRect))
		{
			this->m_velocity.x = 0;

			this->m_position.x = round(this->m_position.x);
			break;
		}
	}

	this->m_position.x += this->m_velocity.x * i_deltaTime;
	this->m_hitbox.left = this->m_position.x;

	// Vertical movement
	this->m_velocity.y = std::min<float>(this->m_velocity.y + 750 * i_deltaTime, 1500);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->wasJumpKeyPressed == false)
			this->m_velocity.y = -300;
		this->wasJumpKeyPressed = true;
	}

	else
	{
		this->wasJumpKeyPressed = false;
	}

	this->m_hitbox.top += this->m_velocity.y * i_deltaTime;
	
	for (sf::FloatRect tileRect : i_map.physicsTilesAround(sf::Vector2i(this->m_hitbox.left, this->m_hitbox.top)))
	{
		if (this->m_hitbox.intersects(tileRect))
		{
			this->m_velocity.y = 0;

			this->m_position.y = round(this->m_position.y);
			break;
		}
	}
	
	this->m_position.y += this->m_velocity.y * i_deltaTime;
}

void Player::render(sf::RenderTarget* i_target)
{
	this->m_sprite.setPosition(this->m_position);
	i_target->draw(this->m_sprite);
}
