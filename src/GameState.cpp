#include <sstream>
#include <iostream>
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "CoreDefines.h"
#include <SFML/Graphics.hpp>

namespace Blink
{

	void GameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->data->assetMgr.LoadTexture("Pause Button", PAUSE_BUTTON);

		this->data->assetMgr.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->data->assetMgr.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->data->assetMgr.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->data->assetMgr.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->data->assetMgr.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		gridSprite.setTexture(this->data->assetMgr.GetTexture("Grid Sprite"));

		backGround.setTexture(this->data->assetMgr.GetTexture("Background"));
		pauseButton.setTexture(this->data->assetMgr.GetTexture("Pause Button"));


		gridSprite.setPosition(SCREEN_WIDTH / 2 - gridSprite.getGlobalBounds().width / 2,
								SCREEN_HEIGHT / 2 - gridSprite.getGlobalBounds().height / 2);

		pauseButton.setPosition(this->data->window.getSize().x - pauseButton.getLocalBounds().width,
								pauseButton.getPosition().y);



		InitGridPieces();


		std::cout << gridArray[0][0] << '\t' << gridArray[1][0] << '\t' << gridArray[2][0] << '\n'
					<< gridArray[0][1] << '\t' << gridArray[1][1] << '\t' << gridArray[2][1] << '\n'
					<< gridArray[0][2] << '\t' << gridArray[1][2] << '\t' << gridArray[2][2] << '\n' << '\n';

		aiPlayer = AI(gridArray);
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->data->window.close();
			}

			if (this->data->inputMgr.IsSpriteClicked(this->pauseButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.AddState(StateUptr(new PauseState(this->data)), false);
			}
			else if (this->data->inputMgr.IsSpriteClicked(this->gridSprite, sf::Mouse::Left, this->data->window) || turn == AI_PIECE)
			{
				if(gameState == STATE_PLAYING)
					this->CheckAndPlacePiece();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				this->data->machine.AddState(StateUptr(new GameOverState(this->data)), false);
			}
		}
	}

	void GameState::Update(float deltaTime)
	{

	}

	void GameState::Draw(float deltaTime)
	{
		this->data->window.clear(sf::Color::Yellow);

		this->data->window.draw(this->backGround);
		this->data->window.draw(this->pauseButton);
		this->data->window.draw(this->gridSprite);

		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				this->data->window.draw(this->gridPieces[x][y]);
			}
		}

		this->data->window.display();
	}

	void GameState::InitGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->data->assetMgr.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				gridArray[x][y] = EMPTY_PIECE;
				gridPieces[x][y].setPosition(gridSprite.getPosition().x + tempSpriteSize.x * x - 6.5,
					gridSprite.getPosition().y + tempSpriteSize.y * y - 6);
				gridPieces[x][y].setColor(sf::Color::White);
			}
		}

		numEmptyCells = 9;
	}


	void GameState::CheckAndPlacePiece()
	{
		int column, row;
		if (turn == PLAYER_PIECE)
		{
			sf::Vector2i touchPoint = this->data->inputMgr.GetMousePosition(this->data->window);
			sf::FloatRect gridSize = gridSprite.getGlobalBounds();
			sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
			sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
			sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

			column = gridLocalTouchPos.x / gridSectionSize.x;
			row = gridLocalTouchPos.y / gridSectionSize.y;
		}
		else if (turn == AI_PIECE)
		{
			sf::Vector2i cr = aiPlayer.CalculateMove(turn, &gridArray);
			column = cr.x;
			row = cr.y;

			std::cout << "col = " << column << std::endl;
			std::cout << "row = " << row << std::endl;
		}


		if (gridArray[column][row] == EMPTY_PIECE)
		{
			gridArray[column][row] = turn;


			if (PLAYER_PIECE == turn)
			{
				gridPieces[column][row].setTexture(this->data->assetMgr.GetTexture("X Piece"));

				ProceedIfWon(column, row);
				ProceedIfDraw();

				turn = AI_PIECE;

			}
			else if(AI_PIECE == turn)
			{
				gridPieces[column][row].setTexture(this->data->assetMgr.GetTexture("O Piece"));
				
				ProceedIfWon(column, row);
				ProceedIfDraw();

				turn = PLAYER_PIECE;
			}

			//gridPieces[column][row].setColor(sf::Color(255, 255, 255));
		}
	}

	void GameState::ProceedIfWon(int column, int row)
	{
		if (CheckWinningCondition(column, row))
		{
			std::string texName = "- Winning Piece";
			if (turn == PLAYER_PIECE)
			{
				texName[0] = 'X';
				gameState = X_WON;
			}
			else if (turn == AI_PIECE)
			{
				texName[0] = 'O';
				gameState = O_WON;
			}
			for (const auto& blck : winningBlocks)
				gridPieces[blck.x][blck.y].setTexture(this->data->assetMgr.GetTexture(texName));
		}
	}

	void GameState::ProceedIfDraw()
	{
		--numEmptyCells;
		if (numEmptyCells == 0 && gameState == STATE_PLAYING)
		{
			gameState = STATE_DRAW;
		}
	}

	bool GameState::CheckWinningCondition(int column, int row)
	{
		bool flag = false;
		if (column == row)
			flag = gridArray[0][0] == turn && gridArray[1][1] == turn && gridArray[2][2] == turn;

		if (flag)
		{
			winningBlocks[0] = sf::Vector2i(0, 0);
			winningBlocks[1] = sf::Vector2i(1, 1);
			winningBlocks[2] = sf::Vector2i(2, 2);

			return flag;
		}

		if (column == 2 - row || row == 2 - column)
			flag = gridArray[2][0] == turn && gridArray[1][1] == turn && gridArray[0][2] == turn;

		if (flag)
		{
			winningBlocks[0] = sf::Vector2i(2, 0);
			winningBlocks[1] = sf::Vector2i(1, 1);
			winningBlocks[2] = sf::Vector2i(0, 2);

			return flag;
		}

		flag = true;
		for (int i = 0; i < 3; ++i)
			flag &= (gridArray[column][i] == turn);

		if (flag)
		{
			for (int i = 0; i < 3; ++i)
				winningBlocks[i] = sf::Vector2i(column, i);

			return flag;
		}
		
		flag = true;
		for (int i = 0; i < 3; ++i)
			flag &= (gridArray[i][row] == turn);

		if (flag)
		{
			for (int i = 0; i < 3; ++i)
				winningBlocks[i] = sf::Vector2i(i, row);

			return flag;
		}

		return flag;
	}
}


