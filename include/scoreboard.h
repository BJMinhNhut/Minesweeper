#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include <graphics.h>
#include <time.h>
using namespace std;

class ScoreBoard {
	private:
		int posX, posY;
		int startTime, backupTime, num_bomb; //startTime: depend on the time player start game (not program)

		int getMin(int t) {
			return t/60;
		}

		int getSec(int t) {
			return t%60;
		}

	public:
		ScoreBoard(int x = 0, int y = 0, int sT = 0, int bomb = 0, int bk = 0): posX(x), posY(y), startTime(sT), num_bomb(bomb), backupTime(bk) {}

		void setBackupTime(int val)	 {backupTime = val;}

		int getPlayTime() {return clock()/1000 - startTime + backupTime;}

		int getHeight() {
			char display_char[30];
			sprintf(display_char, "Temp");
			settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			return textheight(display_char);
		}

		void display(int font, int font_size) {
			int total_time = getPlayTime();
			char display_char[30];
			sprintf(display_char, "Time: %02d:%02d  Bomb: %03d", getMin(total_time), getSec(total_time), num_bomb);
			setfillstyle(SOLID_FILL, MyColor::GAME_BG);
			settextstyle(font, HORIZ_DIR, font_size);
			settextjustify(CENTER_TEXT, BOTTOM_TEXT);
			setbkcolor(MyColor::GAME_BG);
			setcolor(MyColor::TEXT);
			int height = textheight(display_char);
			int width = textwidth(display_char);
			bar(posX - width/2, posY - height, posX + (width+1)/2, posY);
			outtextxy(posX, posY, display_char);
		} 
};

#endif