#ifndef _BOMB_H_
#define _BOMB_H_

#include <bits/stdc++.h>
#include <graphics.h>
#include "box.h"
#include "scoreboard.h"
#include "constants.h"
#include "button.h"
#include "window.h"
#include "ranking.h"
using namespace std;

class Game {
	private:

		static const int ON_GOING = 0, LOSE_GAME = 1, WIN_GAME = 2;
		vector<vector<Box>> bombMap;
		int height, width, num_bomb, num_flag;
		int start_time, backup_time;
		int status;
		pair<int, int> lastClick;
		ScoreBoard time_board, flag_board;
		Button restart_butt, menu_butt;
		int game_mode;

		int getBoxSize() {
			return min({40, (WINDOW_HEIGHT-MAP_PADDING)/height, GAME_WIDTH/width});
		}

		pair<int, int> getBombPos(int x, int y, bool clicked = false) {
			int box_size = getBoxSize();
			pair<int, int> ans = make_pair(-1, -1);
			for(int step = height/2; step > 0; step >>= 1) {
				while (ans.first+step < height && bombMap[ans.first+step][0].getTop() <= y) ans.first += step;
			}
			for(int step = width/2; step > 0; step >>= 1) {
				while (ans.second+step < width && bombMap[0][ans.second+step].getLeft() <= x) ans.second += step;
			}
			if (DEBUG_MOUSE && clicked) cerr << "Clicked " << ans.first << ' ' << ans.second << '\n';
			return ans;
		}

		bool validPos(int x, int y) {
			return x >= 0 && x < height && y >= 0 && y < width;
		}

		void calcAdjTable() {
			for(int i = 0; i < height; ++i) for (int j = 0; j < width; ++j) {
				int cnt = 0;
				for(int d = 0; d < 8; ++d) {
					int x = i + NEXTX[d], y = j + NEXTY[d];
					if (!validPos(x, y)) continue;
					cnt += bombMap[x][y].hasBomb();
				}
				bombMap[i][j].setAdj(cnt);
			}
		}

		tuple<int, int, int, int> getPosOfBox(int i, int j) {
			int box_size = getBoxSize();			
			int base_height = WINDOW_HEIGHT/2 - box_size*height/2;
			int base_width = (GAME_WIDTH - box_size*width + 2*MAP_PADDING)/2;
			return make_tuple(base_width + j*box_size, base_height + i*box_size, base_width + (j+1)*box_size, base_height + (i+1)*box_size);
		}

		bool canGoOn(int x, int y) {
			return validPos(x, y) && !bombMap[x][y].hasBomb() && bombMap[x][y].hidden();
		}

		void revealAreaStartFrom(int startX, int startY) {
			queue<pair<int, int>> q;
			q.push(make_pair(startX, startY));

			while (q.size()) {
				int curX, curY; tie(curX, curY) = q.front(); q.pop();
				bombMap[curX][curY].revealBox();
				if (bombMap[curX][curY].getAdjBomb() > 0) continue;
				for(int dir = 0; dir < 8; ++dir) {
					int newX = curX + NEXTX[dir], newY = curY + NEXTY[dir];
					if (canGoOn(newX, newY)) {
						bombMap[newX][newY].revealBox();
						q.push(make_pair(newX, newY));
					}
				}
			}
		}

