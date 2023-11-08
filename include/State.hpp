#pragma once

#include "Common.hpp"
#include "Player.hpp"
#include "Map.hpp"

class State
{
public:
	State(sf::RenderWindow* i_window);
	virtual ~State();

	virtual void checkForQuit();
	const bool& getQuit() const;

	virtual void listenKeyboard(const float& i_deltaTime) = 0;
	virtual void update(const float& i_deltaTime) = 0;
	virtual void render(sf::RenderTarget* i_target = nullptr) = 0;

protected:
	sf::RenderWindow* m_window;
	std::vector<sf::Texture> m_textures;
	bool quit = false;
};


class GameState : public State
{
public:
	GameState(sf::RenderWindow* i_window);
	~GameState();

	void listenKeyboard(const float& i_deltaTime) override;
	void update(const float& i_deltaTime) override;
	void render(sf::RenderTarget* i_target = nullptr) override;

private:
	Player m_player;
	Map m_map;
};
