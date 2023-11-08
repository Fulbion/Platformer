#pragma once

#include "State.hpp"

class Game
{
public:
	Game();
	~Game();

	void updateDeltaTime();
	void handleEvents();
	void update();
	void render();
	void run();

private:
	sf::RenderWindow* m_window;
	sf::Event m_event;

	sf::Clock m_clock;
	float m_deltaTime = 0.0f;

	std::stack<State*> m_states;
};
