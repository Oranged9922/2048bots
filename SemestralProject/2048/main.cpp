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

using namespace std;


class game {
private:
    const string dash = "------";
    const static int sizeY = 8;
    const static int sizeX = 8;
    int MAX = 2048;
    int score = 0;
    
public:
    game()
    {

    }
    bool show = true;
    int board[sizeY][sizeX] = { 0 };
    bool something_moved = false;
    int step = 0;

    void set_show(bool show) {
		this->show = show;
    }
	
    void set_max(int max) {
        MAX = max;
    }

    void run(int input = -1)  {
        char ch, c;
        show_board();
        if (is_win()) {
            cout << "You won!" << endl;
        play_again:
            cout << "Play again? (y/n)" << endl;
            cin >> c;
            if (c == 'n')
                return;
            else if (c == 'y') {
                init_board();
                return;
            }
        }
        if (is_lose()) {
            cout << "game over" << endl;
            // not nice, i know
            goto play_again;
            return;
        }
        if (input == -1) {
            cin >> ch;
        }
        else {
            ch = (char)input;
        }
            something_moved = false;
            switch (ch) {
            case 'w':
                merge_up();
                break;
            case 's':
                merge_down();
                break;
            case 'a':
                merge_left();
                break;
            case 'd':
                merge_right();
                break;
            case 'q':
                return;
            case 'r':
                run();
                return;
            default:
                break;
            }
            if (something_moved) place_new_tile();
            ++step;
    }
	
    void place_new_tile() {
		if (is_full())
			return;

		int x, y;
		do {
			x = rand() % sizeX;
			y = rand() % sizeY;
		} while (board[x][y] != 0);
		board[x][y] = get_new_value();
    }
	
    bool is_full() {
    for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (board[i][j] == 0)
					return false;
			}
		}
		return true;
	}
	

    void init_board() {
        score = 0;
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				board[i][j] = 0;
			}
		}
        int i1 = -1, i2 = -1, j1 = -1, j2 = -1;
        while (i1 == i2 && j1 == j2) {
            i1 = get_random_index(sizeX);
            i2 = get_random_index(sizeX);
            j1 = get_random_index(sizeY);
            j2 = get_random_index(sizeY);
        }
		
        board[i1][j1] = get_new_value();
        board[i2][j2] = get_new_value();
    }

    int get_random_index(int max) {
		return rand() % max;
    }
	
    int get_new_value() {
        return 2 + 2 * get_random_index(2);
    }

    void show_board() {
        //clear_board();
        if (!(show || is_win() || is_lose())) return;
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

    void clear_board() {
#if linux
        system("clear");
#else
        system("CLS");
#endif
    }
    bool is_free_space() {
		for (int i = 0; i < sizeX; i++)
			for (int j = 0; j < sizeY; j++)
				if (board[i][j] == 0)
					return true;
		return false;
    }
    bool is_win() {
        for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (board[i][j] == MAX)
					return true;
			}
        }
        return false;
    }
    bool is_lose() {
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                if (board[i][j] == 0)
                    return false;
                if (i > 0 && board[i][j] == board[i - 1][j])
                    return false;
                if (i < sizeX - 1 && board[i][j] == board[i + 1][j])
                    return false;
                if (j > 0 && board[i][j] == board[i][j - 1])
                    return false;
                if (j < sizeY - 1 && board[i][j] == board[i][j + 1])
                    return false;
            }
        }
    }
    void merge_down() {
        
        for (int i = 0; i < sizeY; i++) 
        {
            int index = sizeY - 1;
            for (int j = sizeX - 1; j >= 0; j--) 
            {
                if (board[j][i] != 0) 
                {
                    if (j != index)
                    {
                        something_moved = true;
                        board[index][i] = board[j][i];
                        board[j][i] = 0;
                    }
                    index--;
                }
            }
        }		
        for (int i = 0; i < sizeY; i++) {
            for (int j = sizeX - 1; j >= 0; j--) {
                if(board[j][i] == 0)
					continue;
                else 
                {
                    if (board[j][i] == board[j - 1][i]) {
                        board[j][i] *= 2;
                        score += board[j][i];
                        board[j - 1][i] = 0;
                        something_moved = true;
                    }
                }
            }
        }
        for (int i = 0; i < sizeY; i++) {
            int index = sizeY - 1; 
            for (int j = sizeX - 1; j >= 0; j--) {
                if (board[j][i] != 0) {
                    if (j != index) {
                        something_moved = true;
                        board[index][i] = board[j][i];
                        board[j][i] = 0;
                    }
                    index--;
                }
            }
        }       
    }
    void merge_up() {
        for (int i = 0; i < sizeY; i++)
        {
            int index = 0;
            for (int j = 0; j < sizeX ; j++)
            {
                if (board[j][i] != 0)
                {
                    if (j != index)
                    {
                        something_moved = true;
                        board[index][i] = board[j][i];
                        board[j][i] = 0;
                    }
                    index++;
                }
            }
        }
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                if (board[j][i] == 0)
                    continue;
                else
                {
                    if (board[j][i] == board[j + 1][i]) {
                        board[j][i] *= 2;
                        score += board[j][i];
                        board[j + 1][i] = 0;
                        something_moved = true;
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
                        something_moved = true;
                        board[index][i] = board[j][i];
                        board[j][i] = 0;
                    }
                    index++;
                }
            }
        }
        
    }
    void merge_left() {
       for (int i = 0; i < sizeX; i++)
		{
			int index = 0;
			for (int j = 0; j < sizeY; j++)
			{
				if (board[i][j] != 0)
				{
					if (j != index)
					{
						something_moved = true;
						board[i][index] = board[i][j];
						board[i][j] = 0;
					}
					index++;
				}
			}
		}
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (board[i][j] == 0)
					continue;
				else
				{
					if (board[i][j] == board[i][j + 1]) {
						board[i][j] *= 2;
                        score += board[i][j];
						board[i][j + 1] = 0;
						something_moved = true;
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
						something_moved = true;
						board[i][index] = board[i][j];
						board[i][j] = 0;
					}
					index++;
				}
			}
		}
    }
    void merge_right() {
       for (int i = 0; i < sizeX; i++) {
			int index = sizeX - 1;
			for (int j = sizeY - 1; j >= 0; j--) {
				if (board[i][j] != 0) {
					if (j != index) {
						something_moved = true;
						board[i][index] = board[i][j];
						board[i][j] = 0;
					}
					index--;
				}
			}
		}
		for (int i = 0; i < sizeX; i++) {
			for (int j = sizeY - 1; j >= 0; j--) {
				if (board[i][j] == 0)
					continue;
				else {
					if (board[i][j] == board[i][j - 1]) {
						board[i][j] *= 2;
                        score += board[i][j];
                        board[i][j - 1] = 0;
						something_moved = true;
					}
				}
			}
		}
		for (int i = 0; i < sizeX; i++) {
			int index = sizeX - 1;
			for (int j = sizeY - 1; j >= 0; j--) {
				if (board[i][j] != 0) {
					if (j != index) {
						something_moved = true;
						board[i][index] = board[i][j];
						board[i][j] = 0;
					}
					index--;
				}
			}
		}
    }
};

