#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "constants.h"
#include "button.h"
#include <graphics.h>

namespace Window {
	const int CONTINUE = 1, NEW = 0, RETURN = 2, RESTART = 3; 
	char *TITLE[2] = {"GAME OVER", "CONGRATULATIONS!"};

	int endGameAnnouncement(bool win) {
		char *title;

		int midx = WINDOW_WIDTH/2, midy = WINDOW_HEIGHT/2;

		settextstyle(BOLD_FONT, HORIZ_DIR, 5);

		Button menu_butt(100, 30, midx - 70, midy + textheight(TITLE[win]), "MENU");
		Button restart_butt(100, 30, midx + 70, midy + textheight(TITLE[win]), "RESTART");

		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, midx-textwidth(TITLE[win])-10, midy-textheight(TITLE[win])-10, midx+textwidth(TITLE[win])+10, midy + textheight(TITLE[win]) + menu_butt.getHeight() + 10);
		
		setbkcolor(MyColor::WINDOW_BG);
		setcolor(MyColor::WINDOW_TEXT);
		outtextxy(midx, midy, TITLE[win]);
		menu_butt.draw();
		restart_butt.draw();

		while (1) {
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
				if (menu_butt.isClicked(x, y)) return RETURN;
				if (restart_butt.isClicked(x, y)) return RESTART;
			} else {
				menu_butt.checkHover();
				restart_butt.checkHover();
			}
		}
	}

	int newGameWarning() {
		char *announce = "There is an old session not finished!";
		int midx = WINDOW_WIDTH/2, midy = WINDOW_HEIGHT/2;

		char *question = "Do you want to continue?";

		int pos_y = midy + textheight(announce) + textheight(question) + 20;
		Button yes(60, 30, midx - 100, pos_y, "YES");

		Button no(60, 30, midx - 14, pos_y, "NO");

		Button return_butt(100, 30, midx + 90, pos_y, "RETURN");

		int width = 500, height = 500;
		pos_y += no.getHeight() + 10;
		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, midx-width/2, midy-textheight(announce) - 10, midx+width/2, pos_y);
		//PRINT CONTENT
		setbkcolor(MyColor::WINDOW_BG);
		setcolor(MyColor::WINDOW_TEXT);
		outtextxy(midx, midy, announce);
		outtextxy(midx, midy + textheight(announce), question);
		yes.draw();
		return_butt.draw();
		no.draw();

		while (1) {
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
				if (yes.isClicked(x, y)) return CONTINUE;
				if (no.isClicked(x, y)) return NEW;
				if (return_butt.isClicked(x, y)) return RETURN;
			} else {
				yes.checkHover();
				no.checkHover();
				return_butt.checkHover();
			}
		}
	}
}

#endif 