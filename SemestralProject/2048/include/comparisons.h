#pragma once
/*
    2048 game.This file is header for comparison of bots.
    Author: Lukáš Salak
*/

#include <vector>
#include <functional>
#include "..\include\game.h"
#include "..\include\bots.h"
using namespace std;

class result {
public:
	string type;
    vector<int> moves;
    vector<int> scores;
    vector<int> steps;
    vector<bool> wins;
	vector<long> timesElapsed;
    result()
    {
    }
};

class comparer {
public:
	vector<pair<string,function<int(game&)>>> bots;
    comparer(){}
	
    vector<result> calculate_results(int repeats, int x, int y);
	
};

inline vector<result> comparer::calculate_results(int repeats, int x, int y)
{
	vector<result> results;
	for (auto& func : bots)
	{
		result r;
		r.type = func.first;
		cout << "Simulating " << r.type << " " << repeats << " times " << endl;

		std::chrono::steady_clock::time_point tbegin = std::chrono::steady_clock::now();
		for (int i = 0; i < repeats; i++)
		{
			game g;
			g.set_board(vector<vector<int>>(x, vector<int>(y, 0)));
			g.restart();
			bool win = false;
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			while (!g.is_win() && !g.is_lose())
			{
				int move = func.second(g);
				g.move(move);
				r.moves.push_back(move);
			}
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			
			r.scores.push_back(g.get_score());
			r.steps.push_back(g.get_step());
			r.wins.push_back(g.is_win() ? 1 : 0);
			r.timesElapsed.push_back(chrono::duration_cast<chrono::microseconds>(end - begin).count());
			if((i*100 * (repeats*100/100)) % 100 == 0)
				cout << ".";
		}
		std::chrono::steady_clock::time_point tend = std::chrono::steady_clock::now();
		
		cout << endl << "Simulation finished in " << chrono::duration_cast<chrono::milliseconds>(tend - tbegin).count()/1000.0f << " seconds" << endl << endl;
		results.push_back(r);
	}
	return results;
}