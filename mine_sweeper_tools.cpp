#include<iostream>
#include<chrono>
#include<conio.h>
#include<windows.h>
#include"mine_sweeper.h"
#include"cmd_console_tools.h"
using namespace std;

void printDifficulty() {
	cout << "请选择难度：" << endl;
	cout << "  1.初级( 9*9  - 10颗雷)" << endl;
	cout << "  2.中级(16*16 - 40颗雷)" << endl;
	cout << "  3.高级(16*30 - 99颗雷)" << endl;
	cout << "请输入[1..3]：";
}

void operate3(map m, int s) {
	int flag;

	while (1) {
		map::pos_t footprint = getOperate(m);
		if (footprint.x == -2) {
			flag = 114514;
			break;
		}
		flag = judge(m, footprint, s);
		if (flag == -1)break;
		else if (flag == 0) {
			openblock(m, footprint);
			printmap(m);
		}
		else break;
	}
	if (flag == -1) {
		cout << endl << endl;
		cout << "你输了，游戏结束";
		return;
	}
	else if (flag == 1) {
		cout << endl << endl;
		cout << "恭喜胜利，游戏结束";
		return;
	}
	else return;
}

void operate4(map m, int s) {
	auto t1 = std::chrono::steady_clock::now();
	int flag = 0;
	while (1) {
		char option = getOpt(m);
		if (option == '&') {
			auto t2 = std::chrono::steady_clock::now();
			double dr_s = std::chrono::duration<double>(t2 - t1).count();
			cct_cls();
			printui(m);
			printmap(m);
			cout << endl << endl << "已运行时间：" << dr_s << "秒";
			exPrint();
			continue;
		}
		else if (option == 'q' || option == 'Q') break;
		else if (option == '!') {
			map::pos_t footprint = gettwoopt(m);
			Mark(m, footprint);
			cct_cls();
			printui(m);
			printmap(m);
			exPrint();
			continue;
		}
		else if (option == '#') {
			map::pos_t footprint = gettwoopt(m);
			UnMark(m, footprint);
			cct_cls();
			printui(m);
			printmap(m);
			exPrint();
			continue;
		}
		else {
			size_t option2 = getlastopt(m);
			map::pos_t footprint = { option2,size_t(option) };
			flag = judge(m, footprint, s);
			if (flag == -1)break;
			else if (flag == 0) {
				openblock(m, footprint);
				cct_cls();
				printui(m);
				printmap(m);
				exPrint();
				continue;
			}
			else if (flag == 2) {
				cct_cls();
				printui(m);
				printmap(m);
				exPrint();
				continue;
			}
			else break;
		}

	}
	if (flag == -1) {
		cout << endl << endl;
		cout << "你输了，游戏结束";
		return;
	}
	else if (flag == 1) {
		cout << endl << endl;
		cout << "恭喜胜利，游戏结束";
		return;
	}
	else return;
}


int judge(map m, map::pos_t footprint, int s) {
	size_t cnt = 0;
	bool flag = 1;
	for (size_t i = 0; i < m.width * m.height; i++) {
		if (m.uncovered[i] == 0 || m.uncovered[i] == -1)cnt++;
	}
	if (m.uncovered[footprint.y * m.width + footprint.x] == -1)return 2;
	if (at(m, footprint) == map::elem::mine)return -1;
	else if (cnt == tt[s].mine_num + 1)return 1;
	else return 0;
}

void operate6(map m, int& x, int& y) {

	getcursorpos(m, x, y);
	if (x == -1 || y == -1) {
		cct_gotoxy(0, 3 * m.height + 3);
		cout << "　　　　　　　　　　　　　\r[当前光标] 位置非法";
	}
	else {
		char row, col;
		row = char(y + 'A');
		col = char(x > 9 ? x - 9 + 'a' : x + '1');
		cct_gotoxy(0, 3 * m.height + 3);
		cout << "　　　　　　　　　　　　　\r[当前光标] " << row << "行" << col << "列" << "";
	}
}

void operate66(map m, int& x, int& y) {

	getcursorpos(m, x, y);
	if (x == -1 || y == -1) {
		cct_gotoxy(0, 3 * m.height + 3);
		cout << "　　　　　　　　　　　　　\r[当前光标] 位置非法" << endl << "按esc键退出..";
	}
	else {
		char row, col;
		row = char(y + 'A');
		col = char(x > 9 ? x - 9 + 'a' : x + '1');
		cct_gotoxy(0, 3 * m.height + 3);
		cout << "　　　　　　　　　　　　　\r[当前光标] " << row << "行" << col << "列" << endl << "按esc键退出..";
	}
}

