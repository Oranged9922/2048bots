#pragma once
/* 
    2048 game.This file is header for class game.
    Author: Lukáš Salak
*/
#include <chrono>
#include <vector>
using namespace std;

class game {
private:

    const string dash = "------";
    int sizeY = 4; // default
    int sizeX = 4; // default
    int MAX = 2048; // default
    int score = 0;
    int step = 0;
	int result_can_shift_right = -1;
	int result_can_shift_left = -1;
	int result_can_shift_up = -1;
	int result_can_shift_down = -1;
	int result_is_win = -1;
	int result_is_lose = -1;
	int result_is_free_space = -1;
	// determines how often 4 would spawn over 2
	float two_vs_four_spawn = 0.05f;
    bool can_shift_right();
	bool can_shift_left();
	bool can_shift_up();
	bool can_shift_down();
	void shift_right();
	void shift_left();
	void shift_up();
	void shift_down();
	void reset_results();
public:
	vector<vector<int>> board;
    game();
    game(int max);
    game(int x, int y);
    game(int x, int y, int max);
	
	tuple<int, int> get_board_size();
	void set_board(vector<vector<int>> board);
	void restart();
	/// <summary>
	/// places randomly new tile
	/// </summary>
	/// <returns>x,y coordinates and value, returns {-1,-1,-1} if board is full, doesn't place anything</returns>
	tuple<int,int,int> place_new_tile();
	bool is_free_space();
	bool is_win();
	bool is_lose();
	int free_spaces();
    int get_step();
    int get_score();
	int get_max();
	void set_max(int m);
    int get_tile(int x, int y);
    /// <summary>
    /// </summary>
    /// <param name="dir">0 - right, 1 - up, 2 - left, 3 - down</param>
    /// <returns>true if can shift in that direction, false otherwise</returns>
    bool can_shift(int dir);
	bool move(int dir);
	void shift(int dir);
	void display();
};

inline game::game() {
    board.resize(sizeX, vector<int>(sizeY, 0));
}
inline game::game(int max) {
	board.resize(sizeX, vector<int>(sizeY, 0));
	MAX = max;
}
inline game::game(int x, int y) {
    sizeY = x;
    sizeX = y;
    board.resize(sizeX, vector<int>(sizeY, 0));
}
inline game::game(int x, int y, int max) {
	sizeY = x;
	sizeX = y;
	board.resize(sizeX, vector<int>(sizeY, 0));
	MAX = max;
}

inline void game::restart() {
	srand(std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch())
		.count());
	this->board.clear(); 
	this->board.resize(sizeX, vector<int>(sizeY, 0));
	score = 0;
	step = 0;
	this->place_new_tile();
	this->place_new_tile();
	reset_results();
}

inline tuple<int,int> game::get_board_size() {
	return make_tuple(sizeY, sizeX);
}

inline void game::set_board(vector<vector<int>> board) {
	this->board = board;
	this->sizeY = board[0].size();
	this->sizeX = board.size();
}

inline int game::get_step() {
	return step;
}
inline int game::get_score() {
    return score;
}
inline int game::get_max() {
	return MAX;
}
inline void game::set_max(int m) {
	this->MAX = m;
}
inline int game::get_tile(int x, int y) {
	return board[x][y];
}
inline bool game::can_shift(int dir) {
    switch (dir) {
		case 0:
            return can_shift_right();
        case 1:
		    return can_shift_up();
	    case 2:
		    return can_shift_left();
		case 3:
		    return can_shift_down();
		default:
			return false;
    }
}