class bots
{
public:
    // player playing
    static void player1(game& g) {
        srand((unsigned)time(NULL));
        //initialize board
        g.init_board();
        long tick = 0;
        while (!g.is_win()) {
            
            g.run(-1);
        }
    }

    static void algo2(game& g) {
        srand((unsigned)time(NULL));
        //initialize board
        g.init_board();
        long tick = 0;
        char c;
        while (!g.is_win()) {
            c = rand() % 2 ? 's' : 'd';
            g.run(c);
            ++tick;

            if (!g.something_moved) {
                c = (c == 's') ? 'd' : 's';
                g.run(c);
                ++tick;
                if (g.show) {
                    cout << "move: " << c << endl;
                    cout << "steps: " << tick << endl;
                }
            }

            if (!g.something_moved) {
                g.run('a');
                c = 'a';
                ++tick;
                if (g.show) {
                    cout << "move: " << c << endl;
                    cout << "steps: " << tick << endl;

                }
            }
                if (!g.something_moved) {
                    g.run('w');
                    c = 'w';
                    ++tick;
                    if (g.show) {
                        cout << "move: " << c << endl;
                        cout << "steps: " << tick << endl;
                    }
                }
            ++tick;
            if (g.show) {
                cout << "move: " << c << endl;
                cout << "steps: " << tick << endl;
            }
            if (g.is_lose()) break;
        }
        g.run('s');
        
    }
    static void algo3(game& g) {
        srand((unsigned)time(NULL));
        //initialize board
        g.init_board();
    }
};

int main() {
    game g;
    int size; 
    char ch;
    char show;
    int sizeX;
    int sizeY;
    while (true) {

        cout << "2048" << endl;
        cout << "Rules: type w(up), s(down), a(left), d(right) keys to shift the tiles" << endl;
        cout << "Add tiles with same number to double the value" << endl;
        cout << "Choose the winning condition (value of the tile to reach) (type the exponent (meaning 2^n ... 10 = 2048, 11 = 4096...))" << endl;
        cin >> size;
        cout << "Enter q to quit" << endl;
        cout << "Enter 1 if you want to play on your own" << endl;
        cout << "Enter 2 if you want algorithm1 (naive) to play for you" << endl;
        cin >> ch;
		
		cout << "Do you want to see all steps, or just the final result? (y/n)" << endl;
        cin >> show;
        g.set_max(2 << size);
        g.set_show(show == 'y');
        switch (ch) {
            case '1':
                bots::player1(g);
                break;
            case '2':
                bots::algo2(g);
                break; 
            case '3':
                bots::algo3(g);
                break;
            case 'q':
                return 0;
            default:
                break;
        }
    }
    return 0;
}