		void checkWinGame() {
			for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) {
				if ((bombMap[i][j].hidden() || bombMap[i][j].isFlagged()) && !bombMap[i][j].hasBomb()) return;
			}
			status = WIN_GAME;
		}

		int cntFlagged(int bombX, int bombY) {
			int ans = 0;
			for(int dir = 0; dir < 8; ++dir) {
				int newX = bombX+NEXTX[dir], newY = bombY+NEXTY[dir];
				if (validPos(newX, newY) && bombMap[newX][newY].isFlagged()) ++ans; 
			}
			return ans;
		}

		bool enoughFlagged(int bombX, int bombY) {
			return cntFlagged(bombX, bombY) == bombMap[bombX][bombY].getAdjBomb();
		}

		int getDelayTime(int cnt) {
			if (cnt < 10) return 70;
			if (cnt < 20) return 20;
			if (cnt < 40) return 10;
			if (cnt < 60) return 5;
			return 0;
		}

		void loseGameBFS(int bombX, int bombY) {
			vector<vector<bool>> visited(height, vector<bool>(width, 0));
			queue<pair<int, int>> q;
			q.push(make_pair(bombX, bombY));

			int cnt = 0;

			while (q.size()) {
				int x,y; tie(x, y) = q.front(); q.pop();

				if (bombMap[x][y].isFlagged()) {
					if (bombMap[x][y].hasBomb()) bombMap[x][y].drawCorrectFlag();
					else bombMap[x][y].drawIncorrectFlag();
				} else if (bombMap[x][y].hasBomb() && (x != bombX || y != bombY)) 
						bombMap[x][y].revealBox();

				if (bombMap[x][y].hasBomb()) Delay(getDelayTime(++cnt));

				for(int dir = 0; dir < 8; ++dir) {
					int nxt_x = x + NEXTX[dir], nxt_y = y + NEXTY[dir];
					if (!validPos(nxt_x, nxt_y) || visited[nxt_x][nxt_y]) continue;
					q.push(make_pair(nxt_x, nxt_y));
					visited[nxt_x][nxt_y] = true;
				}
			}
			vector<vector<bool>>().swap(visited);
		}

		bool openBox(int bombX, int bombY) {
			if (bombMap[bombX][bombY].hasBomb()) {
				//EXPLODE
				PlaySound(MAKEINTRESOURCE(EXPLODE), NULL, SND_RESOURCE|SND_ASYNC);
				status = LOSE_GAME;
				bombMap[bombX][bombY].explode();
				loseGameBFS(bombX, bombY);
				return true;
			} else if (bombMap[bombX][bombY].hidden()) {
				//REVEAL BOX
				revealAreaStartFrom(bombX, bombY);
				if (DEBUG_MOUSE) for(int j = 0; j < width; ++j) for(int i = 0; i < height; ++i) cerr << bombMap[i][j].hidden() << " \n"[i == height-1];
				return true;
			}
			return false;
		}

		bool checkLeftMouseClick() {
			int x, y; 
			int bombX, bombY; 
			getmouseclick(WM_LBUTTONDOWN, x, y);
			tie(bombX, bombY) = getBombPos(x, y, true);	// Get box position

			if (!validPos(bombX, bombY)) {
				if (DEBUG_MOUSE) cerr << "Outside Box\n";
				return false;
			}

			if (bombMap[bombX][bombY].hidden()) { //OPEN BOX
				return openBox(bombX, bombY);
			} else if (bombMap[bombX][bombY].isFlagged()) {
				if (DEBUG_MOUSE) cerr << "Cannot open flagged box";
				return false;
			} else { 
				if (enoughFlagged(bombX, bombY)) {
					// OPEN SURROUND
					bool result = false;
					for(int dir = 0; dir < 8; ++dir) {
						int newX = bombX + NEXTX[dir], newY = bombY + NEXTY[dir];
						if (!validPos(newX, newY) || bombMap[newX][newY].isFlagged()) continue;
						result |= openBox(newX, newY);
 					}
					return result;
				} else {
					if (DEBUG_MOUSE) cerr << "Not enough flagged\n";
					return false;
				}
			}
		}

		int getPlayTime() {return clock()/1000 - start_time + backup_time;}
		int getMin(int t) {return t/60;}
		int getSec(int t) {return t%60;}

		string getTimeString() {
			char ans[30];
			int play_time = getPlayTime();
			sprintf(ans, "%02d:%02d", getMin(play_time), getSec(play_time));
			return ans;
		}

		string getBombLeft() {
			char ans[30];
			sprintf(ans, "%04d", num_bomb - num_flag);
			return ans;
		}

		bool checkRightMouseClick() {
			int x, y; 
			int bombX, bombY; 
			getmouseclick(WM_RBUTTONDOWN, x, y);
			tie(bombX, bombY) = getBombPos(x, y, true);
			if (validPos(bombX, bombY) && (bombMap[bombX][bombY].hidden() || bombMap[bombX][bombY].isFlagged())) {
				num_flag += bombMap[bombX][bombY].toggleFlag(); 
				flag_board.update(&getBombLeft()[0], BOLD_FONT, 2);
				time_board.update(&getTimeString()[0], BOLD_FONT, 2);
				lastClick = make_pair(bombX, bombY);
				return true;
			} else if (DEBUG_MOUSE) cerr << "Outside Box\n";		
			return false;
		}

		void checkHover() {
			int x = mousex(), y = mousey();
			int bombX, bombY; tie(bombX, bombY) = getBombPos(x, y, false);
			static int lastX = -1, lastY = -1;
			if (lastX != bombX || lastY != bombY) {
				if (validPos(lastX, lastY)) bombMap[lastX][lastY].draw();
				if (validPos(bombX, bombY) && bombMap[bombX][bombY].checkHover()) {
					lastX = bombX, lastY = bombY;
				} else lastX = -1, lastY = -1;
			}
		}

		void updateGameTime() {
			ofstream time_file(GameFile::TIME);
			time_file << getPlayTime() << '\n';
			time_file.close();
		}

		void removeBackupFile() {
			ofstream game_file(GameFile::GAME), time_file(GameFile::TIME);
			game_file.clear();
			time_file.clear();
		}
	
	public:

		void initMap(int height, int width) {
			bombMap.assign(height, vector<Box>(width, Box()));
			
			for(int i = 0; i < height; ++i) 
			for(int j = 0; j < width; ++j) {
				int left, right, top, bot; tie(left, top, right, bot) = getPosOfBox(i, j);
				bombMap[i][j].setPos(left, top, right, bot);
			}
		}

		void initVar() {
			start_time = clock()/1000;
			time_board = ScoreBoard("TIME", WINDOW_WIDTH - (SCOREBOARD_WIDTH + 2*MAP_PADDING)/2, WINDOW_HEIGHT/2 - SCOREBOARD_HEIGHT/2 - 10, SCOREBOARD_HEIGHT, SCOREBOARD_WIDTH);
			flag_board = ScoreBoard("FLAGS", WINDOW_WIDTH - (SCOREBOARD_WIDTH + 2*MAP_PADDING)/2, WINDOW_HEIGHT/2 + SCOREBOARD_HEIGHT/2 + 10, SCOREBOARD_HEIGHT, SCOREBOARD_WIDTH);
			restart_butt = Button(SCOREBOARD_WIDTH, 30, WINDOW_WIDTH - (SCOREBOARD_WIDTH + 2*MAP_PADDING)/2, WINDOW_HEIGHT-100, "RESTART");
			menu_butt = Button(SCOREBOARD_WIDTH, 30, WINDOW_WIDTH - (SCOREBOARD_WIDTH + 2*MAP_PADDING)/2, WINDOW_HEIGHT-60, "MENU");
		}

		Game(int gm = -1, int h = DEBUG_HEIGHT, int w = DEBUG_WIDTH, int b = DEBUG_BOMB): height(h), width(w), num_bomb(b), status(ON_GOING), num_flag(0), game_mode(gm) {
			assert(num_bomb <= height*width && height <= 30 && width <= 30);
			backup_time = 0;
			initMap(height, width);
			initVar();
		}

		int getHeight() {return height;}
		int getWidth() {return width;}
		int getNumBomb() {return num_bomb;}
		bool onGoing() {return status == ON_GOING;}
		bool lose() {return status == LOSE_GAME;}
		bool win() {return status == WIN_GAME;}

		bool foundValidBackupFile() {
			/* Need to refactor this later */
			ifstream game_file(GameFile::GAME), time_file(GameFile::TIME);
			start_time = clock()/1000;
			if (!(time_file >> backup_time)) return false; 

			if (!(game_file >> game_mode >> height >> width >> num_bomb)) return false;

			if (!(num_bomb <= height*width && height <= 50 && width <= 50)) return false;
			initMap(height, width);

			for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) {
				int code; if (!(game_file >> code)) return false;
				decode(code, bombMap[i][j]);
				num_flag += bombMap[i][j].isFlagged();
			}
			game_file.close(), time_file.close();
			initVar();
			return true;
		}

		void genRandomBombMap() {
			srand(time(NULL));
			vector<pair<int, int>> cand;
			for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) cand.push_back(make_pair(i, j));
			random_shuffle(cand.begin(), cand.end());
			for(int i = 0; i < num_bomb; ++i) {
				int x, y; tie(x, y) = cand[i];
				bombMap[x][y].setBomb(1);
			}

			calcAdjTable();
		}

		void drawScoreboardBar() {
			setfillstyle(SOLID_FILL, MyColor::WINDOW_BG);
			bar(GAME_WIDTH + 2*MAP_PADDING, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

			setcolor(MyColor::BORDER);
			line(GAME_WIDTH + 2*MAP_PADDING, 0, GAME_WIDTH + 2*MAP_PADDING, WINDOW_HEIGHT);

			time_board.display(&getTimeString()[0], BOLD_FONT, 2);
			flag_board.display(&getBombLeft()[0], BOLD_FONT, 2);
		}
		
		void display() {
			drawScoreboardBar();
			restart_butt.draw();
			menu_butt.draw();

			int box_size = getBoxSize();
			for(int i = 0; i < height; ++i) 
			for(int j = 0; j < width; ++j) {
				bombMap[i][j].draw();
			}
		}

		void saveGame() {
			ofstream game_file(GameFile::GAME), time_file(GameFile::TIME);
			time_file << getPlayTime() << '\n';
			game_file << game_mode << ' ' << height << ' ' << width << ' ' << num_bomb << ' ' << '\n';
			for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) game_file << bombMap[i][j].encode() << " \n"[j == width-1]; 
			time_file.close();
			game_file.close();
		}
		
		static const int RESTART = 1, MENU = 2;
		int checkClickAndUpdate() {
			int cntLoops = 0;
			while (1) {
				bool has_update = false;
				if (restart_butt.checkHover() == Button::CLICKED) return RESTART;
				if (menu_butt.checkHover() == Button::CLICKED) return MENU;
				if (ismouseclick(WM_LBUTTONDOWN)) {
					has_update |= checkLeftMouseClick(); 
					if (has_update && status != LOSE_GAME) 
						PlaySound(MAKEINTRESOURCE(VALID_BOX), NULL, SND_RESOURCE|SND_ASYNC);
					else if (!lose()) PlaySound(MAKEINTRESOURCE(NONE), NULL, SND_RESOURCE|SND_ASYNC);
				} else if (ismouseclick(WM_RBUTTONDOWN)) {
					has_update |= checkRightMouseClick(); 	
					if (has_update) 
						PlaySound(MAKEINTRESOURCE(FLAG), NULL, SND_RESOURCE|SND_ASYNC);	
					else if (!lose()) PlaySound(MAKEINTRESOURCE(NONE), NULL, SND_RESOURCE|SND_ASYNC);
				} else checkHover();

				++cntLoops;
				if (cntLoops%40 == 0) updateGameTime();
				
				if (cntLoops%10 == 0) time_board.update(&getTimeString()[0], BOLD_FONT, 2);

				if (has_update) {
					saveGame();
					break;
				}

				delay(25);
			}

			if (status == ON_GOING) checkWinGame();
			
			if (status != ON_GOING) removeBackupFile();

			if (status == WIN_GAME) {
				for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) {
					if (bombMap[i][j].hasBomb()) bombMap[i][j].drawCorrectFlag();
				}
			}

			return 0;
		}

		void run() {
			setbkcolor(MyColor::GAME_BG);
			cleardevice();
			clearmouseclick(WM_LBUTTONDOWN);
			clearmouseclick(WM_RBUTTONDOWN);
			
			int cnt = 0;
			display();
			saveGame();
			int choice = -1;
			while (onGoing()) {
				int state = checkClickAndUpdate();

				if (state == RESTART) {
					choice = Window::RESTART;
					break;
				}
				if (state == MENU) return;
			}
			if (win() && game_mode != GameMode::NMODE-1) Ranking::insertScore(game_mode, getPlayTime());

			if (choice == -1) {
				delay(1000);
				if (win()) PlaySound(MAKEINTRESOURCE(WIN), NULL, SND_RESOURCE|SND_ASYNC);
				choice = Window::endGameAnnouncement(win());
			}
			
			if (choice == Window::RESTART) {
				Game newGame(game_mode, height, width, num_bomb);
				newGame.genRandomBombMap();
				newGame.run();
			}
		}
};

#undef DEBUG_MOUSE
#endif