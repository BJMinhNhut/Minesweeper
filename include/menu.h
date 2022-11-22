#ifndef _MENU_H_
#define _MENU_H_

#include "button.h"
#include "constants.h"
#include "window.h"
#include "input.h"
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

			// game.display();

			int choice = Window::endGameAnnouncement(game.win());
			if (choice == Window::RESTART) {
				Game newGame(game.getHeight(), game.getWidth(), game.getNumBomb());
				newGame.genRandomBombMap();
				runGame(newGame);
			}
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

		void customScreen() {
			clearMenu();
			clearmouseclick(WM_LBUTTONDOWN);

			InputBox height_box("Height", WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - 20, DEFAULT_SIZE, MIN_SIZE, MAX_SIZE);
			InputBox width_box("Width", WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 50, DEFAULT_SIZE, MIN_SIZE, MAX_SIZE);
			InputBox bomb_box("Bombs", WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 120, DEFAULT_BOMB, MIN_BOMB, MAX_BOMB);
			Button go_butt(100, 30, WINDOW_WIDTH/2 + 60, WINDOW_HEIGHT/2 + 210, "GO");
			Button return_butt(100, 30, WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT/2 + 210, "RETURN");

			drawFrame(MyColor::WINDOW_TITLE, MyColor::BORDER, 200, WINDOW_HEIGHT/2 - 110, 1000, WINDOW_HEIGHT/2 - 70);
			setcolor(WHITE);
			setbkcolor(MyColor::WINDOW_TITLE);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			outtextxy(600, WINDOW_HEIGHT/2-85, "CUSTOMIZE SETTINGS");

			drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, 200, WINDOW_HEIGHT/2 - 70, 1000, WINDOW_HEIGHT/2 + 250);

			height_box.display();
			width_box.display();
			bomb_box.display();
			return_butt.draw();
			go_butt.draw();

			while (1) {
				if (return_butt.checkHover() == Button::CLICKED) return;
				if (go_butt.checkHover() == Button::CLICKED) {
					Game newGame(height_box.getVal(), width_box.getVal(), bomb_box.getVal());
					newGame.genRandomBombMap();
					runGame(newGame);
					return;
				}
				if (height_box.checkHover() == InputBox::UPDATED) continue;
				if (width_box.checkHover() == InputBox::UPDATED) continue;
				if (bomb_box.checkHover() == InputBox::UPDATED) continue;
			}
		}

		void optionScreen() {
			clearMenu();
			clearmouseclick(WM_LBUTTONDOWN);
			int midx = WINDOW_WIDTH/2, midy = WINDOW_HEIGHT/2;
			
			//New Game Button
			int curY = midy;
			vector<Button> mode_butt(GameMode::NMODE);
			for(int mode_id = 0; mode_id < GameMode::NMODE; ++mode_id) {
				mode_butt[mode_id] = Button(OPTION_WIDTH, OPTION_HEIGHT, midx, curY, GameMode::CAPTION[mode_id]);
				mode_butt[mode_id].draw();
				curY += mode_butt[mode_id].getHeight() + 10;
			}

			while (1) {
				if (mode_butt[0].checkHover() == Button::CLICKED) {customScreen(); return;}
				for(int mode_id = 1; mode_id < GameMode::NMODE; ++mode_id) {
					if (mode_butt[mode_id].checkHover() == Button::CLICKED) {
						genNewGame(mode_id);
						clearmouseclick(WM_LBUTTONDOWN);
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
			Button newGameButt(MENU_WIDTH, MENU_HEIGHT, midx, curY, "New game");
			newGameButt.draw();

			//Exit Game Button
			curY += newGameButt.getHeight() + 10;
			Button exitGameButt(MENU_WIDTH, MENU_HEIGHT, midx, curY, "Exit");
			exitGameButt.draw();

			while (1) {
				bool clicked_button = false;

				if (newGameButt.checkHover() == Button::CLICKED) {
					clicked_button = true;
					Game old_game;
					if (old_game.foundValidBackupFile()) {
						clearMenu();
						int choice = Window::newGameWarning();
						
						if (choice == Window::CONTINUE) runGame(old_game);
						else if (choice == Window::RETURN) {display(); return;}
						else optionScreen();

					} else optionScreen();

				} else if (exitGameButt.checkHover() == Button::CLICKED) {
					clicked_button = true;
					exit(EXIT_SUCCESS);
				}

				if (clicked_button) break;
			}
		}
};

#endif