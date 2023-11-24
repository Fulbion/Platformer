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

	inline void updateView(const CameraMovement& i_cameraMovement, float i_deltaTime)
	{
		this->m_view.setSize(this->m_window->getSize().x, this->m_window->getSize().y);

		float camX = this->m_view.getCenter().x;
		float camY = this->m_view.getCenter().y;

		switch (i_cameraMovement)
		{
		case CameraMovement::Instant:
		{
			camX = this->m_viewTarget.x;
			camY = this->m_viewTarget.y;
			break;
		}

		case CameraMovement::Follow:
		{
			float deltaX = this->m_viewTarget.x - camX;
			float deltaY = this->m_viewTarget.y - camY;

			camX += sign(deltaX) * std::min<float>(100 * i_deltaTime, abs(deltaX));
			camY += sign(deltaY) * std::min<float>(100 * i_deltaTime, abs(deltaY));

			break;
		}

		case CameraMovement::Lerp:
		{
			camX = std::lerp(camX, this->m_viewTarget.x, 7.5 * i_deltaTime);
			camY = std::lerp(camY, this->m_viewTarget.y, 7.5 * i_deltaTime);
			break;
		}

		default:
			break;
		}

		this->m_view.setCenter(camX, camY);
	}

protected:
	sf::RenderWindow* m_window;
	sf::View m_view;
	sf::Vector2f m_viewTarget;
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
