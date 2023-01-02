#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "constants.h"
#include <graphics.h>
#include <bits/stdc++.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

class Button {
	private:
		int left, top, right, bot;
		string content;

	public:
		static const int CLICKED = 1;

		Button(int width = 0, int height = 0, int x = 0, int y = 0, string _content = ""): 
			left(x), top(y), content(_content) {
				right = left + width;
				bot = top + height;

				int x_offset = (right-left+1)>>1, y_offset = (bot-top+1)>>1;
				left -= x_offset, right -= x_offset;
				bot -= y_offset, top -= y_offset;
			}

		int getHeight() {return bot-top;}

		bool contain(int x, int y) {
			return x >= left && x <= right && y >= top && y <= bot;
		}

		bool checkHover(int color = MyColor::BUTTON_HOVER, int text_color = MyColor::BUTTON) {
			if (!contain(mousex(), mousey())) return false;
			draw(color, text_color);
			do {
				while (ismouseclick(WM_LBUTTONDOWN)) {
					int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
					if (contain(x, y)) {
						bool played = PlaySound(TEXT("assets\\click.wav"), NULL, SND_FILENAME|SND_ASYNC);
						return CLICKED;
					}
				}
			} while (contain(mousex(), mousey()));

			draw(text_color, color);
			return false;
		}

		void updateContent(int color = MyColor::BUTTON, int text_color = MyColor::BUTTON_HOVER) {
			setbkcolor(color);
			setcolor(text_color);
			SetTextStyle(BOLD_FONT, HORIZ_DIR, 2);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			int width = textwidth(&content[0]);
			int height = textheight(&content[0]);
			outtextxy((left+right)>>1, (top+bot+height/2)>>1, &content[0]);			
		}
		
		void draw(int color = MyColor::BUTTON, int text_color = MyColor::BUTTON_HOVER, bool has_border = true) {
			setfillstyle(SOLID_FILL, color);
			bar(left, top, right, bot);

			if (has_border) {
				setcolor(text_color);
				rectangle(left, top, right, bot);
			}

			updateContent(color, text_color);
		}

		void setContent(string new_content) {
			content = new_content;
		}
};

#endif