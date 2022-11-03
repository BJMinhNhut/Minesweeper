#ifndef _MENU_H_
#define _MENU_H_

#include "button.h"
#include "constants.h"
#include "window.h"
#include <bits/stdc++.h>

class Menu {
		void runGame(Game &game) {
			setbkcolor(MyColor::GAME_BG);
			cleardevice();
			clearmouseclick(WM_LBUTTONDOWN);
			clearmouseclick(WM_RBUTTONDOWN);
			
			int cnt = 0;
			game.display();
			game.saveGame();
			while (game.onGoing()) {
				game.checkClickAndUpdate();
			}

			game.display();

			setcolor(MyColor::TEXT);
			setbkcolor(MyColor::GAME_BG);
			settextjustify(CENTER_TEXT, BOTTOM_TEXT);
			outtextxy(WINDOW_WIDTH/2, WINDOW_HEIGHT-10, "Press any key to go back to main menu...");
			getch();
		}

		void genNewGame(int game_mode) {
			int height, width, bomb; tie(height, width, bomb) = GameMode::PROPERTIES[game_mode]; 
			Game newGame(height, width, bomb);
			newGame.genRandomBombMap();

			runGame(newGame);
		}

		void clearMenu() {
			setfillstyle(SOLID_FILL, MyColor::GAME_BG);
			bar(0, WINDOW_HEIGHT/2 - 50, WINDOW_WIDTH, WINDOW_HEIGHT);
		}

		void optionScreen() {
			clearMenu();
			clearmouseclick(WM_LBUTTONDOWN);
			int midx = WINDOW_WIDTH/2, midy = WINDOW_HEIGHT/2;
			
			//New Game Button
			int curY = midy;
			vector<Button> mode_butt(GameMode::NMODE);
			for(int mode_id = 1; mode_id < GameMode::NMODE; ++mode_id) {
				mode_butt[mode_id] = Button(midx, curY, GameMode::CAPTION[mode_id]);
				mode_butt[mode_id].draw();
				curY += mode_butt[mode_id].getHeight() + 20;
			}

			while (1) {
				while (!ismouseclick(WM_LBUTTONDOWN)) {delay(1);}
				int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
				for(int mode_id = 1; mode_id < GameMode::NMODE; ++mode_id) {
					if (mode_butt[mode_id].isClicked(x, y)) {
						genNewGame(mode_id);
						return;
					}
				}
			}
		}

	public:
		void display() {
			clearMenu();
			clearmouseclick(WM_LBUTTONDOWN);

			int midx = WINDOW_WIDTH/2, midy = WINDOW_HEIGHT/2;
			
			//New Game Button
			int curY = midy;
			Button newGameButt(midx, curY, "New game");
			newGameButt.draw();

			//Exit Game Button
			curY += newGameButt.getHeight() + 20;
			Button exitGameButt(midx, curY, "Exit");
			exitGameButt.draw();

			while (!ismouseclick(WM_LBUTTONDOWN)) {delay(1);}
			int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
			if (newGameButt.isClicked(x, y)) {
				Game old_game;
				if (old_game.foundValidBackupFile()) {
					Window::newGameWarning();
					runGame(old_game);
				} else optionScreen();
			} else if (exitGameButt.isClicked(x, y)) {
				exit(EXIT_SUCCESS);
			}
		}
};

#endif