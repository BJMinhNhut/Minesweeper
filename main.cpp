#include "include/headers.h"
using namespace std;

/* Define debug */

void printTitle() {
	int midx = WINDOW_WIDTH/2;
	int midy = WINDOW_HEIGHT/2;

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(MyColor::TEXT);
	setbkcolor(MyColor::GAME_BG);
   	outtextxy(midx, midy/2, "MINESWEEPER");
}

void printStartMenu() {
	while (1) {
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
	printStartMenu();
   	closegraph();
   	return 0;
}