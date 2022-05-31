// 2048 game. This file contains main function.
//
/*
Author: Lukáš Salak
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include "..\include\game.h"
#include "..\include\argparse.hpp"
#include "..\include\bots.h"
#include "..\include\comparisons.h"


using namespace std;
    void clear_console() {
#if linux
        system("clear");
#else
        system("CLS");
#endif
    }
    bool show;

    void run_comparison(int repeat, int x, int y) {
        vector<pair<string, function<int(game&)>>> delegates;
        //    connectingTiles = 1,
        //    emptyTiles = 2,
        //    scoreTiles = 4

        delegates.push_back(make_pair(typeid(randomBot).name(), randomBot::getMove));
        delegates.push_back(make_pair(typeid(cornerBot).name(), cornerBot::getMove));

		

        // no depth, counting only for max score
        delegates.push_back(make_pair(typeid(minmaxBot<0, 4, 100>).name(), minmaxBot<0, 4, 100>::getMove));
        // no depth, counting for max score and empty tiles
        delegates.push_back(make_pair(typeid(minmaxBot<0, 6, 110>).name(), minmaxBot<0, 6, 110>::getMove));
        // 1 depth, counting only for max score
        delegates.push_back(make_pair(typeid(minmaxBot<1, 4, 100>).name(), minmaxBot<1, 4, 100>::getMove));
        // 1 depth, counting for max score and empty tiles
        delegates.push_back(make_pair(typeid(minmaxBot<1, 6, 110>).name(), minmaxBot<1, 6, 110>::getMove));
        // 1 depth, counting for max score and empty tiles, different weights
        delegates.push_back(make_pair(typeid(minmaxBot<1, 6, 210>).name(), minmaxBot<1, 6, 210>::getMove));
        // 1 depth, counting for max score and empty tiles, different weights
        delegates.push_back(make_pair(typeid(minmaxBot<1, 7, 211>).name(), minmaxBot<1, 7, 211>::getMove));
        delegates.push_back(make_pair(typeid(minmaxBot<1, 7, 421>).name(), minmaxBot<1, 7, 421>::getMove));
        delegates.push_back(make_pair(typeid(minmaxBot<2, 7, 211>).name(), minmaxBot<2, 7, 211>::getMove));
        delegates.push_back(make_pair(typeid(minmaxBot<2, 7, 421>).name(), minmaxBot<2, 7, 421>::getMove));
		

        delegates.push_back(make_pair(typeid(minmaxBot<3, 7, 211>).name(), minmaxBot<3, 7, 211>::getMove));
        delegates.push_back(make_pair(typeid(minmaxBot<3, 7, 421>).name(), minmaxBot<3, 7, 421>::getMove));
        delegates.push_back(make_pair(typeid(minmaxBot<4, 7, 211>).name(), minmaxBot<4, 7, 211>::getMove));
        delegates.push_back(make_pair(typeid(minmaxBot<4, 7, 421>).name(), minmaxBot<4, 7, 421>::getMove));

        comparer c;
        c.bots = delegates;
        auto results = c.calculate_results(repeat, y, x);
        cout << "Results:" << endl;
        cout << endl;
        for (auto& r : results) {
            // wins
            cout << "Bot " << r.type << " average wins: " << accumulate(r.wins.begin(), r.wins.end(), 0) << endl;
        }
        cout << endl;
        for (auto& r : results) {
            // scores
            cout << "Bot " << r.type << " average scores: " << accumulate(r.scores.begin(), r.scores.end(), 0) / repeat << endl;
        }
        cout << endl;
        for (auto& r : results) {
            // steps
            cout << "Bot " << r.type << " average steps: " << accumulate(r.steps.begin(), r.steps.end(), 0) / repeat << endl;
        }
        cout << endl;
        for (auto& r : results) {
            // times
            cout << "Bot " << r.type << " average time elapsed per simulation: " << accumulate(r.timesElapsed.begin(), r.timesElapsed.end(), 0) / repeat / 1000000.0f << endl;
        }
        cout << endl;
    }

    void run_human(game& g) {

        cout << "Available moves: w s a d" << endl;
        g.restart();
        g.display();
        char c;
        int dir = 0;
        while (cin >> c) {
            if (c == 'd') dir = 0;
            if (c == 'w') dir = 1;
            if (c == 'a') dir = 2;
            if (c == 's') dir = 3;
            g.move(dir);
            clear_console();
            g.display();
        }
    }
    void run_randomBot(game& g) {
        g.restart();
        while (!(g.is_win() || g.is_lose())) {
            int m = randomBot::getMove(g);
            g.move(m);
            if (show) {
                clear_console();
                g.display();
                cout << "Move: " << m << endl;
            }
        }
        if (g.is_win())
            cout << "won" << endl;
        else cout << "lost" << endl;
        g.display();
    }
    void run_cornerBot(game& g) {
        g.restart();
        while (!(g.is_win() || g.is_lose())) {
            int m = cornerBot::getMove(g);
            g.move(m);
            if (show) {
                clear_console();
                g.display();
                cout << "Move: " << m << endl;
            }

        }
        if (g.is_win())
            cout << "won" << endl;
        else cout << "lost" << endl;
        g.display();
    }
    void run_minmaxBot(game& g) {
        g.restart();
        while (!(g.is_win() || g.is_lose())) {
            int m = minmaxBot<5,7,831>::getMove(g);
            g.move(m);
            if (show) {
                clear_console();
                g.display();
                cout << "Move: " << m << endl;
                }

        }
        if (g.is_win())
            cout << "won" << endl;
        else cout << "lost" << endl;
        g.display();
    }

    int main(int argc, char* argv[]) {
        argparse::ArgumentParser parser("2048 game");
        parser.add_argument("").default_value("With no arguments, the game starts with default values");
        parser.add_argument("--sizeX").help("set size of game field X").default_value(4);
        parser.add_argument("--sizeY").help("set size of game field Y").default_value(4);
        parser.add_argument("--max").help("set max tile for win condition").default_value(2048);
        parser.add_argument("--bots").help("set bot, values: human, randomBot, cornerBot, minmaxBot").default_value(std::string{ "human" });
        parser.add_argument("--comparison-repeat").help("how many times comparison will run, only works with --comparison argument");
        parser.add_argument("--show").help("shows all steps when bot is chosen").default_value(false);

        try {
            parser.parse_args(argc, argv);
        }
        catch (const std::runtime_error& err) {
            cerr << err.what() << endl;
            cerr << parser;
            exit(1);
        }
        show = parser.is_used("--show");
        int x = 4;
        int y = 4;
        int max = 2048;
        game g;
        vector<vector<int>> board;
        if (parser.is_used("--sizeY")) {
            y = stoi(parser.get("--sizeY"));
        }
        if (parser.is_used("--sizeX")) {
            x = stoi(parser.get("--sizeX"));
        }
        if (parser.is_used("--max")) {
            max = stoi(parser.get("--max"));
        }
        
        board = vector<vector<int>>(y,vector<int>(x, 0));

        g.set_board(board);
        g.set_max(max);

        if (parser.is_used("--comparison-repeat")) {
            int repeat = 1000;
            auto r = parser.get("--comparison-repeat");
            repeat = stoi(r);
            run_comparison(repeat, x, y);
            return 0;
        }

        auto value = parser.get<std::string>("--bots");
        if (value == "human") {
            
            run_human(g);
        }
        else if (value == "randomBot") {
            run_randomBot(g);
        }
        else if (value == "cornerBot") {
            run_cornerBot(g);
        }
        else if (value == "minmaxBot") {
            run_minmaxBot(g);
        }

        return 0;
    }
