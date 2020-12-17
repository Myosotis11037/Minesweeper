#include<iostream>
#include<conio.h>
#include<chrono>
#include<iomanip>
#include"cmd_console_tools.h"
#include"mine_sweeper.h"
using namespace std;

void printui(map m) {
	cout << "内部数组：" << endl;
	cout << "  |";
	for (uintptr_t col = 1; col <= m.width; col++) {
		cout << char((col < 10 ? '0' + col : 'a' + col - 10)) << ' ';
	}
	cout << endl << "--+";
	for (uintptr_t col = 1; col <= m.width; col++) {
		cout << "--";
	}
	cout << "--" << endl;
	for (char row = 'A'; row < char('A' + m.height); row++) {
		cout << row << " |" << endl;
	}
}

void printmap(map m, int coverage, bool highlight) {
	for (uintptr_t j = 0; j < m.height; j++) {
		cct_gotoxy(3, 3 + j);
		for (uintptr_t i = 0; i < m.width; i++) {
			if (m.uncovered[j * m.width + i] != -1 && (!coverage || m.uncovered[j * m.width + i])) {
				char thing = at(m, map::pos_t{ i, j }) == map::elem::air ?
					'0' : char(at(m, map::pos_t{ i, j }));

				if (highlight) {
					cct_setcolor(COLOR_HYELLOW, (thing - '0') % COLOR_HWHITE);
				}

				cout << thing << ' ';

				if (highlight) {
					cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				}
			}
			else {
				if (m.uncovered[j * m.width + i] == -1)cct_setcolor(COLOR_RED, COLOR_WHITE);
				else cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << 'X' << ' ';
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
		}
	}
}

void Mark(map m, map::pos_t footprint) {
	intptr_t& coverage = m.uncovered[footprint.y * m.width + footprint.x];
	if (coverage == 0) {
		coverage = -1;
		cct_setcolor(COLOR_RED, COLOR_WHITE);
		cct_showch(footprint.x * 2 + 3, footprint.y + 3, 'X', COLOR_RED, COLOR_BLACK);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	}

}

void UnMark(map m, map::pos_t footprint) {
	intptr_t& coverage = m.uncovered[footprint.y * m.width + footprint.x];
	if (coverage == -1) {
		coverage = 0;
		cct_showch(footprint.x * 2 + 3, footprint.y * 2 + 3, 'X', COLOR_BLACK, COLOR_WHITE);
	}
}


map::pos_t getOperate(map m) {
	cout << endl << endl;
	cout << "输入非雷位置的行列坐标（先行后列，严格区分大小写，例：G1/Af，按Q/q退出）：";

	size_t row = 0, col = 0;


	while (1) {
		char c = _getch();
		if (c == 'q' || c == 'Q') return map::GLOBAL_INVALID_POS;
		else if (c >= 'A' && c <= char('A' - 1 + m.height)) {
			row = c - 'A';
			break;
		}
	}
	cout << char(row + 'A');

	while (1) {
		char c = _getch();
		if (c >= '1' && c <= '9') {
			col = c - '1';
			break;
		}
		else if (c >= 'a' && c <= char('a' + m.width - 10) && m.width > 10) {
			col = c - 'a' + 9;
			break;
		}
	}
	cout << char(col > 9 ? col - 9 + 'a' : col + '1');

	return { col, row };
}

void exPrint() {
	cout << endl << endl;
	cout << "特殊输入说明：& - 游戏已运行时间(单字符即可，不需要加坐标)" << endl;
	cout << "              ! - 标记该坐标为雷(例：!E3)" << endl;
	cout << "              # - 取消标记      (例：#E3)" << endl;
	cout << "请输入（坐标必须先行后列，严格区分大小写，例：G1/Af，按Q/q退出）：";
}

char getOpt(map m) {
	while (1) {
		char c = _getch();
		if (c == '&' || c == '!' || c == '#' || c == 'q' || c == 'Q') {
			cout << c;
			return c;
		}
		else if (c >= 'A' && c <= char('A' - 1 + m.height)) {
			char row = c - 'A';
			cout << char(row + 'A');
			return row;
		}
	}
}

size_t getlastopt(map m) {
	size_t col;
	while (1) {
		char c = _getch();
		if (c >= '1' && c <= '9') {
			col = c - '1';
			break;
		}
		else if (c >= 'a' && c <= char('a' + m.width - 10) && m.width > 10) {
			col = c - 'a' + 9;
			break;
		}
	}
	cout << char(col > 9 ? col - 9 + 'a' : col + '1');
	return col;

}

map::pos_t gettwoopt(map m) {
	size_t row = 0, col = 0;
	while (1) {
		char c = _getch();
		if (c >= 'A' && c <= char('A' - 1 + m.height)) {
			row = c - 'A';
			break;
		}
	}
	cout << char(row + 'A');

	while (1) {
		char c = _getch();
		if (c >= '1' && c <= '9') {
			col = c - '1';
			break;
		}
		else if (c >= 'a' && c <= char('a' + m.width - 10) && m.width > 10) {
			col = c - 'a' + 9;
			break;
		}
	}
	cout << char(col > 9 ? col - 9 + 'a' : col + '1');

	return { col, row };
}

void printhalt() {
	cout << endl << endl;
	cout << "\n\r按回车键继续...";
	while (1) {
		char c = _getch();
		if (c == 13)break;
	}
}

void printgraphui(map m) {
	switch (m.width) {
	case 10:cct_setconsoleborder(120, 50, 120, 9000); break;
	case 16:cct_setconsoleborder(140, 70, 120, 9000); break;
	case 30:cct_setconsoleborder(200, 70, 120, 9000); break;
	}
	cout << endl;
	for (size_t i = 0; i < m.width; i++) {
		cout << setw(6) << char(i >= 9 ? i - 9 + 'a' : i + '1');
	}
	cout << endl;
	for (size_t i = 0; i <= m.height; i++) {
		if (i == 0) {
			cct_gotoxy(2, i * 3 + 2);
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "╔";
			for (size_t j = 0; j < m.width - 1; j++) {
				cout << "══╦";
			}
			cout << "══╗";
		}
		else if (i < m.height) {
			cct_gotoxy(2, i * 3 + 2);
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "╠";
			for (size_t j = 0; j < m.width - 1; j++) {
				cout << "══╬";
			}
			cout << "══╣";
		}
		else {
			cct_gotoxy(2, i * 3 + 2);
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "╚";
			for (size_t j = 0; j < m.width - 1; j++) {
				cout << "══╩";
			}
			cout << "══╝";
		}
	}

	for (size_t i = 0; i <= m.width; i++) {
		for (size_t j = 0; j <= m.height - 1; j++) {
			cct_gotoxy(6 * i + 2, 3 * j + 3);
			cout << "║";
			cct_gotoxy(6 * i + 2, 3 * j + 4);
			cout << "║";
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	for (size_t i = 0; i < m.height; i++) {
		cct_gotoxy(0, 3 * i + 4);
		cout << char('A' + i);
	}



	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 3 * m.height + 3);
}

void printgraphmap(map m, int coverage, bool highlight) {
	for (size_t i = 0; i < m.width; i++) {
		for (size_t j = 0; j < m.height; j++) {
			if (m.uncovered[j * m.width + i] != -1) {
				cct_showch(6 * i + 4, 3 * (j + 1), ' ', coverage && !m.uncovered[j * m.width + i] ? COLOR_YELLOW : COLOR_WHITE, COLOR_WHITE, 4);
				cct_showch(6 * i + 4, 3 * (j + 1) + 1, ' ', coverage && !m.uncovered[j * m.width + i] ? COLOR_YELLOW : COLOR_WHITE, COLOR_WHITE, 4);
			}
			else {
				cct_showch(6 * i + 4, 3 * (j + 1), ' ',COLOR_HRED, COLOR_HWHITE, 4);
				cct_showch(6 * i + 4, 3 * (j + 1) + 1,' ', COLOR_HRED, COLOR_HWHITE, 4);
			}
		}
	}

	for (uintptr_t j = 0; j < m.height; j++) {
		for (uintptr_t i = 0; i < m.width; i++) {
			cct_gotoxy(6 * i + 5, 3 * j + 4);
			if (m.uncovered[j * m.width + i] != -1 && (!coverage || m.uncovered[j * m.width + i])) {
				char thing = at(m, map::pos_t{ i, j }) == map::elem::air ?
					'0' : char(at(m, map::pos_t{ i, j }));

				if (highlight) {
					cct_setcolor(COLOR_WHITE, (thing - '0') % COLOR_HWHITE);
				}
				if (thing == '0')cout << ' ';
				else if (thing == '*') {
					cct_setcolor(COLOR_WHITE, COLOR_BLACK);
					cout << thing;
				}
				else cout << thing;
				cct_setcolor(COLOR_WHITE, COLOR_BLACK);
				cout << ' ';
			}
			else {
				if (m.uncovered[j * m.width + i] == -1) {
					cct_setcolor(COLOR_HRED, COLOR_WHITE);
					cout << '#';
					continue;
				}
				else if(!m.uncovered[j * m.width + i]) cct_setcolor(COLOR_YELLOW, COLOR_BLACK);
				else cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << ' ';
			}
		}
	}

	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 3 * m.height + 3);

}