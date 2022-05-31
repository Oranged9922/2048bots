#include "pch.h"
#include "..\2048\include\game.h"
#include "..\2048\include\bots.h"

namespace gameTests {
	// test for game.h, default initialization, board size should be 4x4
	TEST(Game, Default_constructor_initialization) {
		game game;
		EXPECT_EQ(game.get_board_size(), make_tuple(4, 4));
	}
	// test for game.h, board size 8x6
	TEST(Game, Constructor_initialization_8x6) {
		game game(8, 6);
		EXPECT_EQ(game.get_board_size(), make_tuple(8, 6));
		game.restart();
		EXPECT_EQ(game.free_spaces(), (8 * 6) - 2);		
	}
	TEST(Game, Constructor_initialization_6x8) {
		game game(6, 8);
		EXPECT_EQ(game.get_board_size(), make_tuple(6, 8));
		game.restart();
		EXPECT_EQ(game.free_spaces(), (8 * 6) - 2);
	}
	TEST(Game, Constructor_initialization_max) {
		game game(8, 6,4096);
		EXPECT_EQ(game.get_board_size(), make_tuple(8, 6));
		EXPECT_EQ(game.get_max(), 4096);
	}	
	
	// tests for can_shift function
	TEST(Game_can_shift, can_shift_right1) {
		game game;
		game.set_board(vector<vector<int>>{ 
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{2,4,8,16} });
		// right
		EXPECT_EQ(game.can_shift(0), false);
	}
	TEST(Game_can_shift, can_shift_right2) {
		game game;
		game.set_board(vector<vector<int>>{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{4,4,8,16} });
		// right
		EXPECT_EQ(game.can_shift(0), true);
	}
	TEST(Game_can_shift, can_shift_right3) {
		game game;
		game.set_board(vector<vector<int>>{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{4,0,8,16} });
		// right
		EXPECT_EQ(game.can_shift(0), true);
	}
	TEST(Game_can_shift, can_shift_left1) {
		game game;
		game.set_board(vector<vector<int>>{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{2,4,8,16} });
		// left
		EXPECT_EQ(game.can_shift(2), false);
	}
	TEST(Game_can_shift, can_shift_left2) {
		game game;
		game.set_board(vector<vector<int>>{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{4,4,8,16} });
		// up
		EXPECT_EQ(game.can_shift(2), true);
	}
	TEST(Game_can_shift, can_shift_left3) {
		game game;
		game.set_board(vector<vector<int>>{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{2,0,8,16} });
		// down
		EXPECT_EQ(game.can_shift(2), true);
	}
	
	TEST(Game_can_shift, can_shift_up1) {
		game game;
		game.set_board(vector<vector<int>>{
			{16,0,0,0},
			{8,0,0,0},
			{4,0,0,0},
			{2,0,0,0} });
		// left
		EXPECT_EQ(game.can_shift(1), false);
	}
	TEST(Game_can_shift, can_shift_up2) {
		game game;
		game.set_board(vector<vector<int>>{
			{16,0,0,0},
			{8,0,0,0},
			{4,0,0,0},
			{4,0,0,0} });
		// up
		EXPECT_EQ(game.can_shift(1), true);
	}
	TEST(Game_can_shift, can_shift_up3) {
		game game;
		game.set_board(vector<vector<int>>{
			{16,0,0,0},
			{8,0,0,0},
			{0,0,0,0},
			{2,0,0,0} });
		// down
		EXPECT_EQ(game.can_shift(1), true);
	}
	
	TEST(Game_can_shift, can_shift_down1) {
		game game;
		game.set_board(vector<vector<int>>{
			{16,0,0,0},
			{8,0,0,0},
			{4,0,0,0},
			{2,0,0,0} });
		// left
		EXPECT_EQ(game.can_shift(3), false);
	}
	TEST(Game_can_shift, can_shift_down2) {
		game game;
		game.set_board(vector<vector<int>>{
			{16,0,0,0},
			{8,0,0,0},
			{4,0,0,0},
			{4,0,0,0} });
		// up
		EXPECT_EQ(game.can_shift(3), true);
	}
	TEST(Game_can_shift, can_shift_down3) {
		game game;
		game.set_board(vector<vector<int>>{
			{16,0,0,0},
			{8,0,0,0},
			{0,0,0,0},
			{2,0,0,0} });
		// down
		EXPECT_EQ(game.can_shift(3), true);
	}
	
