#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include <graphics.h>
#include <time.h>
using namespace std;

class ScoreBoard {
	private:
		int posX, posY;
		int height, width;
		char *title; //startTime: depend on the time player start game (not program)

		void init_text(int font, int font_size) {
			settextstyle(font, HORIZ_DIR, font_size);
			settextjustify(CENTER_TEXT, BOTTOM_TEXT);
			setbkcolor(MyColor::GAME_BG);
			setcolor(MyColor::TEXT);
		}

	public:
		ScoreBoard(char *_title = "", int x = 0, int y = 0, int h = 0, int w = 0): posX(x), posY(y), title(_title), height(h), width(w)  {}

		void display(char *content, int font, int font_size) {
			drawFrame(MyColor::GAME_BG, MyColor::BORDER, posX - width/2, posY - height/2, posX + (width+1)/2, posY + (height+1)/2);
			line(posX - width/2, posY, posX + (width+1)/2, posY);
			init_text(font, font_size);
			outtextxy(posX, posY - 10, title);
			outtextxy(posX, posY + 30, content);
		} 

		void update(char *content, int font, int font_size) {
			setfillstyle(SOLID_FILL, MyColor::GAME_BG);
			// bar(posX - textwidth(content)/2, posY + 30 - textheight(content)/2, posX + textwidth(content)/2, posY + 30 + textheight(content)/2);
			init_text(font, font_size);
			outtextxy(posX, posY + 30, content);
		}
};

#endif