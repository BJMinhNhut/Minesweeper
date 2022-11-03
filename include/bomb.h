#ifndef _BOMB_H_
#define _BOMB_H_

#include <bits/stdc++.h>
#include <graphics.h>
#include "box.h"
#include "scoreboard.h"
#include "constants.h"
using namespace std;

class Game {
	private:

		static const int ON_GOING = 0, LOSE_GAME = 1, WIN_GAME = 2;
		vector<vector<Box>> bombMap;
		int height, width, num_bomb;
		int status;
		ScoreBoard score_board;

		int getBoxSize() {
			return min({30, (WINDOW_HEIGHT-50)/height, (WINDOW_WIDTH-50)/width});
		}

		pair<int, int> getBombPos(int x, int y) {
			int box_size = getBoxSize();
			for(int i = 0; i < height; ++i) 
			for(int j = 0; j < width; ++j) {
				if (bombMap[i][j].isClicked(x, y)) {
					cerr << "Clicked " << i << ' ' << j << '\n';
					return make_pair(i, j);
				}
			}
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
			int base_pos = WINDOW_HEIGHT/2 - box_size*height/2;
			return make_tuple(base_pos + j*box_size, base_pos + i*box_size, base_pos + (j+1)*box_size, base_pos + (i+1)*box_size);
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

		void updateGameTime() {
			GameFile::TIME << score_board.getPlayTime() << '\n';
		}

		void removeBackupFile() {
			GameFile::TIME.clear();
			GameFile::GAME.clear();
		}
	
	public:
		Game(int h = DEBUG_HEIGHT, int w = DEBUG_WIDTH, int b = DEBUG_BOMB): height(h), width(w), num_bomb(b), status(ON_GOING) {
			bombMap.assign(height, vector<Box>(width, Box()));
			assert(num_bomb <= height*width && height <= 50 && width <= 50);
			
			for(int i = 0; i < height; ++i) 
			for(int j = 0; j < width; ++j) {
				int left, right, top, bot; tie(left, top, right, bot) = getPosOfBox(i, j);
				bombMap[i][j].setPos(left, top, right, bot);
			}

			int top_box = get<1>(getPosOfBox(0, 0));
			score_board = ScoreBoard(WINDOW_WIDTH/2, top_box-score_board.getHeight()/2, clock()/1000, num_bomb);
		}

		int getHeight() {return height;}
		int getWidth() {return width;}
		bool onGoing() {return status == ON_GOING;}
		bool lose() {return status == LOSE_GAME;}
		bool win() {return status == WIN_GAME;}

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
		
		void display() {
			int box_size = getBoxSize();
			for(int i = 0; i < height; ++i) 
			for(int j = 0; j < width; ++j) {
				bombMap[i][j].draw();
			}

			if (status == WIN_GAME) {
				setcolor(GREEN);
				outtextxy(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, "WINNNNNN");
			}
			if (status == LOSE_GAME) {
				setcolor(RED);
				outtextxy(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, "LOSEEEEE");
			}
		}

		bool openBox(int bombX, int bombY) {
			if (bombMap[bombX][bombY].hasBomb()) {
				//EXPLODE
				status = LOSE_GAME;
				for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) 
					if (bombMap[i][j].hasBomb()) bombMap[i][j].revealBox();
				return true;
			} else {
				//REVEAL BOX
				revealAreaStartFrom(bombX, bombY);
				if (DEBUG_MOUSE) for(int j = 0; j < width; ++j) for(int i = 0; i < height; ++i) cerr << bombMap[i][j].hidden() << " \n"[i == height-1];
				return true;
			}
			return false;
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

		bool checkLeftMouseClick() {
			int x, y; 
			int bombX, bombY; 
			getmouseclick(WM_LBUTTONDOWN, x, y);
			tie(bombX, bombY) = getBombPos(x, y);	// Get box position

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
					bool result = true;
					for(int dir = 0; dir < 8; ++dir) {
						int newX = bombX + NEXTX[dir], newY = bombY + NEXTY[dir];
						if (!validPos(newX, newY) || bombMap[newX][newY].isFlagged()) continue;
						result &= openBox(newX, newY);
 					}
					return result;
				} else {
					if (DEBUG_MOUSE) cerr << "Not enough flagged\n";
					return false;
				}
			}
		}

		bool checkRightMouseClick() {
			int x, y; 
			int bombX, bombY; 
			getmouseclick(WM_RBUTTONDOWN, x, y);
			tie(bombX, bombY) = getBombPos(x, y);
			if (validPos(bombX, bombY) && (bombMap[bombX][bombY].hidden() || bombMap[bombX][bombY].isFlagged())) {
				bombMap[bombX][bombY].toggleFlag(); 
				return true;
			} else cerr << "Outside Box\n";		
			return false;
		}

		void saveGame() {
			GameFile::TIME << score_board.getPlayTime() << '\n';
			GameFile::GAME << height << ' ' << width << ' ' << num_bomb << ' ' << '\n';
			for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) GameFile::GAME << bombMap[i][j].encode() << " \n"[j == width-1]; 
		}

		void checkClickAndUpdate() {
			int cntLoops = 0;
			while (1) {
				if (ismouseclick(WM_LBUTTONDOWN)) {
					if (checkLeftMouseClick()) {saveGame(); break;}
				} else if (ismouseclick(WM_RBUTTONDOWN)) {
					if (checkRightMouseClick()) {saveGame(); break;}			
				}

				++cntLoops;
				if (cntLoops%10 == 0) updateGameTime();

				score_board.display(bombMap[0][0].getFontType(), bombMap[0][0].getFontSize());
				delay(100);
			}

			if (status == ON_GOING) checkWinGame();
			else removeBackupFile();

			if (status == WIN_GAME) {
				for(int i = 0; i < height; ++i) for(int j = 0; j < width; ++j) {
					if (bombMap[i][j].hasBomb() && bombMap[i][j].hidden()) bombMap[i][j].toggleFlag();
					else if (bombMap[i][j].hidden()) bombMap[i][j].revealBox();
				}
			}
		}
};

#undef DEBUG_MOUSE
#endif