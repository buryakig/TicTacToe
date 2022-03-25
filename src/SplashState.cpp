#include <sstream>
#include <iostream>
#include "SplashState.h"
#include "CoreDefines.h"
#include <SFML/Graphics.hpp>

namespace Blink
{

	SplashState::SplashState(GameDataSptr d) : data(d)
	{
	}

	void SplashState::Init()
	{
		this->data->assetMgr.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		backGround.setTexture(this->data->assetMgr.GetTexture("Splash State Background"));
		backGround.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->data->window.close();
			}
		}
	}

	void SplashState::Update(float deltaTime)
	{
		if (this->clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// Switch to next state
			std::cout << "Go to main menu" << std::endl;
		}
	}

	void SplashState::Draw(float deltaTime)
	{
		this->data->window.clear(sf::Color::Yellow);
		this->data->window.draw(this->backGround);
		this->data->window.display();
	}
}