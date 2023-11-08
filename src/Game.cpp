#include "Game.hpp"

Game::Game()
{
	std::ifstream ifs("resources/config/window.ini");

	std::string title = "Platformer";
	sf::VideoMode windowBounds(1280, 720);
	uint16_t framerateLimit = 60;
	bool vSync = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> framerateLimit;
		ifs >> vSync;
	}

	ifs.close();

	this->m_window = new sf::RenderWindow(windowBounds, title);
	this->m_window->setFramerateLimit(framerateLimit);
	this->m_window->setVerticalSyncEnabled(vSync);
	
	this->m_states.push(new GameState(this->m_window));
}

Game::~Game()
{
	delete this->m_window;

	while (!this->m_states.empty())
	{
		delete this->m_states.top();
		this->m_states.pop();
	}
}

void Game::updateDeltaTime()
{
	m_deltaTime = m_clock.restart().asMilliseconds();
}

void Game::handleEvents()
{
	while (this->m_window->pollEvent(this->m_event))
	{
		switch (this->m_event.type)
		{
		case sf::Event::Closed:
			this->m_window->close();
			break;

		default:
			break;
		}
	}
}

void Game::update()
{
	if (!this->m_states.empty())
	{
		this->m_states.top()->update(this->m_deltaTime);
		
		if (this->m_states.top()->getQuit())
		{
			delete this->m_states.top();
			this->m_states.pop();
		}
	}

	else
	{
		this->m_window->close();
	}
}

void Game::render()
{
	this->m_window->clear();

	if (!this->m_states.empty())
		this->m_states.top()->render(this->m_window);

	this->m_window->display();
}

void Game::run()
{
	while (this->m_window->isOpen())
	{
		this->handleEvents();
		this->updateDeltaTime();

		if (this->m_window->hasFocus())
		{
			this->update();
			this->render();
		}
	}
}