	// tests for placing tiles
	TEST(Game_place_tile, place_tile_empty) {
		game game;
		game.set_board(vector<vector<int>>{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0} });
		auto res = game.place_new_tile();
		EXPECT_EQ(game.board[get<0>(res)][get<1>(res)], get<2>(res));
	}
	TEST(Game_place_tile, place_tile_full) {
		game game;
		game.set_board(vector<vector<int>>{
			{2,4,8,16},
			{2,4,8,16},
			{2,4,8,16},
			{2,4,8,16} });
		auto res = game.place_new_tile();
		EXPECT_EQ(res == make_tuple(-1,-1,-1), true);
	}
	TEST(Game_place_tile, one_tile_free) {
		game game;
		game.set_board(vector<vector<int>>{
			{2,2,2,2},
			{4,8,2,2},
			{0,16,4,2},
			{2,16,4,2} });
		auto res = game.place_new_tile();
		EXPECT_EQ(game.board[get<0>(res)][get<1>(res)], get<2>(res));
	}

	// tests for shifting
	TEST(Game_shift, test_right_1) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 2, 2, 2},
			{ 4,8,2,2 },
			{ 0,16,4,2 },
			{ 2,16,4,2 } });
		game.shift(0);
		EXPECT_EQ(game.get_tile(0, 0), 0);
		EXPECT_EQ(game.get_tile(0, 1), 0);
		EXPECT_EQ(game.get_tile(0, 2), 4);
		EXPECT_EQ(game.get_tile(0, 3), 4);

		EXPECT_EQ(game.get_tile(1, 0), 0);
		EXPECT_EQ(game.get_tile(1, 1), 4);
		EXPECT_EQ(game.get_tile(1, 2), 8);
		EXPECT_EQ(game.get_tile(1, 3), 4);

		EXPECT_EQ(game.get_tile(2, 0), 0);
		EXPECT_EQ(game.get_tile(2, 1), 16);
		EXPECT_EQ(game.get_tile(2, 2), 4);
		EXPECT_EQ(game.get_tile(2, 3), 2);

		EXPECT_EQ(game.get_tile(3, 0), 2);
		EXPECT_EQ(game.get_tile(3, 1), 16);
		EXPECT_EQ(game.get_tile(3, 2), 4);
		EXPECT_EQ(game.get_tile(3, 3), 2);
	}
	TEST(Game_shift, test_right_2) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 4, 8, 16},
			{ 0,0,4,8 },
			{ 0,0,0,4 },
			{ 0,0,2,2 } });
		game.shift(0);
		EXPECT_EQ(game.get_tile(0, 0), 2);
		EXPECT_EQ(game.get_tile(0, 1), 4);
		EXPECT_EQ(game.get_tile(0, 2), 8);
		EXPECT_EQ(game.get_tile(0, 3), 16);

		EXPECT_EQ(game.get_tile(1, 0), 0);
		EXPECT_EQ(game.get_tile(1, 1), 0);
		EXPECT_EQ(game.get_tile(1, 2), 4);
		EXPECT_EQ(game.get_tile(1, 3), 8);

		EXPECT_EQ(game.get_tile(2, 0), 0);
		EXPECT_EQ(game.get_tile(2, 1), 0);
		EXPECT_EQ(game.get_tile(2, 2), 0);
		EXPECT_EQ(game.get_tile(2, 3), 4);

		EXPECT_EQ(game.get_tile(3, 0), 0);
		EXPECT_EQ(game.get_tile(3, 1), 0);
		EXPECT_EQ(game.get_tile(3, 2), 0);
		EXPECT_EQ(game.get_tile(3, 3), 4);
	}
	TEST(Game_shift, test_up_1) {
		game game;
		game.set_board(vector<vector<int>>{
			{2,2,2,2},
			{4,8,2,2},
			{0,16,4,2},
			{2,16,4,2} });
		game.shift(1);
		EXPECT_EQ(game.get_tile(0, 0), 2);
		EXPECT_EQ(game.get_tile(0, 1), 2);
		EXPECT_EQ(game.get_tile(0, 2), 4);
		EXPECT_EQ(game.get_tile(0, 3), 4);

		EXPECT_EQ(game.get_tile(1, 0), 4);
		EXPECT_EQ(game.get_tile(1, 1), 8);
		EXPECT_EQ(game.get_tile(1, 2), 8);
		EXPECT_EQ(game.get_tile(1, 3), 4);
		
		EXPECT_EQ(game.get_tile(2, 0), 2);
		EXPECT_EQ(game.get_tile(2, 1), 32);
		EXPECT_EQ(game.get_tile(2, 2), 0);
		EXPECT_EQ(game.get_tile(2, 3), 0);
		
		EXPECT_EQ(game.get_tile(3, 0), 0);
		EXPECT_EQ(game.get_tile(3, 1), 0);
		EXPECT_EQ(game.get_tile(3, 2), 0);
		EXPECT_EQ(game.get_tile(3, 3), 0);
	}
	TEST(Game_shift, test_up_2) {
		game game;
		game.set_board(vector<vector<int>>{
			{2,4,8,16},
			{0,0,4,8},
			{0,0,0,4},
			{0,0,2,2} });
		game.shift(1);
		EXPECT_EQ(game.get_tile(0, 0), 2);
		EXPECT_EQ(game.get_tile(0, 1), 4);
		EXPECT_EQ(game.get_tile(0, 2), 8);
		EXPECT_EQ(game.get_tile(0, 3), 16);

		EXPECT_EQ(game.get_tile(1, 0), 0);
		EXPECT_EQ(game.get_tile(1, 1), 0);
		EXPECT_EQ(game.get_tile(1, 2), 4);
		EXPECT_EQ(game.get_tile(1, 3), 8);
		
		EXPECT_EQ(game.get_tile(2, 0), 0);
		EXPECT_EQ(game.get_tile(2, 1), 0);
		EXPECT_EQ(game.get_tile(2, 2), 2);
		EXPECT_EQ(game.get_tile(2, 3), 4);
		
		EXPECT_EQ(game.get_tile(3, 0), 0);
		EXPECT_EQ(game.get_tile(3, 1), 0);
		EXPECT_EQ(game.get_tile(3, 2), 0);
		EXPECT_EQ(game.get_tile(3, 3), 2);
	}

	TEST(Game_shift, test_left_1) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 2, 2, 2},
			{ 4,8,2,2 },
			{ 0,16,4,2 },
			{ 2,16,4,2 } });
		game.shift(2);
		EXPECT_EQ(game.get_tile(0, 0), 4);
		EXPECT_EQ(game.get_tile(0, 1), 4);
		EXPECT_EQ(game.get_tile(0, 2), 0);
		EXPECT_EQ(game.get_tile(0, 3), 0);

		EXPECT_EQ(game.get_tile(1, 0), 4);
		EXPECT_EQ(game.get_tile(1, 1), 8);
		EXPECT_EQ(game.get_tile(1, 2), 4);
		EXPECT_EQ(game.get_tile(1, 3), 0);

		EXPECT_EQ(game.get_tile(2, 0), 16);
		EXPECT_EQ(game.get_tile(2, 1), 4);
		EXPECT_EQ(game.get_tile(2, 2), 2);
		EXPECT_EQ(game.get_tile(2, 3), 0);

		EXPECT_EQ(game.get_tile(3, 0), 2);
		EXPECT_EQ(game.get_tile(3, 1), 16);
		EXPECT_EQ(game.get_tile(3, 2), 4);
		EXPECT_EQ(game.get_tile(3, 3), 2);
	}
	TEST(Game_shift, test_left_2) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 4, 8, 16},
			{ 0,0,4,8 },
			{ 0,0,0,4 },
			{ 0,0,2,2 } });
		game.shift(2);
		EXPECT_EQ(game.get_tile(0, 0), 2);
		EXPECT_EQ(game.get_tile(0, 1), 4);
		EXPECT_EQ(game.get_tile(0, 2), 8);
		EXPECT_EQ(game.get_tile(0, 3), 16);

		EXPECT_EQ(game.get_tile(1, 0), 4);
		EXPECT_EQ(game.get_tile(1, 1), 8);
		EXPECT_EQ(game.get_tile(1, 2), 0);
		EXPECT_EQ(game.get_tile(1, 3), 0);

		EXPECT_EQ(game.get_tile(2, 0), 4);
		EXPECT_EQ(game.get_tile(2, 1), 0);
		EXPECT_EQ(game.get_tile(2, 2), 0);
		EXPECT_EQ(game.get_tile(2, 3), 0);

		EXPECT_EQ(game.get_tile(3, 0), 4);
		EXPECT_EQ(game.get_tile(3, 1), 0);
		EXPECT_EQ(game.get_tile(3, 2), 0);
		EXPECT_EQ(game.get_tile(3, 3), 0);
	}
	TEST(Game_shift, test_down_1) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 2, 2, 2},
			{ 4,8,2,2 },
			{ 0,16,4,2 },
			{ 2,16,4,2 } });
		game.shift(3);
		EXPECT_EQ(game.get_tile(0, 0), 0);
		EXPECT_EQ(game.get_tile(0, 1), 0);
		EXPECT_EQ(game.get_tile(0, 2), 0);
		EXPECT_EQ(game.get_tile(0, 3), 0);

		EXPECT_EQ(game.get_tile(1, 0), 2);
		EXPECT_EQ(game.get_tile(1, 1), 2);
		EXPECT_EQ(game.get_tile(1, 2), 0);
		EXPECT_EQ(game.get_tile(1, 3), 0);

		EXPECT_EQ(game.get_tile(2, 0), 4);
		EXPECT_EQ(game.get_tile(2, 1), 8);
		EXPECT_EQ(game.get_tile(2, 2), 4);
		EXPECT_EQ(game.get_tile(2, 3), 4);

		EXPECT_EQ(game.get_tile(3, 0), 2);
		EXPECT_EQ(game.get_tile(3, 1), 32);
		EXPECT_EQ(game.get_tile(3, 2), 8);
		EXPECT_EQ(game.get_tile(3, 3), 4);
	}
	TEST(Game_shift, test_down_2) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 4, 8, 16},
			{ 0,0,4,8 },
			{ 0,0,0,4 },
			{ 0,0,2,2 } });
		game.shift(3);
		EXPECT_EQ(game.get_tile(0, 0), 0);
		EXPECT_EQ(game.get_tile(0, 1), 0);
		EXPECT_EQ(game.get_tile(0, 2), 0);
		EXPECT_EQ(game.get_tile(0, 3), 16);

		EXPECT_EQ(game.get_tile(1, 0), 0);
		EXPECT_EQ(game.get_tile(1, 1), 0);
		EXPECT_EQ(game.get_tile(1, 2), 8);
		EXPECT_EQ(game.get_tile(1, 3), 8);

		EXPECT_EQ(game.get_tile(2, 0), 0);
		EXPECT_EQ(game.get_tile(2, 1), 0);
		EXPECT_EQ(game.get_tile(2, 2), 4);
		EXPECT_EQ(game.get_tile(2, 3), 4);

		EXPECT_EQ(game.get_tile(3, 0), 2);
		EXPECT_EQ(game.get_tile(3, 1), 4);
		EXPECT_EQ(game.get_tile(3, 2), 2);
		EXPECT_EQ(game.get_tile(3, 3), 2);
	}
	
	TEST(Game_shift, cant_shift_lose) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 4, 8, },
			{ 4, 2, 4, },
			{ 2, 4, 2, }
		});
		EXPECT_EQ(game.can_shift(0), false);
		EXPECT_EQ(game.can_shift(1), false);
		EXPECT_EQ(game.can_shift(2), false);
		EXPECT_EQ(game.can_shift(3), false);
		EXPECT_EQ(game.is_lose(), true);
		EXPECT_EQ(game.is_win(), false);
	}

	TEST(Game_shift, cant_shift_win) {
		game game;
		game.set_board(vector<vector<int>>{
			{2, 2048, 8, },
			{ 4, 2, 4, },
			{ 2, 4, 2, }
		});
		EXPECT_EQ(game.can_shift(0), false);
		EXPECT_EQ(game.can_shift(1), false);
		EXPECT_EQ(game.can_shift(2), false);
		EXPECT_EQ(game.can_shift(3), false);
		EXPECT_EQ(game.is_win(), true);
		EXPECT_EQ(game.is_lose(), false);
	}

	// tests for winning/losing conditions
	TEST(Game_winlose, test_win) {
		game game;
		game.set_board(vector<vector<int>>{
			{0, 0, 0, 0},
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 1024, 1024 }});
		
		EXPECT_EQ(game.is_win(), false);
		EXPECT_EQ(game.is_lose(), false);
		game.move(0);
		EXPECT_EQ(game.is_win(), true);
		EXPECT_EQ(game.is_lose(), false);
	}

	TEST(Game_winlose, test_lose) {
		game game;
		game.set_board(vector<vector<int>>{
			{  2,  4, 16, 2},
			{  4,  8,  2, 4},
			{ 64, 16,  4, 2},
			{ 32, 16,  4, 4} });
		EXPECT_EQ(game.is_win(), false);
		EXPECT_EQ(game.is_lose(), false);
		game.move(0);
		EXPECT_EQ(game.is_win(), false);
		EXPECT_EQ(game.is_lose(), true);
	}
}

namespace botsTests {
	
}