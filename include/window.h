#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "constants.h"
#include "button.h"
#include <graphics.h>

namespace Window {
	void newGameWarning() {
		setbkcolor(RED);
		outtextxy(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, "SURE? Press any key to run new game...");

		getch();
	}
}

#endif 