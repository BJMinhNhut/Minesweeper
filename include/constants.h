#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define DEBUG_MOUSE 1
#include <bits/stdc++.h>
// #define _DEBUG_BOX_COLOR_

const int WINDOW_HEIGHT = 700;
const int WINDOW_WIDTH = 700;
const char WINDOW_TITLE[] = "Minesweeper";	

const int NEXTX[8] = {-1, 0, 1, 0, 1, -1, 1, -1};
const int NEXTY[8] = {0, -1, 0, 1, -1, 1, 1, -1};

const int DEBUG_WIDTH = 10;
const int DEBUG_HEIGHT = 10;
const int DEBUG_BOMB = 12;

namespace GameMode {
	const int CUSTOM = 0;
	const int EASY = 1;
	const int NORMAL = 2;
	const int HARD = 3;

	const int NMODE = 4;
	char *CAPTION[NMODE] = {"Custom", "Easy", "Normal", "Hard"};
	const std::tuple<int, int, int> PROPERTIES[NMODE] = {std::make_tuple(-1, -1, -1), std::make_tuple(10, 10, 12), 
													std::make_tuple(20, 20, 50), std::make_tuple(30, 30, 100)};
}

namespace MyColor {
	const int GAME_BG = COLOR(64, 60, 57);
	const int TEXT = WHITE;

	const int BORDER = COLOR(215, 215, 170);
	const int FLAG = COLOR(255, 143, 0);
	const int HIDDEN = COLOR(119, 148, 85);
	const int REVEAL = COLOR(235, 235, 208);
	const int BOMB_BG = COLOR(244, 67, 54);
	const int ONE = COLOR(13, 70, 160);
	const int TWO = COLOR(0, 96, 100);
	const int THREE = COLOR(27, 94, 32);
	const int FOUR = COLOR(130, 119, 23);
	const int FIVE = COLOR(255, 111, 0);
	const int SIX = COLOR(191, 54, 12);
	const int SEVEN = COLOR(183, 28, 28);
	const int EIGHT = COLOR(136, 14, 79);

} 

namespace GameFile {
	const char TIME[] = "savefiles\\time.log";
	const char GAME[] = "savefiles\\game.log";
}

#endif


