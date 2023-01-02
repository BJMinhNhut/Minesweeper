#ifndef _ABOUT_H_
#define _ABOUT_H_

#include "constants.h"
#include "button.h"
#include "window.h"
#include <graphics.h>
#include <algorithm>

namespace About {

	void printTitle() {
		int midx = WINDOW_WIDTH/2;
		int midy = WINDOW_HEIGHT/2;

		settextjustify(CENTER_TEXT, CENTER_TEXT);
		SetTextStyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(MyColor::TEXT);
		setbkcolor(MyColor::WINDOW_BG);
		outtextxy(midx, midy-170, "ABOUT");
	}

	void loadText() {
		ifstream about_file("assets\\about.txt");
		int cury = WINDOW_HEIGHT/2-100;
		string cur_line;
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		setcolor(MyColor::TEXT);
		while (getline(about_file, cur_line)) {
			outtextxy(WINDOW_WIDTH/2-350, cury, &cur_line[0]);
			cury += textheight(&cur_line[0]);
		}
	}
	
	void display() {
		clearmouseclick(WM_LBUTTONDOWN);
		setbkcolor(MyColor::GAME_BG);
		cleardevice();
		Button returnButt(100, 30, WINDOW_WIDTH/2, WINDOW_HEIGHT - 50, "RETURN");
		
		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, WINDOW_WIDTH/2-400, WINDOW_HEIGHT/2-200, WINDOW_WIDTH/2+400, WINDOW_HEIGHT/2-150);
		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, WINDOW_WIDTH/2-400, WINDOW_HEIGHT/2-150, WINDOW_WIDTH/2+400, WINDOW_HEIGHT/2+250);

		loadText();

		printTitle();

		returnButt.draw();

		while (1) {
			if (returnButt.checkHover() == Button::CLICKED) return;
		}
	}
}

#endif