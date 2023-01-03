#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "constants.h"
#include "button.h"
#include <graphics.h>

namespace Window {
	const int CONTINUE = 1, NEW = 0, RETURN = 2, RESTART = 3; 
	char *TITLE[2] = {"GAME OVER", "CONGRATULATIONS!"};

	int loseGameAnnouncement(int game_mode, string game_descrip, int flag) {
		bool win = false;
		clearmouseclick(WM_LBUTTONDOWN);

		int midx = (GAME_WIDTH + 2*MAP_PADDING)/2, midy = WINDOW_HEIGHT/2;

		SetTextStyle(BOLD_FONT, HORIZ_DIR, 5);

		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, midx-270, midy-textheight(TITLE[win])-100, midx+270, midy + textheight(TITLE[win]) + 120);
		
		setbkcolor(MyColor::WINDOW_BG);
		setcolor(MyColor::WINDOW_TEXT);

		int cury = midy-70;
		outtextxy(midx, cury, TITLE[win]);

		cury += 50;
		SetTextStyle(BOLD_FONT, HORIZ_DIR, 2);
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(midx-200, cury, "Game mode:");

		settextjustify(RIGHT_TEXT, CENTER_TEXT);
		outtextxy(midx+200, cury, &(GameMode::CAPTION[game_mode])[0]);

		cury += 30;
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(midx-200, cury, "Properties:");

		settextjustify(RIGHT_TEXT, CENTER_TEXT);
		outtextxy(midx+200, cury, &(game_descrip)[0]);

		cury += 30;
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(midx-200, cury, "Correct flags:");

		settextjustify(RIGHT_TEXT, CENTER_TEXT);
		outtextxy(midx+200, cury, &(to_string(flag))[0]);

		cury += 60;

		Button menu_butt(100, 30, midx - 70, cury, "MENU");
		Button restart_butt(100, 30, midx + 70, cury, "RESTART");


		menu_butt.draw();
		restart_butt.draw();

		while (1) {
			if (menu_butt.checkHover() == Button::CLICKED) return RETURN;
			if (restart_butt.checkHover() == Button::CLICKED) return RESTART;
		}
	}

	int winGameAnnouncement(int game_mode, string game_descrip, string play_time, string best_time) {
		bool win = true;
		clearmouseclick(WM_LBUTTONDOWN);

		int midx = (GAME_WIDTH + 2*MAP_PADDING)/2, midy = WINDOW_HEIGHT/2;

		SetTextStyle(BOLD_FONT, HORIZ_DIR, 5);

		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, midx-270, midy-textheight(TITLE[win])-100, 
					midx+270, midy + textheight(TITLE[win]) + 140 - 30*(game_mode >= GameMode::NMODE-1));
		
		setbkcolor(MyColor::WINDOW_BG);
		setcolor(MyColor::WINDOW_TEXT);

		int cury = midy-70;
		outtextxy(midx, cury, TITLE[win]);

		cury += 50;
		SetTextStyle(BOLD_FONT, HORIZ_DIR, 2);
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(midx-200, cury, "Game mode:");

		settextjustify(RIGHT_TEXT, CENTER_TEXT);
		outtextxy(midx+200, cury, &(GameMode::CAPTION[game_mode])[0]);

		cury += 30;
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(midx-200, cury, "Properties:");

		settextjustify(RIGHT_TEXT, CENTER_TEXT);
		outtextxy(midx+200, cury, &(game_descrip)[0]);

		cury += 30;
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(midx-200, cury, "Play time:");

		settextjustify(RIGHT_TEXT, CENTER_TEXT);
		outtextxy(midx+200, cury, &(play_time)[0]);

		if (game_mode < GameMode::NMODE-1) {
			cury += 30;
			settextjustify(LEFT_TEXT, CENTER_TEXT);
			outtextxy(midx-200, cury, "Best time:");

			settextjustify(RIGHT_TEXT, CENTER_TEXT);
			outtextxy(midx+200, cury, &(best_time)[0]);
		}

		cury += 60;

		Button menu_butt(100, 30, midx - 70, cury, "MENU");
		Button restart_butt(100, 30, midx + 70, cury, "RESTART");


		menu_butt.draw();
		restart_butt.draw();

		while (1) {
			if (menu_butt.checkHover() == Button::CLICKED) return RETURN;
			if (restart_butt.checkHover() == Button::CLICKED) return RESTART;
		}
	}

	int newGameWarning() {
		clearmouseclick(WM_LBUTTONDOWN);
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
			if (yes.checkHover() == Button::CLICKED) return CONTINUE;
			if (no.checkHover() == Button::CLICKED) return NEW;
			if (return_butt.checkHover() == Button::CLICKED) return RETURN;
		}
	}

	int resetRankWarning() {
		clearmouseclick(WM_LBUTTONDOWN);
		char *announce = "The playing history will be cleared.";
		int midx = WINDOW_WIDTH/2, midy = WINDOW_HEIGHT/2;

		char *question = "Are you sure you want to proceed?";

		int pos_y = midy + textheight(announce) + textheight(question) + 20;
		Button yes(60, 30, midx - 50, pos_y, "YES");

		Button no(60, 30, midx + 50, pos_y, "NO");

		int width = 500, height = 500;
		pos_y += no.getHeight() + 10;
		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, midx-width/2, midy-textheight(announce) - 10, midx+width/2, pos_y);
		//PRINT CONTENT
		setbkcolor(MyColor::WINDOW_BG);
		setcolor(MyColor::WINDOW_TEXT);
		outtextxy(midx, midy, announce);
		outtextxy(midx, midy + textheight(announce), question);
		yes.draw();
		no.draw();

		while (1) {
			if (yes.checkHover() == Button::CLICKED) return CONTINUE;
			if (no.checkHover() == Button::CLICKED) return RETURN;
		}
	}
}

#endif 