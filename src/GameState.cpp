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

		gridSprite.setTexture(this->data->assetMgr.GetTexture("Grid Sprite"));

		backGround.setTexture(this->data->assetMgr.GetTexture("Background"));
		pauseButton.setTexture(this->data->assetMgr.GetTexture("Pause Button"));


		gridSprite.setPosition(SCREEN_WIDTH / 2 - gridSprite.getGlobalBounds().width / 2,
								SCREEN_HEIGHT / 2 - gridSprite.getGlobalBounds().height / 2);

		pauseButton.setPosition(this->data->window.getSize().x - pauseButton.getLocalBounds().width,
								pauseButton.getPosition().y);



		InitGridPieces();

		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
			}
		}

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
				gridPieces[x][y].setTexture(this->data->assetMgr.GetTexture("X Piece"));
				gridPieces[x][y].setPosition(gridSprite.getPosition().x + tempSpriteSize.x * x - 7,
					gridSprite.getPosition().y + tempSpriteSize.y * y - 7);
				gridPieces[x][y].setColor(sf::Color::White);
			}
		}
	}
}