void operate666(map m, int& x, int& y) {

	getcursorpos(m, x, y);
	if (x == -1 || y == -1) {
		cct_gotoxy(0, 3 * m.height + 3);
		cout << "　　　　　　　　　　　　　\r[当前光标] 位置非法" << endl << "按esc键退出，空格显示时间..";
	}
	else {
		char row, col;
		row = char(y + 'A');
		col = char(x > 9 ? x - 9 + 'a' : x + '1');
		cct_gotoxy(0, 3 * m.height + 3);
		cout << "　　　　　　　　　　　　　\r[当前光标] " << row << "行" << col << "列" << endl << "按esc键退出，空格显示时间..";
	}
}

void operate8(map m, int s) {
	int x1 = 0, y1 = 0;
	int maction, keycode1, keycode2, ret;
	int flag = 0;
	cct_enable_mouse();
	map::pos_t footprint;
	while (1) {
		ret = cct_read_keyboard_and_mouse(x1, y1, maction, keycode1, keycode2);
		int xtemp = x1, ytemp = y1;
		operate66(m, x1, y1);
		x1 = xtemp, y1 = ytemp;
		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				operate6(m, x1, y1);
				footprint = { size_t(x1), size_t(y1) };
				if (footprint.x == -2)continue;
				flag = judge(m, footprint, s);
				if (flag == -1) break;
				else {
					openblock(m, footprint);
					cct_cls();
					printgraphui(m);
					printgraphmap(m, true, true);
					if (flag == 0)continue;
					else break;
				}

				if (footprint.x == -1 || footprint.y == -1)continue;
				break;
			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
				operate6(m, x1, y1);
				footprint = { size_t(x1), size_t(y1) };
				if (footprint.x == -1 || footprint.y == -1)continue;
				else {
					if (!m.uncovered[footprint.y * m.width + footprint.x])m.uncovered[footprint.y * m.width + footprint.x] = -1;
					else m.uncovered[footprint.y * m.width + footprint.x] = 0;
					cct_cls();
					printgraphui(m);
					printgraphmap(m, true, true);
					continue;
				}
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			if (keycode1 == 27)break;
		}

	}

	if (flag == -1) {
		cout << endl << endl;
		cout << "你输了，游戏结束";
		return;
	}
	else if (flag == 1) {
		cout << endl << endl;
		cout << "恭喜胜利，游戏结束";
		return;
	}
	else return;

}

void operate9(map m, int s) {
	int x1 = 0, y1 = 0;
	int maction, keycode1, keycode2, ret;
	int flag = 0;
	cct_enable_mouse();
	map::pos_t footprint;
	auto t1 = std::chrono::steady_clock::now();
	while (1) {
		ret = cct_read_keyboard_and_mouse(x1, y1, maction, keycode1, keycode2);
		int xtemp = x1, ytemp = y1;
		operate666(m, x1, y1);
		x1 = xtemp, y1 = ytemp;
		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				operate6(m, x1, y1);
				footprint = { size_t(x1), size_t(y1) };
				if (footprint.x == -2)continue;
				flag = judge(m, footprint, s);
				if (flag == -1) break;
				else {
					openblock(m, footprint);
					cct_cls();
					printgraphui(m);
					printgraphmap(m, true, true);
					if (flag == 0)continue;
					else break;
				}

				if (footprint.x == -1 || footprint.y == -1)continue;
				break;
			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
				operate6(m, x1, y1);
				footprint = { size_t(x1), size_t(y1) };
				if (footprint.x == -1 || footprint.y == -1)continue;
				else {
					if (!m.uncovered[footprint.y * m.width + footprint.x])m.uncovered[footprint.y * m.width + footprint.x] = -1;
					else m.uncovered[footprint.y * m.width + footprint.x] = 0;
					cct_cls();
					printgraphui(m);
					printgraphmap(m, true, true);
					continue;
				}
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			if (keycode1 == 27)break;
			else if (keycode1 == 32) {
				auto t2 = std::chrono::steady_clock::now();
				double dr_s = std::chrono::duration<double>(t2 - t1).count();
				cct_gotoxy(0, 3 * m.height + 5);
				cout << "当前程序运行时间为: " << dr_s << "秒";
			}
		}

	}

	if (flag == -1) {
		cout << endl << endl;
		cout << "你输了，游戏结束";
		return;
	}
	else if (flag == 1) {
		cout << endl << endl;
		cout << "恭喜胜利，游戏结束";
		return;
	}
	else return;
}

void getcursorpos(map m, int& x, int& y) {
	x -= 2;
	if (x < 0 || x / 6 >= (int)m.width || x % 6 <= 1)x = -1;
	else x /= 6;

	y -= 2;
	if (y < 0 || y / 3 >= (int)m.height || y % 3 == 0)y = -1;
	else y /= 3;

}