inline bool game::can_shift_right() {
	for (int i = 0; i < sizeX; i++) {
		int index = sizeY - 1;
		for (int j = sizeY - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				if (j != index) {
					return true;
				}
				index--;
			}
		}
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = sizeY - 1; j > 0; j--) {
			if (board[i][j] == 0)
				continue;
			else {
				if (board[i][j] == board[i][j - 1]) {
					return true;
				}
			}
		}
	}
	for (int i = 0; i < sizeX; i++) {
		int index = sizeY - 1;
		for (int j = sizeY - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				if (j != index) {
					return true;
				}
				index--;
			}
		}
	}
	return false;
}
inline bool game::can_shift_left() {
	for (int i = 0; i < sizeX; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeY; j++)
		{
			if (board[i][j] != 0)
			{
				if (j != index)
				{
					return true;
				}
				index++;
			}
		}
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY - 1; j++) {
			if (board[i][j] == 0)
				continue;
			else
			{
				if (board[i][j] == board[i][j + 1]) {
					return true;
				}
			}
		}
	}
	for (int i = 0; i < sizeX; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeY; j++)
		{
			if (board[i][j] != 0)
			{
				if (j != index)
				{
					return true;
				}
				index++;
			}
		}
	}
	return false;
}
inline bool game::can_shift_up() {
	for (int i = 0; i < sizeY; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeX; j++)
		{
			if (board[j][i] != 0)
			{
				if (j != index)
				{
					return true;
				}
				index++;
			}
		}
	}
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX - 1; j++) {
			if (board[j][i] == 0)
				continue;
			else
			{
				if (board[j][i] == board[j + 1][i]) {
					return true;
				}
			}
		}
	}
	for (int i = 0; i < sizeY; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeX; j++)
		{
			if (board[j][i] != 0)
			{
				if (j != index)
				{
					return true;
				}
				index++;
			}
		}
	}
	return false;
}
inline bool game::can_shift_down() {
	for (int i = 0; i < sizeY; i++)
	{
		int index = sizeX - 1;
		for (int j = sizeX - 1; j >= 0; j--)
		{
			if (board[j][i] != 0)
			{
				if (j != index)
				{
					return true;
				}
				index--;
			}
		}
	}
	for (int i = 0; i < sizeY; i++) {
		for (int j = sizeX - 1; j > 0; j--) {
			if (board[j][i] == 0)
				continue;
			else
			{
				if (board[j][i] == board[j - 1][i]) {
					return true;
				}
			}
		}
	}
	for (int i = 0; i < sizeY; i++) {
		int index = sizeX - 1;
		for (int j = sizeX - 1; j >= 0; j--) {
			if (board[j][i] != 0) {
				if (j != index) {
					return true;
				}
				index--;
			}
		}
	}
	return false;
}

inline tuple<int,int,int> game::place_new_tile()
{
	if (this->is_free_space()) {
		//places randomly new tile, either two or four based on two_vs_four_spawn float
		int x = (float)(rand() % 100) / 100 < two_vs_four_spawn ? 4 : 2;
		// find free space
		int i, j;
		do {
			i = rand() % sizeX;
			j = rand() % sizeY;
		} while (board[i][j] != 0);
		// place new tile
		board[i][j] = x;
		return make_tuple(i, j, x);
	}
	else {
		return make_tuple(-1, -1, -1);
	}
}
inline bool game::is_free_space() {
	if (result_is_free_space == -1) {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (board[i][j] == 0) {
					result_is_free_space = 1;
					return true;
				}
				
			}
		}
		result_is_free_space = 0;
		return false;
	}
	else return result_is_free_space;
}
inline bool game::move(int dir) {
	if (!can_shift(dir)) return false;
	this->shift(dir);
	auto res = this->place_new_tile();
	this->step+=1;
	reset_results();
	return get<0>(res) != -1;
}
inline void game::reset_results() {
	result_can_shift_down = -1;
	result_can_shift_up = -1;
	result_can_shift_left = -1;
	result_can_shift_right = -1;
	result_is_lose = -1;
	result_is_win = -1;
	result_is_free_space = -1;
}
inline bool game::is_lose() {
	if (result_is_lose != -1) return result_is_lose;
	result_is_lose = !(this->can_shift(0) || this->can_shift(1) || this->can_shift(2) || this->can_shift(3)) && !this->is_win();
	return result_is_lose;
}
inline bool game::is_win() {
	if (result_is_win == -1) {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (board[i][j] == MAX) {
					result_is_win = 1;
					return true;
				}
			}
		}
		result_is_win = 0;
		return false;
	}
	else return result_is_win;
}

