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
			else if (this->data->inputMgr.IsSpriteClicked(this->gridSprite, sf::Mouse::Left, this->data->window))
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
				gridPieces[x][y].setPosition(gridSprite.getPosition().x + tempSpriteSize.x * x - 7,
					gridSprite.getPosition().y + tempSpriteSize.y * y - 7);
				gridPieces[x][y].setColor(sf::Color::White);
			}
		}
	}


	void GameState::CheckAndPlacePiece()
	{
		sf::Vector2i touchPoint = this->data->inputMgr.GetMousePosition(this->data->window);
		sf::FloatRect gridSize = gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3 );

		int column = gridLocalTouchPos.x / gridSectionSize.x;
		int row = gridLocalTouchPos.y / gridSectionSize.y;

		if (gridArray[column][row] == EMPTY_PIECE)
		{
			gridArray[column][row] = turn;

			if (PLAYER_PIECE == turn)
			{
				gridPieces[column][row].setTexture(this->data->assetMgr.GetTexture("X Piece"));
				if (CheckWinningCondition(column, row, turn))
				{

				}

				turn = AI_PIECE;
			}
			else if(AI_PIECE == turn)
			{
				gridPieces[column][row].setTexture(this->data->assetMgr.GetTexture("O Piece"));
				if (CheckWinningCondition(column, row, turn))
				{

				}

				turn = PLAYER_PIECE;
			}

			gridPieces[column][row].setColor(sf::Color(255, 255, 255));
		}
	}

	bool GameState::CheckWinningCondition(int column, int row, int turn)
	{
		bool flag = true;
		if (column == row)
			flag = gridArray[0][0] == turn && gridArray[1][1] == turn && gridArray[2][2] == turn;

		if (column == 2 - row || row == 2 - column)
			flag = gridArray[2][0] == turn && gridArray[1][1] == turn && gridArray[0][2] == turn;

		flag = true;
		for (int i = 0; i < 3; ++i)
			flag &= (gridArray[column][i] == turn);
		
		flag = true;
		for (int i = 0; i < 3; ++i)
			flag &= (gridArray[i][row] == turn);

		return flag;
	}
}


