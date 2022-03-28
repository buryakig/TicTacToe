#include <sstream>
#include <iostream>
#include "MainMenuState.h"
#include "GameOverState.h"
#include "CoreDefines.h"
#include <SFML/Graphics.hpp>

namespace Blink
{

	void GameOverState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->data->assetMgr.LoadTexture("Retry Button", RETRY_BUTTON);
		this->data->assetMgr.LoadTexture("Home Button", HOME_BUTTON);

		retryButton.setTexture(this->data->assetMgr.GetTexture("Retry Button"));
		homeButton.setTexture(this->data->assetMgr.GetTexture("Home Button"));

		retryButton.setPosition(this->data->window.getSize().x / 2 - retryButton.getLocalBounds().width / 2,
			this->data->window.getSize().y / 3 - retryButton.getLocalBounds().height / 2);
		homeButton.setPosition(this->data->window.getSize().x / 2 - homeButton.getLocalBounds().width / 2,
			this->data->window.getSize().y / 1.5 - retryButton.getLocalBounds().height / 2);

	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->data->window.close();
			}

			if (this->data->inputMgr.IsSpriteClicked(this->homeButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.AddState(StateUptr(new MainMenuState(this->data)), true);
			}

			if (this->data->inputMgr.IsSpriteClicked(this->homeButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.AddState(StateUptr(new MainMenuState(this->data)), true);
			}
		}
	}

	void GameOverState::Update(float deltaTime)
	{

	}

	void GameOverState::Draw(float deltaTime)
	{
		this->data->window.clear(sf::Color::Red);

		this->data->window.draw(this->retryButton);
		this->data->window.draw(this->homeButton);

		this->data->window.display();
	}
}