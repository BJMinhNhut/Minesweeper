#ifndef _INPUT_H_
#define _INPUT_H_

#include <graphics.h>
#include "button.h"
#include "constants.h"

class InputBox {
	int posX, posY;
	int val, min_val, max_val;
	char *title;
	Button inc_1, dec_1, inc_5, dec_5;

	void update() {
		char display_char[20];
		sprintf(display_char, "%03d", val);
		setcolor(MyColor::TEXT);
		setbkcolor(MyColor::GAME_BG);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		outtextxy(posX, posY+27, display_char);
	}

public:
	static const int UPDATED = 1;

	InputBox(char *_title = "", int x = 0, int y = 0, int default_val = 0, int minV = 0, int maxV = 0): 
		title(_title), posX(x), posY(y), val(default_val),  min_val(minV), max_val(maxV) {
		inc_1 = Button(30, 30, posX+50+25, posY+5+15, "+1");
		dec_1 = Button(30, 30, posX-50-25, posY+5+15, "-1");
		inc_5 = Button(30, 30, posX+50+60, posY+5+15, "+5");
		dec_5 = Button(30, 30, posX-50-60, posY+5+15, "-5");
	}

	void display() {
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		settextjustify(CENTER_TEXT, BOTTOM_TEXT);
		setcolor(MyColor::TEXT);
		setbkcolor(MyColor::WINDOW_BG);
		outtextxy(posX, posY, title);

		drawFrame(MyColor::GAME_BG, MyColor::BORDER, posX-50, posY+5 , posX+50, posY+35);
		update();

		inc_1.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
		dec_1.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
		inc_5.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
		dec_5.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
	}	

	bool checkHover() {
		bool updated = false;
		while (inc_1.checkHover(MyColor::ADJUST_BUTTON, MyColor::GAME_BG) == Button::CLICKED) {
			updated = true;
			val = min(val+1, max_val);
			update();
		}
		while (dec_1.checkHover(MyColor::ADJUST_BUTTON, MyColor::GAME_BG) == Button::CLICKED) {
			updated = true;
			val = max(val-1, min_val);
			update();
		}

		while (inc_5.checkHover(MyColor::ADJUST_BUTTON, MyColor::GAME_BG) == Button::CLICKED) {
			updated = true;
			val = min(val+5, max_val);
			update();
		}

		while (dec_5.checkHover(MyColor::ADJUST_BUTTON, MyColor::GAME_BG) == Button::CLICKED) {
			updated = true;
			val = max(val-5, min_val);
			update();
		}

		return updated;
	}

	int getVal() {
		return val;
	}
};

#endif