#include <sstream>
#include <iostream>
#include "MainMenuState.h"
#include "PauseState.h"
#include "CoreDefines.h"
#include <SFML/Graphics.hpp>

namespace Blink
{

	void PauseState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->data->assetMgr.LoadTexture("Resume Button", RESUME_BUTTON);
		this->data->assetMgr.LoadTexture("Home Button", HOME_BUTTON);

		backGround.setTexture(this->data->assetMgr.GetTexture("Background"));
		resumeButton.setTexture(this->data->assetMgr.GetTexture("Resume Button"));
		homeButton.setTexture(this->data->assetMgr.GetTexture("Home Button"));

		resumeButton.setPosition(this->data->window.getSize().x / 2 - resumeButton.getLocalBounds().width / 2,
			this->data->window.getSize().y / 3 - resumeButton.getLocalBounds().height / 2);
		homeButton.setPosition(this->data->window.getSize().x / 2 - homeButton.getLocalBounds().width / 2,
			this->data->window.getSize().y / 1.5f - homeButton.getLocalBounds().height / 2);

	}

	void PauseState::HandleInput()
	{
		sf::Event event;

		while (this->data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->data->window.close();
			}

			if (this->data->inputMgr.IsSpriteClicked(this->resumeButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.RemoveState();
			}

			if (this->data->inputMgr.IsSpriteClicked(this->homeButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.RemoveState();
				this->data->machine.AddState(StateUptr(new MainMenuState(this->data)), true);
			}
		}
	}

	void PauseState::Update(float deltaTime)
	{

	}

	void PauseState::Draw(float deltaTime)
	{
		this->data->window.clear(sf::Color::Yellow);

		this->data->window.draw(this->backGround);
		this->data->window.draw(this->resumeButton);
		this->data->window.draw(this->homeButton);

		this->data->window.display();
	}
}