inline int game::free_spaces() {
	int res = 0;
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (board[i][j] == 0) res++;
		}
	}
	return res;
}

inline void game::shift(int dir) {
	switch (dir) {
	case 0:
		this->shift_right();
		break;
	case 1:
		this->shift_up();
		break;
	case 2:
		this->shift_left();
		break;
	case 3:
		this->shift_down();
		break;
	}
}
inline void game::shift_left() {
	for (int i = 0; i < sizeX; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeY; j++)
		{
			if (board[i][j] != 0)
			{
				if (j != index)
				{
					board[i][index] = board[i][j];
					board[i][j] = 0;
				}
				index++;
			}
		}
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY - 1; j++) {
			if (board[i][j] == 0)
				continue;
			else
			{
				if (board[i][j] == board[i][j + 1]) {
					board[i][j] *= 2;
		            score += board[i][j];
					board[i][j + 1] = 0;
				}
			}
		}
	}
	for (int i = 0; i < sizeX; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeY; j++)
		{
			if (board[i][j] != 0)
			{
				if (j != index)
				{
					board[i][index] = board[i][j];
					board[i][j] = 0;
				}
				index++;
			}
		}
	}
}
inline void game::shift_right() {
	for (int i = 0; i < sizeX; i++) {
		int index = sizeY - 1;
		for (int j = sizeY - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				if (j != index) {
					board[i][index] = board[i][j];
					board[i][j] = 0;
				}
				index--;
			}
		}
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = sizeY - 1; j > 0; j--) {
			if (board[i][j] == 0)
				continue;
			else {
				if (board[i][j] == board[i][j - 1]) {
					board[i][j] *= 2;
		            score += board[i][j];
		            board[i][j - 1] = 0;
				}
			}
		}
	}
	for (int i = 0; i < sizeX; i++) {
		int index = sizeY - 1;
		for (int j = sizeY - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				if (j != index) {
					board[i][index] = board[i][j];
					board[i][j] = 0;
				}
				index--;
			}
		}
	}
}
inline void game::shift_up() {
	for (int i = 0; i < sizeY; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeX ; j++)
		{
		    if (board[j][i] != 0)
		    {
		        if (j != index)
		        {
		            board[index][i] = board[j][i];
		            board[j][i] = 0;
		        }
		        index++;
		    }
		}
	}
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX -1; j++) {
		    if (board[j][i] == 0)
		        continue;
		    else
		    {
		        if (board[j][i] == board[j + 1][i]) {
		            board[j][i] *= 2;
		            score += board[j][i];
		            board[j + 1][i] = 0;
		        }
		    }
		}
	}
	for (int i = 0; i < sizeY; i++)
	{
		int index = 0;
		for (int j = 0; j < sizeX; j++)
		{
		    if (board[j][i] != 0)
		    {
		        if (j != index)
		        {
		            board[index][i] = board[j][i];
		            board[j][i] = 0;
		        }
		        index++;
		    }
		}
	}
}
inline void game::shift_down() {
	for (int i = 0; i < sizeY; i++) 
	{
		int index = sizeX - 1;
		for (int j = sizeX - 1; j >= 0; j--) 
		{
			if (board[j][i] != 0) 
			{
				if (j != index)
				{
					board[index][i] = board[j][i];
					board[j][i] = 0;
				}
				index--;
			}
		}
	}		
	for (int i = 0; i < sizeY; i++) {
		for (int j = sizeX - 1; j > 0; j--) {
			if(board[j][i] == 0)
				continue;
			else 
			{
				if (board[j][i] == board[j - 1][i]) {
					board[j][i] *= 2;
					score += board[j][i];
					board[j - 1][i] = 0;
				}
			}
		}
	}
	for (int i = 0; i < sizeY; i++) {
		int index = sizeX - 1; 
		for (int j = sizeX - 1; j >= 0; j--) {
			if (board[j][i] != 0) {
				if (j != index) {
					board[index][i] = board[j][i];
					board[j][i] = 0;
				}
				index--;
			}
		}
	}       
}
inline void game::display() {
	for (int i = 0; i < sizeX; i++) {
		cout << "|";
		for (size_t d = 0; d < sizeY-1; d++)
		{
			cout << dash;
		}
		cout << dash.substr(1);
		cout << "|" << endl;
		for (int j = 0; j < sizeY; j++) {
			if (!(board[i][j] > 100000)) {
				cout << "|";
			}
			if (board[i][j] != 0) {
				if (board[i][j] > 100000)
					cout << board[i][j];
				if (board[i][j] > 10000 && board[i][j] < 100000)
					cout << board[i][j];
				if (board[i][j] > 1000 && board[i][j] < 10000)
					cout << " " << board[i][j];
				if (board[i][j] > 100 && board[i][j] < 1000)
					cout << " " << board[i][j] << " ";
				if (board[i][j] > 10 && board[i][j] < 100)
					cout << "  " << board[i][j] << " ";
				if (board[i][j] > 0 && board[i][j] < 10)
					cout << "  " << board[i][j] << "  ";
			}
			else
				cout << "     ";
		}
		cout << "|" << endl;
	}
	cout << "|";
	for (size_t d = 0; d < sizeY; d++)
	{
		if (d == sizeY - 1) cout << dash.substr(1);
		else cout << dash;
	}
	cout << "|" << endl;
	cout << "score: " << score << endl;
	cout << "steps: " << step << endl;
}

