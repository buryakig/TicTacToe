#include <sstream>
#include <iostream>
#include "MainMenuState.h"
#include "GameState.h"
#include "CoreDefines.h"
#include <SFML/Graphics.hpp>

namespace Blink
{

	void MainMenuState::Init()
	{
		this->data->assetMgr.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->data->assetMgr.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		this->data->assetMgr.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->data->assetMgr.LoadTexture("Main Menu Title", MAIN_MENU_TITLE_PATH);

		this->backGround.setTexture(this->data->assetMgr.GetTexture("Background"));
		this->playButton.setTexture(this->data->assetMgr.GetTexture("Play Button"));
		this->playButtonOuter.setTexture(this->data->assetMgr.GetTexture("Play Button Outer"));
		this->title.setTexture(this->data->assetMgr.GetTexture("Main Menu Title"));

		this->playButton.setPosition(SCREEN_WIDTH / 2 - this->playButton.getGlobalBounds().width/2, 
									SCREEN_HEIGHT / 2); 

		this->playButtonOuter.setPosition(SCREEN_WIDTH / 2 - this->playButtonOuter.getGlobalBounds().width/2,
									SCREEN_HEIGHT / 2 + this->playButton.getGlobalBounds().height / 2 - 
									this->playButtonOuter.getGlobalBounds().height / 2);
	
		this->title.setPosition(SCREEN_WIDTH / 2 - this->title.getGlobalBounds().width / 2,
								this->title.getGlobalBounds().height * 0.1f);
	
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->data->window.pollEvent(event))
		{ 
			if (sf::Event::Closed == event.type)
			{
				this->data->window.close();
			}

			if (this->data->inputMgr.IsSpriteClicked(this->playButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.AddState(StateUptr(new GameState(this->data)), true);
			}
		}
	}

	void MainMenuState::Update(float deltaTime)
	{

	}

	void MainMenuState::Draw(float deltaTime)
	{
		this->data->window.clear(sf::Color::Yellow);

		this->data->window.draw(this->backGround);
		this->data->window.draw(this->playButton);
		this->data->window.draw(this->playButtonOuter);
		this->data->window.draw(this->title);

		this->data->window.display();
	}
}