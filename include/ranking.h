#ifndef _RANKING_H_
#define _RANKING_H_

#include "constants.h"
#include "button.h"
#include "window.h"
#include <graphics.h>
#include <algorithm>

namespace Ranking {
	const int NRANK = 5, INF = 1e9;
	vector<int> data[GameMode::NMODE-1];

	void loadRanking() {
		ifstream rank_file(GameFile::RANK);
		for(int i = 0; i < GameMode::NMODE-1; ++i) data[i].assign(NRANK, INF);
		for(int i = 0; i < GameMode::NMODE-1; ++i) {
			for (int j = 0; j < NRANK; ++j) {
				if (!(rank_file >> data[i][j])) return;
			}
		} 
		rank_file.close();
	}

	void saveRanking() {
		ofstream rank_file(GameFile::RANK);
		for(int i = 0; i < GameMode::NMODE-1; ++i) {
			for (int j = 0; j < NRANK; ++j) {
				rank_file << data[i][j] << ' ';
			}
		} 
		rank_file.close();
	}

	void printTitle() {
		int midx = WINDOW_WIDTH/2;
		int midy = WINDOW_HEIGHT/2;

		settextjustify(CENTER_TEXT, CENTER_TEXT);
		SetTextStyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(MyColor::TEXT);
		setbkcolor(MyColor::WINDOW_BG);
		outtextxy(midx, midy-170, "HALL OF FAME");
	}

	string getTimeString(int play_time) {
		if (play_time == INF) return "-";
		char ans[30];
		sprintf(ans, "%02d:%02d", play_time/60, play_time%60);
		return ans;
	}

	string getBestTime(int game_mode) {
		if (game_mode >= GameMode::NMODE-1 || *data[game_mode].begin() == INF) return "-";
		return getTimeString(*data[game_mode].begin());
	}
	
	void displayRanking() {
		clearmouseclick(WM_LBUTTONDOWN);
		setbkcolor(MyColor::GAME_BG);
		cleardevice();
		Button returnButt(100, 30, WINDOW_WIDTH/2-70, WINDOW_HEIGHT - 50, "RETURN");
		Button resetButt(100, 30, WINDOW_WIDTH/2+70, WINDOW_HEIGHT - 50, "RESET");
		
		// ranking table
		drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, WINDOW_WIDTH/2-400, WINDOW_HEIGHT/2-200, WINDOW_WIDTH/2+400, WINDOW_HEIGHT/2-150);
		printTitle();

		for(int game_mode = 0, left = WINDOW_WIDTH/2 - 400; game_mode < GameMode::NMODE-1; ++game_mode, left += 200) {
			drawFrame(MyColor::WINDOW_BG, MyColor::BORDER, left, WINDOW_HEIGHT/2-150, left+200, WINDOW_HEIGHT/2-100);
			setcolor(WHITE);
			outtextxy(left+100, WINDOW_HEIGHT/2-120, &GameMode::CAPTION[game_mode][0]);
			// cerr << data[game_mode].size() << '\n';
			for(int i = 0, bot = WINDOW_HEIGHT/2-100; i < NRANK; ++i, bot += 50) {
				drawFrame(MyColor::GAME_BG, MyColor::BORDER, left, bot, left+200, bot+50);
				setcolor(WHITE);
				outtextxy(left+100, bot+30, &getTimeString(data[game_mode][i])[0]);
				// cerr << getTimeString(data[game_mode][i]) << '\n';
			}
		}
		returnButt.draw();
		resetButt.draw();

		while (1) {
			if (returnButt.checkHover() == Button::CLICKED) return;
			if (resetButt.checkHover() == Button::CLICKED) {
				if (Window::resetRankWarning() == Window::CONTINUE) {
					for(int i = 0; i < GameMode::NMODE-1; ++i) data[i].assign(NRANK, INF);
					saveRanking();
				}
				
				displayRanking();
				return;
			}
		}
	}

	void insertScore(int game_mode, int score) {
		// cerr << "Inserting new score: " << score << '\n';
		data[game_mode].push_back(score);
		sort(data[game_mode].begin(), data[game_mode].end());
		data[game_mode].resize(NRANK);
		saveRanking();
	}
}

#endif 