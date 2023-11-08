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
	this->m_velocity.x = (0.2f + isOnGround * 0.1) * i_deltaTime * (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	this->m_hitbox.left += this->m_velocity.x;

	bool canMove = true;

	for (sf::FloatRect tileRect : i_map.physicsTilesAround(sf::Vector2i(this->m_hitbox.left, this->m_hitbox.top)))
	{
		if (this->m_hitbox.intersects(tileRect))
		{
			canMove = false;

			m_position.x = round(m_position.x);
			break;
		}
	}

	if (canMove)
		this->m_position.x += this->m_velocity.x;

	// // Vertical movement
	this->m_velocity.y = std::min<float>(this->m_velocity.y + 0.01 * i_deltaTime, 1.81 * i_deltaTime);
	this->m_hitbox.top += round(this->m_velocity.y);
	
	canMove = true;
	
	for (sf::FloatRect tileRect : i_map.physicsTilesAround(sf::Vector2i(this->m_hitbox.left, this->m_hitbox.top)))
	{
		isOnGround = false;
		wasOnGround = false;

		if (this->m_hitbox.intersects(tileRect))
		{
			// this->m_velocity.y = 0;

			if (this->m_velocity.y > 0)
				isOnGround = true;

			canMove = false;
			if (m_position.y != round(m_position.y))
				m_position.y = round(m_position.y);
			break;
		}
	}
	
	if (canMove)
		this->m_position.y += this->m_velocity.y;


	if (!wasOnGround && isOnGround)
	{
		this->m_velocity.y = 0;
		wasOnGround = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->wasJumpKeyPressed == false)
			this->m_velocity.y = -0.4 * i_deltaTime;
		this->wasJumpKeyPressed = true;
	}

	else
	{
		this->wasJumpKeyPressed = false;
	}
}

void Player::render(sf::RenderTarget* i_target)
{
	this->m_sprite.setPosition(this->m_position);
	i_target->draw(this->m_sprite);
}
