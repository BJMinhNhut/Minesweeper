#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "constants.h"
#include "button.h"
#include <graphics.h>

namespace Window {
	const bool CONTINUE = 1, NEW = 0; 
	bool newGameWarning() {
		setbkcolor(MyColor::GAME_BG);
		char *announce = "There is an old session not finished!";
		int midx = WINDOW_WIDTH/2, midy = WINDOW_HEIGHT/2;
		outtextxy(midx, midy, announce);

		char *question = "Do you want to continue?";
		outtextxy(midx, midy + textheight(announce), question);

		int pos_y = midy + textheight(announce) + textheight(question) + 30;
		Button yes(midx, pos_y, "YES");
		yes.draw();

		pos_y += yes.getHeight() + 10;
		Button no(WINDOW_WIDTH/2, pos_y, "NO");
		no.draw();
		
		while (1) if (ismouseclick(WM_LBUTTONDOWN)) {
			int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
			if (yes.isClicked(x, y)) return CONTINUE;
			if (no.isClicked(x, y)) return NEW;
		}
	}
}

#endif 