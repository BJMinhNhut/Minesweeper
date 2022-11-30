#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define DEBUG_MOUSE 1
#include <bits/stdc++.h>
// #define _DEBUG_BOX_COLOR_

const int WINDOW_HEIGHT = 750;
const int WINDOW_WIDTH = 1200;
const char WINDOW_TITLE[] = "Minesweeper";	
const int MAP_PADDING = 30;
const int SCOREBOARD_WIDTH = 120;
const int SCOREBOARD_HEIGHT = 80;
const int GAME_WIDTH = WINDOW_WIDTH - 4*MAP_PADDING - SCOREBOARD_WIDTH;

const int MENU_HEIGHT = 40, MENU_WIDTH = 200;
const int OPTION_HEIGHT = 40, OPTION_WIDTH = 400;

const int NEXTX[8] = {-1, 0, 1, 0, 1, -1, 1, -1};
const int NEXTY[8] = {0, -1, 0, 1, -1, 1, 1, -1};

const int DEBUG_WIDTH = 10;
const int DEBUG_HEIGHT = 10;
const int DEBUG_BOMB = 12;

const int MAX_SIZE = 30;
const int MAX_BOMB = 99;
const int MIN_SIZE = 0;
const int MIN_BOMB = 0;
const int DEFAULT_SIZE = 16;
const int DEFAULT_BOMB = 40;

namespace GameMode {
	const int CUSTOM = 0;
	const int EASY = 1;
	const int NORMAL = 2;
	const int HARD = 3;

	const int NMODE = 5;
	char *DESCRIP[NMODE] = {"", "(9x9, 10 bombs)", "(16x16, 40 bombs)", "(30x16, 99 bombs)", "(30x30, 199 bombs)"};
	char *CAPTION[NMODE] = {"CUSTOM", "WEAK", "FIT", "STRONG", "SUPERHERO"};
	const std::tuple<int, int, int> PROPERTIES[NMODE] = {std::make_tuple(-1, -1, -1), std::make_tuple(9, 9, 10), 
													std::make_tuple(16, 16, 40), std::make_tuple(16, 30, 99), std::make_tuple(30, 30, 199)};
}

namespace Image {
	const char FLAG[] = "assets\\flag.bmp"; 
	const char BOMB[] = "assets\\bomb.bmp"; 
	const char BOMB_INACTIVE[] = "assets\\bomb_inactive.bmp"; 
}

namespace MyColor {
	const int GAME_BG = COLOR(5, 12, 27);
	const int TEXT = WHITE;

	// const int BUTTON = COLOR(29, 36, 50);
	const int BUTTON = GAME_BG;
	const int BUTTON_HOVER = COLOR(50, 199, 102);
	const int BOX_HOVER = COLOR(88, 93, 104);
	const int WINDOW_BG = COLOR(29, 36, 50);
	const int WINDOW_TEXT = WHITE;

	const int BORDER = COLOR(140, 150, 166);
	const int FLAG = COLOR(50, 199, 102);
	// const int HIDDEN = COLOR(29, 36, 50);
	const int HIDDEN = WINDOW_BG;
	const int REVEAL = WHITE;
	const int BOMB_BG = COLOR(226, 81, 71);
	const int ONE = COLOR(13, 70, 160);
	const int TWO = COLOR(0, 96, 100);
	const int THREE = COLOR(27, 94, 32);
	const int FOUR = COLOR(130, 119, 23);
	const int FIVE = COLOR(255, 111, 0);
	const int SIX = COLOR(191, 54, 12); 
	const int SEVEN = COLOR(183, 28, 28);
	const int EIGHT = COLOR(136, 14, 79);

	const int ADJUST_BUTTON = COLOR(64, 193, 232);
	const int WINDOW_TITLE = COLOR(29, 36, 50);
} 

namespace GameFile {
	const char TIME[] = "savefiles\\time.log";
	const char GAME[] = "savefiles\\game.log";
	const char RANK[] = "savefiles\\rank.log";
}

void drawFrame(int background, int color, int left, int top, int right, int bot) {
	setbkcolor(background);
	setcolor(color);
	setfillstyle(SOLID_FILL, background);
	bar(left, top, right, bot);
	rectangle(left, top, right, bot);
}

#endif


