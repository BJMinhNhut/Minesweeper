#ifndef _RANKING_H_
#define _RANKING_H_

#include "constants.h"
#include "button.h"
#include <graphics.h>

namespace Ranking {
	const int NRANK = 5;
	int data[GameMode::NMODE][NRANK+1];

	void loadRanking() {
		ifstream rank_file(GameFile::RANK);
		memset(data, -1, sizeof data);
		for(int i = 1; i < GameMode::NMODE; ++i) {
			for (int j = 1; j <= NRANK; ++j) {
				if (!(rank_file >> data[i][j])) return;
			}
		} 
	}

	std::tuple<int, int, int, int> getPos(int i, int j) {
		
	}
	
	void displayRanking() {
		clearmouseclick(WM_LBUTTONDOWN);

		drawFrame(MyColor::WINDOW_TITLE, MyColor::BORDER, 200, WINDOW_HEIGHT/2 - 110, 1000, WINDOW_HEIGHT/2 - 70);
		setcolor(WHITE);
		setbkcolor(MyColor::WINDOW_TITLE);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		outtextxy(600, WINDOW_HEIGHT/2-85, "HALL OF FAME");

		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, 200, WINDOW_HEIGHT/2 - 70, 1000, WINDOW_HEIGHT/2 + 250);

		Button returnButt(100, 30, WINDOW_WIDTH/2, WINDOW_HEIGHT - 50, "RETURN");
		returnButt.draw();

		while (1) {
			if (returnButt.checkHover() == Button::CLICKED) return;
		}
	}
}

#endif 