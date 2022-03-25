#include <algorithm>    // std::max

#include "Game.h"
#include "SplashState.h"

namespace Blink
{
	Blink::Game::Game(int width, int height, std::string title)
	{
		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	}

	void Game::Prepare()
	{
		data->machine.AddState(StateUptr(new SplashState(this->data)));
	}

	void Blink::Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->data->window.isOpen())
		{
			this->data->machine.ProcessStateChanges();
			newTime = this->clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			//frameTime = std::min(frameTime, 0.25f);
			currentTime = newTime;
			accumulator += frameTime;

			if (accumulator >= deltaTime)
			{
				this->data->machine.GetActiveState()->HandleInput();
				this->data->machine.GetActiveState()->Update(deltaTime);

				accumulator -= deltaTime;
			}

			interpolation = accumulator / deltaTime;
			this->data->machine.GetActiveState()->Draw(deltaTime);
		}
	}
}
