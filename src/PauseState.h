#pragma once
#include "State.h"
#include "Game.h"

namespace Blink
{
	class PauseState : public State
	{
	public:

		PauseState(GameDataSptr d) : data(d) {}
		~PauseState() {}

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataSptr data; 

		sf::Sprite  backGround;
		sf::Sprite  resumeButton;
		sf::Sprite  homeButton;

		int turn;
		int gameState;
	};
}