#pragma once
#include "State.h"
#include "Game.h"

namespace Blink
{

	class GameOverState : public State
	{
	public:

		GameOverState(GameDataSptr d) : data(d) {}
		~GameOverState() {}

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataSptr data; 


		sf::Sprite  retryButton;
		sf::Sprite  homeButton;

		int turn;
		int gameState;
	};
}