#include "State.hpp"

State::State(sf::RenderWindow* i_window) :
	m_window(i_window)
{
}

State::~State()
{
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

const bool& State::getQuit() const
{
	return this->quit;
}

GameState::GameState(sf::RenderWindow* i_window) :
	State(i_window)
{

}

GameState::~GameState()
{
}

void GameState::listenKeyboard(const float& i_deltaTime)
{
	this->checkForQuit();
}

void GameState::update(const float& i_deltaTime)
{
	this->listenKeyboard(i_deltaTime);
	this->m_player.update(i_deltaTime, m_map);
	
	this->m_viewTarget.x = this->m_player.getPosition().x + (this->m_player.getSize().x / 2);
	this->m_viewTarget.y = this->m_player.getPosition().y + (this->m_player.getSize().y / 2);

	this->updateView(CameraMovement::Lerp, i_deltaTime);

	this->m_window->setView(m_view);
}

void GameState::render(sf::RenderTarget* i_target)
{
	// Draw the map
	this->m_map.render(i_target);
	// Draw the player
	this->m_player.render(i_target);
}
