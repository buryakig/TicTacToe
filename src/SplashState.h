#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"


namespace Blink
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataSptr d);
		~SplashState();

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataSptr data;
		
		sf::Clock clock;

		sf::Sprite  backGround;
	};
}