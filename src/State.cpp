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
	this->m_player.update(i_deltaTime, m_map);
}

void GameState::update(const float& i_deltaTime)
{
	this->listenKeyboard(i_deltaTime);
}

void GameState::render(sf::RenderTarget* i_target)
{
	// Draw the map
	this->m_map.render(i_target);
	// Draw the player
	this->m_player.render(i_target);
}
