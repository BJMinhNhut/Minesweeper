#include "include/headers.h"
using namespace std;

/* Define debug */

void printTitle() {
	int midx = WINDOW_WIDTH/2;
	int midy = WINDOW_HEIGHT/2;

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	SetTextStyle(BOLD_FONT, HORIZ_DIR, 6);
	setcolor(MyColor::TEXT);
	setbkcolor(MyColor::GAME_BG);
   	outtextxy(midx, midy/2, "MINESWEEPER");
}

void printStartMenu() {
	while (1) {
		PlaySound(MAKEINTRESOURCE(MENU_BGM), NULL, SND_RESOURCE|SND_LOOP|SND_ASYNC);
		setbkcolor(MyColor::GAME_BG);
		cleardevice();

		printTitle();

		Menu menu;
		menu.display();
	}
	
	getch();	
}

int main()
{
	initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	mkdir("savefiles");
	Ranking::loadRanking();
	printStartMenu();
	Ranking::saveRanking();
	while (1){}
   	closegraph();
   	return 0;
}