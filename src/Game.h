#pragma once
#include <memory>
#include <string>
#include "SFML/Graphics.hpp"
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace Blink
{
	struct GameData
	{
		sf::RenderWindow window;
		StateMachine machine;
		AssetManager assetMgr;
		InputManager inputMgr;
	};

	typedef std::shared_ptr<GameData> GameDataSptr;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

		void Prepare();
		void Run();

	private:
		const float deltaTime = 1.0f / 60.0f;
		sf::Clock clock;

		GameDataSptr data = std::make_shared<GameData>();

	};
}