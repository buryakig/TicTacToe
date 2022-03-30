#pragma once

#include "Game.h"

namespace Blink
{
	class GameState : public State
	{
	public:

		GameState(GameDataSptr d) : data(d) {}
		~GameState() {}

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		void InitGridPieces();
		void CheckAndPlacePiece();
		bool CheckWinningCondition(int column, int row, int turn);

		GameDataSptr data;

		sf::Sprite  backGround;
		
		sf::Sprite  pauseButton;
		sf::Sprite  gridSprite;
		
		sf::Sprite  gridPieces[3][3];
		int gridArray[3][3];

		int turn;
		int gameState;
	};
}