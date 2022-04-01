#include <iostream>
#include "AI.h"
#include "CoreDefines.h"

namespace Blink
{
	void AI::PlacePiece()
	{
	}

	sf::Vector2i AI::CalculateMove(int turn, int(*ga)[3][3])
	{
		gridArray = ga;
		sf::Vector2i bestMove = sf::Vector2i(0, 0);
		
		int bestScore = std::numeric_limits<int>::min();

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if ((*gridArray)[i][j] != EMPTY_PIECE) continue;

				int score = Minimax();

				if (score > bestScore)
				{
					bestScore = score;
					bestMove.x = i;
					bestMove.y = j;
				}
			}
		}


		return bestMove;
	}

	int AI::Minimax()
	{
		return 1;
	}
}
