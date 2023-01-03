#ifndef _INPUT_H_
#define _INPUT_H_

#include <graphics.h>
#include "button.h"
#include "constants.h"

class InputBox {
	int posX, posY;
	int val, min_val, max_val;
	char *title;
	Button main_box;
	Button inc_1, dec_1, inc_5, dec_5;

	string getStringVal() {
		string ans = to_string(val);
		while (ans.size() < 3) ans = '0' + ans;
		return ans;
	}

	void edit() {
		while (kbhit()) getch();
		rectangle(posX-50, posY+20-15, posX+50, posY+20+15);
		while (1) {
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
				if (!main_box.contain(x, y)) break;
			}

			bool updated = false;
			if (kbhit()) {
				int ch = getch();
				if (isdigit(ch)) {
					val = min(max_val, val*10 + (ch-'0'));
					updated = true;
				}
				if (ch == 8) {
					val = val/10;
					updated = true;
				}
				if (ch == '\r') break;
			}

			if (updated) {
				main_box.setContent(getStringVal());
				main_box.updateContent(WHITE, MyColor::WINDOW_BG);
			}
		}
		main_box.draw(MyColor::WINDOW_BG, WHITE);
		while (main_box.contain(mousex(), mousey())) {}

		val = max(min_val, val);
		main_box.setContent(getStringVal());
		main_box.updateContent(MyColor::WINDOW_BG, WHITE);
	}

	bool checkButton(Button &butt, int delta) {
		bool updated = false;
		while (butt.checkHover(MyColor::ADJUST_BUTTON, MyColor::GAME_BG, 0) == Button::CLICKED) {
			updated = true;
			val = max(min_val, min(val+delta, max_val));

			main_box.setContent(getStringVal());
			main_box.updateContent(MyColor::WINDOW_BG, WHITE);
		}

		return updated;
	}

public:
	static const int UPDATED = 1;

	InputBox(char *_title = "", int x = 0, int y = 0, int default_val = 0, int minV = 0, int maxV = 0): 
		title(_title), posX(x), posY(y), val(default_val),  min_val(minV), max_val(maxV) {
		main_box = Button(100, 30, posX, posY+20, getStringVal());
		inc_1 = Button(30, 30, posX+50+25, posY+5+15, "+1");
		dec_1 = Button(30, 30, posX-50-25, posY+5+15, "-1");
		inc_5 = Button(30, 30, posX+50+60, posY+5+15, "+5");
		dec_5 = Button(30, 30, posX-50-60, posY+5+15, "-5");
	}

	void display() {
		SetTextStyle(BOLD_FONT, HORIZ_DIR, 2);
		settextjustify(CENTER_TEXT, BOTTOM_TEXT);
		setcolor(MyColor::TEXT);
		setbkcolor(MyColor::WINDOW_BG);
		outtextxy(posX, posY, title);

		main_box.draw(MyColor::WINDOW_BG, WHITE);
		inc_1.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
		dec_1.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
		inc_5.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
		dec_5.draw(MyColor::GAME_BG, MyColor::ADJUST_BUTTON);
	}	

	bool checkHover() {
		bool updated = false;
		if (main_box.checkHover(WHITE, MyColor::WINDOW_BG) == Button::CLICKED) {
			edit();
			updated = true;
		} 
		updated |= checkButton(inc_1, 1);
		updated |= checkButton(dec_1, -1);
		updated |= checkButton(inc_5, 5);
		updated |= checkButton(dec_5, -5);
		return updated;
	}

	void updateMax(int max_val) {
		this->max_val = max_val;
		val = min(val, max_val);
		main_box.setContent(getStringVal());
		main_box.updateContent(MyColor::WINDOW_BG, WHITE);
	}

	int getVal() {
		return val;
	}
};

#endif