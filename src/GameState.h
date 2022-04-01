#pragma once

#include "Game.h"
#include "AI.h"

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
		void ProceedIfWon(int column, int row);
		void ProceedIfDraw();
		bool CheckWinningCondition(int column, int row);

		AI aiPlayer;

		GameDataSptr data;

		sf::Sprite  backGround;
		
		sf::Sprite  pauseButton;
		sf::Sprite  gridSprite;
		
		sf::Sprite  gridPieces[3][3];
		
		sf::Vector2i winningBlocks[3];

		int gridArray[3][3];

		int turn;
		int gameState;
		int numEmptyCells;
	};
}