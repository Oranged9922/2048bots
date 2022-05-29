#pragma once
/*
    2048 game.This file is header for class bots.
    Author: Lukáš Salak
*/
#include "..\include\game.h"
#include <stdlib.h>
#include <time.h>

using namespace std;


class bot {
    public:
        /// <summary>
        /// 0 - right, 1 - up, 2 - left, 3 - down
        /// </summary>
        /// <param name="g">game to make next move in</param>
        /// <returns>int that represents direction</returns>
        static int getMove(game& g);
};

// completely random bot, returns random move
#pragma region randomBot
class randomBot: public bot {
	public:
		static int getMove(game& g);
};
int randomBot::getMove(game& g) {
	return rand() % 4;
}
#pragma endregion

// bot that tries to push tiles into one corner
class cornerBot: public bot {
	public:
		static int getMove(game& g);
};
int cornerBot::getMove(game& g) {
    if (g.can_shift(0) && g.can_shift(1))
        //right or up
        return rand() % 2 ? 0 : 1;
    else if (g.can_shift(0)) return 0;
    else if (g.can_shift(1)) return 1;
    else if (g.can_shift(2)) return 2;
    else return 3;
	
}

enum minmaxEnum {
	// number of tiles that would get merged in one move
	connectingTiles = 1,
	// number of empty tiles after the move
	emptyTiles = 2,
	// score of the move
	scoreTiles = 4
};

#pragma region minmaxBot
/// <summary>
/// first template parameter is depth of the search tree
/// second template parameter is enums
/// third parameter is weights of the enums
/// </summary>
template <int A, int B, int C>
class minmaxBot: public bot {
private:
	static int minmax(game& g, int depth);
public:
	static int getMove(game& g);
};

template<int _depth, int _minmaxEnums, int _enumsWeights>
inline int minmaxBot<_depth, _minmaxEnums, _enumsWeights>::minmax(game& g, int depth)
{

	
	if (g.is_lose() || g.is_win()) {
		if (g.is_lose() == 1) return INT_MIN+1;
		else if (g.is_win() == 1) return INT_MAX;
	}
	if (depth == 0) return g.get_score();
	int bestScore = INT_MIN;
	for (int i = 0; i < 4; i++) {
		if (g.can_shift(i)) {
			game g2 = g;
			g2.move(i);
			int newScore = minmax(g2, depth - 1);
			int score = newScore * (_minmaxEnums & 4 == 4) * (_enumsWeights / 100)
				+ newScore * (_minmaxEnums & 2 == 2) * ((_enumsWeights % 100) / 10)* g2.free_spaces()
				+ newScore * (_minmaxEnums & 1 == 1) * (((_enumsWeights%100)%10)) * (g2.free_spaces() - g.free_spaces());
			if (score > bestScore) bestScore = score;

		}
	}
	return bestScore;
}

template<int A, int B, int C>
inline int minmaxBot<A, B, C>::getMove(game& g) {
	int bestScore = INT_MIN;
	int bestMove = -1;
	for (int i = 0; i < 4; i++) {
		if (g.can_shift(i)) {
			game g2 = g;
			g2.move(i);
			int score = minmax(g2, A);
			if (score > bestScore) {
				bestScore = score;
				bestMove = i;
			}
		}
	}
	return bestMove;
}
#pragma endregion