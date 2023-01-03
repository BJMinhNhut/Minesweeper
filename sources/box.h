#ifndef _BOX_H_
#define _BOX_H_

#include "constants.h"
#include <graphics.h>

#define MASK(s) (1ll<<(s))
#define BIT(s, i) (((s)>>(i))&1)

class Box {
	private:
		static const int HIDDEN = 0, REVEALED = 1, FLAGGED  = 2;
		int left, top, right, bot;
		int adj_bomb_num;
		bool has_bomb;
		int display_status;

		int getColorOnScale(int val) {
			static const int scaleColor[8] = {MyColor::ONE, MyColor::TWO, MyColor::THREE, MyColor::FOUR,
												MyColor::FIVE, MyColor::SIX, MyColor::SEVEN, MyColor::EIGHT};
			return scaleColor[val-1]; 
		}

		void printNum(int num) {
			char display_num[4];
			sprintf(display_num, "%d", num);
			setbkcolor(MyColor::REVEAL);
			setcolor(getColorOnScale(num));
			SetTextStyle(getFontType(), HORIZ_DIR, getFontSize());
			settextjustify(CENTER_TEXT, CENTER_TEXT);

			int height = textheight(display_num);
			outtextxy((left+right)>>1, (top+bot+height/2)>>1, display_num);
			setbkcolor(BLACK);
		}

		void printChar(int bg_color, int color, char *display_obj) {
			setbkcolor(bg_color);
			setcolor(color);
			SetTextStyle(getFontType(), HORIZ_DIR, getFontSize());
			settextjustify(CENTER_TEXT, CENTER_TEXT);

			int height = textheight(display_obj);
			outtextxy((left+right)>>1, (top+bot+height/2)>>1, display_obj);
			setbkcolor(BLACK);
		}

		void drawBox(int color = 0) {
			setfillstyle(SOLID_FILL, color);
			bar(left, top, right, bot);
			setcolor(MyColor::BORDER);
			rectangle(left, top, right, bot);
		}

		void drawImageBox(const char *image_link) {
			readimagefile(image_link, left, top, right, bot);
			setcolor(MyColor::BORDER);
			rectangle(left, top, right, bot);
		}


	public:
		Box(int l = 0, int t = 0, int r = 0, int b = 0, bool _has_bomb = 0): 
			left(l), top(t), right(r), bot(b), has_bomb(_has_bomb), adj_bomb_num(0), display_status(0) {}

		void setPos(int l, int t, int r, int b) {left = l, right = r, top = t, bot = b;}

		int getTop() {return top;}
		int getLeft() {return left;}

		bool hidden() {return display_status == HIDDEN;}
		bool isFlagged() {return display_status == FLAGGED;}

		int getStatus() {return display_status;}
		void setStatus(int val) {display_status = val;}

		void setBomb(bool state) {has_bomb = state;}
		bool hasBomb() {return has_bomb;}

		void setAdj(int val) {adj_bomb_num = val;}
		int getAdjBomb() {return adj_bomb_num;} 

		int getFontSize() {
			if (bot-top > 40) return 3;
			else if (bot-top > 25) return 2;
			else if (bot-top >= 20) return 1;
			else return 4;
		}

		int getFontType() {
			if (bot-top < 15) return SMALL_FONT;
			else return BOLD_FONT;
		}

		bool isClicked(int x, int y) {
			return x >= left && x <= right && y >= top && y <= bot;
		}

		bool checkHover() {
			if (!hidden() || !isClicked(mousex(), mousey())) return false;
			drawBox(MyColor::BOX_HOVER);
			return true;
		}

		void draw() {
			#ifdef _DEBUG_BOX_COLOR_
				static int cnt = 0;
				drawBox(WHITE);
				printNum((cnt++)%8+1);
			#else
				if (hidden()) drawBox(MyColor::HIDDEN);
				else if (isFlagged()) drawImageBox(Image::FLAG);
				else if (hasBomb()) drawImageBox(Image::BOMB_INACTIVE);
				else {
					drawBox(MyColor::REVEAL);
					if (getAdjBomb()) printNum(adj_bomb_num);
				}
			#endif
		}

		void explode() {
			drawImageBox(Image::BOMB);
		}

		void drawCorrectFlag() {
			drawImageBox(Image::FLAG_CORRECT);
		}

		void drawIncorrectFlag() {
			drawImageBox(Image::FLAG_INCORRECT);
		}

		int toggleFlag() {
			assert(display_status != REVEALED);
			if (display_status == HIDDEN) display_status = FLAGGED;
			else display_status = HIDDEN;
			draw();
			return display_status == HIDDEN ? -1 : 1;
		}

		void revealBox() {
			display_status = REVEALED;
			draw();
		}

		int encode() {
			return adj_bomb_num + (has_bomb<<4) + (display_status<<5);
		}
};

void decode(int val, Box &ans) {
	ans.setAdj(val&(MASK(4)-1));
	ans.setBomb(BIT(val, 4));
	ans.setStatus(val >> 5);
}
#endif