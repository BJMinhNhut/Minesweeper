#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <graphics.h>
#include <bits/stdc++.h>
using namespace std;

class Button {
	private:
		static const int MENU_HEIGHT = 40, MENU_WIDTH = 200;
		int left, top, right, bot;
		char *content;

	public:
		Button(int l = 0, int t = 0, char *_content = ""): 
			left(l), top(t), content(_content) {
				right = left + MENU_WIDTH;
				bot = top + MENU_HEIGHT;

				int x_offset = (right-left+1)>>1, y_offset = (bot-top+1)>>1;
				left -= x_offset, right -= x_offset;
				bot -= y_offset, top -= y_offset;
			}

		int getHeight() {return bot-top;}

		bool isClicked(int x, int y) {
			return x >= left && x <= right && y >= top && y <= bot;
		}

		void draw(int first_color = BLACK, int second_color = BLACK, int text_color = WHITE, bool has_border = true) {
			if (has_border) {
				setcolor(WHITE);
				rectangle(left-1, top-1, right, bot);
			}

			setfillstyle(SOLID_FILL, first_color);
			bar(left, top, right, bot);

			setbkcolor(first_color);
			setcolor(text_color);
			settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			int width = textwidth(content);
			int height = textheight(content);
			outtextxy((left+right)>>1, (top+bot+height/2)>>1, content);
			setbkcolor(BLACK);
		}
};

#endif