//class game {
//private:
//    const string dash = "------";
//    int sizeY = 4;
//    int sizeX = 4;
//    int MAX = 2048;
//    int score = 0;
//    
//public:
//    game(){
//        board.resize(sizeY, vector<int>(sizeX, 0));
//    }
//    game(int x,int y){
//		sizeX = x;
//		sizeY = y;
//        board.resize(sizeY, vector<int>(sizeX, 0));
//	}
//	
//    bool show = true;
//    vector<vector<int>> board;
//    bool something_moved = false;
//    int step = 0;
//
//    void set_show(bool show) {
//		this->show = show;
//    }
//	
//    void set_max(int max) {
//        MAX = max;
//    }
//	
//    bool can_shift(int dir) {
//		
//    }
//
//    void run(int input = -1)  {
//        char ch, c;
//        show_board();
//        if (is_win()) {
//            cout << "You won!" << endl;
//        play_again:
//            cout << "Play again? (y/n)" << endl;
//            cin >> c;
//            if (c == 'n')
//                return;
//            else if (c == 'y') {
//                init_board();
//                return;
//            }
//        }
//        if (is_lose()) {
//            cout << "game over" << endl;
//            // not nice, i know
//            goto play_again;
//            return;
//        }
//        if (input == -1) {
//            cin >> ch;
//        }
//        else {
//            ch = (char)input;
//        }
//            something_moved = false;
//            switch (ch) {
//            case 'w':
//                merge_up();
//                break;
//            case 's':
//                merge_down();
//                break;
//            case 'a':
//                merge_left();
//                break;
//            case 'd':
//                merge_right();
//                break;
//            case 'q':
//                return;
//            case 'r':
//                run();
//                return;
//            default:
//                break;
//            }
//            if (something_moved) place_new_tile();
//            ++step;
//    }
//	
//    void place_new_tile() {
//		if (is_full())
//			return;
//
//		int x, y;
//		do {
//			x = rand() % sizeX;
//			y = rand() % sizeY;
//		} while (board[x][y] != 0);
//		board[x][y] = get_new_value();
//    }
//	
//    bool is_full() {
//    for (int i = 0; i < sizeX; i++) {
//			for (int j = 0; j < sizeY; j++) {
//				if (board[i][j] == 0)
//					return false;
//			}
//		}
//		return true;
//	}
//	
//
//    void init_board() {
//        score = 0;
//		/*for (int i = 0; i < sizeX; i++) {
//			for (int j = 0; j < sizeY; j++) {
//				board[i][j] = 0;
//			}
//		}*/
//        int i1 = -1, i2 = -1, j1 = -1, j2 = -1;
//        while (i1 == i2 && j1 == j2) {
//            i1 = get_random_index(sizeX);
//            i2 = get_random_index(sizeX);
//            j1 = get_random_index(sizeY);
//            j2 = get_random_index(sizeY);
//        }
//		
//        board[i1][j1] = get_new_value();
//        board[i2][j2] = get_new_value();
//    }
//
//    int get_random_index(int max) {
//		return rand() % max;
//    }
//	
//    int get_new_value() {
//        return 2 + 2 * get_random_index(2);
//    }
//
//    void show_board() {
//        //clear_board();
//        if (!(show || is_win() || is_lose())) return;
//        for (int i = 0; i < sizeX; i++) {
//            cout << "|";
//            for (size_t d = 0; d < sizeY-1; d++)
//            {
//                cout << dash;
//            }
//            cout << dash.substr(1);
//			cout << "|" << endl;
//            for (int j = 0; j < sizeY; j++) {
//                if (!(board[i][j] > 100000)) {
//                    cout << "|";
//                }
//                if (board[i][j] != 0) {
//                    if (board[i][j] > 100000)
//                        cout << board[i][j];
//                    if (board[i][j] > 10000 && board[i][j] < 100000)
//                        cout << board[i][j];
//                    if (board[i][j] > 1000 && board[i][j] < 10000)
//                        cout << " " << board[i][j];
//                    if (board[i][j] > 100 && board[i][j] < 1000)
//                        cout << " " << board[i][j] << " ";
//                    if (board[i][j] > 10 && board[i][j] < 100)
//                        cout << "  " << board[i][j] << " ";
//                    if (board[i][j] > 0 && board[i][j] < 10)
//                        cout << "  " << board[i][j] << "  ";
//                }
//                else
//                    cout << "     ";
//            }
//            cout << "|" << endl;
//        }
//        cout << "|";
//        for (size_t d = 0; d < sizeY; d++)
//        {
//            if (d == sizeY - 1) cout << dash.substr(1);
//            else cout << dash;
//        }
//        cout << "|" << endl;
//        cout << "score: " << score << endl;
//		cout << "steps: " << step << endl;
//    }
//
//    void clear_board() {
//#if linux
//        system("clear");
//#else
//        system("CLS");
//#endif
//    }
//    bool is_free_space() {
//		for (int i = 0; i < sizeX; i++)
//			for (int j = 0; j < sizeY; j++)
//				if (board[i][j] == 0)
//					return true;
//		return false;
//    }
//    bool is_win() {
//        for (int i = 0; i < sizeX; i++) {
//			for (int j = 0; j < sizeY; j++) {
//				if (board[i][j] == MAX)
//					return true;
//			}
//        }
//        return false;
//    }
//    bool is_lose() {
//        for (int i = 0; i < sizeX; i++) {
//            for (int j = 0; j < sizeY; j++) {
//                if (board[i][j] == 0)
//                    return false;
//                if (i > 0 && board[i][j] == board[i - 1][j])
//                    return false;
//                if (i < sizeX - 1 && board[i][j] == board[i + 1][j])
//                    return false;
//                if (j > 0 && board[i][j] == board[i][j - 1])
//                    return false;
//                if (j < sizeY - 1 && board[i][j] == board[i][j + 1])
//                    return false;
//            }
//        }
//    }
//    void merge_down() {
//        
//        for (int i = 0; i < sizeY; i++) 
//        {
//            int index = sizeY - 1;
//            for (int j = sizeX - 1; j >= 0; j--) 
//            {
//                if (board[j][i] != 0) 
//                {
//                    if (j != index)
//                    {
//                        something_moved = true;
//                        board[index][i] = board[j][i];
//                        board[j][i] = 0;
//                    }
//                    index--;
//                }
//            }
//        }		
//        for (int i = 0; i < sizeY; i++) {
//            for (int j = sizeX - 1; j >= 0; j--) {
//                if(board[j][i] == 0)
//					continue;
//                else 
//                {
//                    if (board[j][i] == board[j - 1][i]) {
//                        board[j][i] *= 2;
//                        score += board[j][i];
//                        board[j - 1][i] = 0;
//                        something_moved = true;
//                    }
//                }
//            }
//        }
//        for (int i = 0; i < sizeY; i++) {
//            int index = sizeY - 1; 
//            for (int j = sizeX - 1; j >= 0; j--) {
//                if (board[j][i] != 0) {
//                    if (j != index) {
//                        something_moved = true;
//                        board[index][i] = board[j][i];
//                        board[j][i] = 0;
//                    }
//                    index--;
//                }
//            }
//        }       
//    }
//    void merge_up() {
//        for (int i = 0; i < sizeY; i++)
//        {
//            int index = 0;
//            for (int j = 0; j < sizeX ; j++)
//            {
//                if (board[j][i] != 0)
//                {
//                    if (j != index)
//                    {
//                        something_moved = true;
//                        board[index][i] = board[j][i];
//                        board[j][i] = 0;
//                    }
//                    index++;
//                }
//            }
//        }
//        for (int i = 0; i < sizeY; i++) {
//            for (int j = 0; j < sizeX; j++) {
//                if (board[j][i] == 0)
//                    continue;
//                else
//                {
//                    if (board[j][i] == board[j + 1][i]) {
//                        board[j][i] *= 2;
//                        score += board[j][i];
//                        board[j + 1][i] = 0;
//                        something_moved = true;
//                    }
//                }
//            }
//        }
//        for (int i = 0; i < sizeY; i++)
//        {
//            int index = 0;
//            for (int j = 0; j < sizeX; j++)
//            {
//                if (board[j][i] != 0)
//                {
//                    if (j != index)
//                    {
//                        something_moved = true;
//                        board[index][i] = board[j][i];
//                        board[j][i] = 0;
//                    }
//                    index++;
//                }
//            }
//        }
//        
//    }
//    void merge_left() {
//       for (int i = 0; i < sizeX; i++)
//		{
//			int index = 0;
//			for (int j = 0; j < sizeY; j++)
//			{
//				if (board[i][j] != 0)
//				{
//					if (j != index)
//					{
//						something_moved = true;
//						board[i][index] = board[i][j];
//						board[i][j] = 0;
//					}
//					index++;
//				}
//			}
//		}
//		for (int i = 0; i < sizeX; i++) {
//			for (int j = 0; j < sizeY; j++) {
//				if (board[i][j] == 0)
//					continue;
//				else
//				{
//					if (board[i][j] == board[i][j + 1]) {
//						board[i][j] *= 2;
//                        score += board[i][j];
//						board[i][j + 1] = 0;
//						something_moved = true;
//					}
//				}
//			}
//		}
//		for (int i = 0; i < sizeX; i++)
//		{
//			int index = 0;
//			for (int j = 0; j < sizeY; j++)
//			{
//				if (board[i][j] != 0)
//				{
//					if (j != index)
//					{
//						something_moved = true;
//						board[i][index] = board[i][j];
//						board[i][j] = 0;
//					}
//					index++;
//				}
//			}
//		}
//    }
//    void merge_right() {
//       for (int i = 0; i < sizeX; i++) {
//			int index = sizeX - 1;
//			for (int j = sizeY - 1; j >= 0; j--) {
//				if (board[i][j] != 0) {
//					if (j != index) {
//						something_moved = true;
//						board[i][index] = board[i][j];
//						board[i][j] = 0;
//					}
//					index--;
//				}
//			}
//		}
//		for (int i = 0; i < sizeX; i++) {
//			for (int j = sizeY - 1; j >= 0; j--) {
//				if (board[i][j] == 0)
//					continue;
//				else {
//					if (board[i][j] == board[i][j - 1]) {
//						board[i][j] *= 2;
//                        score += board[i][j];
//                        board[i][j - 1] = 0;
//						something_moved = true;
//					}
//				}
//			}
//		}
//		for (int i = 0; i < sizeX; i++) {
//			int index = sizeX - 1;
//			for (int j = sizeY - 1; j >= 0; j--) {
//				if (board[i][j] != 0) {
//					if (j != index) {
//						something_moved = true;
//						board[i][index] = board[i][j];
//						board[i][j] = 0;
//					}
//					index--;
//				}
//			}
//		}
//    }
//};
