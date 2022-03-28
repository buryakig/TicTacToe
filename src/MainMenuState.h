#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"

namespace Blink
{
	class MainMenuState : public State
	{
	public:

		MainMenuState(GameDataSptr d) : data(d) {}
		~MainMenuState() {}

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataSptr data;

		sf::Sprite  backGround;
		sf::Sprite  title;
		sf::Sprite  playButton;
		sf::Sprite  playButtonOuter;
	};
}