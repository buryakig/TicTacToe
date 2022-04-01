#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <array>
#include "Game.h"

namespace Blink
{
	class AI
	{
	public:
		AI() {}
		AI (int(&ga)[3][3])
		{
			gridArray = &ga;

			std::cout	<< (*gridArray)[0][0] << '\t' << (*gridArray)[1][0] << '\t' << (*gridArray)[2][0] << '\n'
						<< (*gridArray)[0][1] << '\t' << (*gridArray)[1][1] << '\t' << (*gridArray)[2][1] << '\n'
						<< (*gridArray)[0][2] << '\t' << (*gridArray)[1][2] << '\t' << (*gridArray)[2][2] << '\n' << '\n';
		}

		~AI () {}

		void PlacePiece();
		sf::Vector2i CalculateMove(int turn, int(*ga)[3][3]);
	private:
		int Minimax();

		int (*gridArray)[3][3];
		std::array<std::array<int, 3>, 3> gridSTL;
	};
}