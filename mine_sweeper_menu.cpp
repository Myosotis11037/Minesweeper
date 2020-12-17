#include<iostream>
#include<windows.h>
#include<conio.h>
#include"mine_sweeper.h"
#include"cmd_console_tools.h"
using namespace std;

int menu() {
	cout << "------------------------------------------" << endl;
	cout << "1.选择难度并显示内部数组" << endl;
	cout << "2.输入初始位置并显示被打开的初始区域" << endl;
	cout << "3.内部数组基础版" << endl;
	cout << "4.内部数组完整版（标记、运行时间）" << endl;
	cout << "5.画出伪图形化框架并显示内部数据" << endl;
	cout << "6.检测鼠标位置和合法性（左键单击退出）" << endl;
	cout << "7.鼠标选择初始位置并显示被打开的初始区域" << endl;
	cout << "8.伪图形界面基础版" << endl;
	cout << "9.伪图形界面完整版" << endl;
	cout << "0.退出游戏" << endl;
	cout << "------------------------------------------" << endl;
	cout << "[请选择:]";
	char cmd;
	while (1) {
		cmd = _getch();
		if (cmd >= '0' && cmd <= '9') {
			break;
		}
		else continue;
	}
	cout << cmd << endl;
	cout << endl;
	return (cmd - '0');

}

void choose(int cmd) {
	switch (cmd) {
	case 1: {
		printDifficulty();
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map1 = createmap(s);
		printui(map1);
		initmap(map1, s, map::GLOBAL_INVALID_POS);
		printmap(map1, false, false);
		printhalt();
		cct_cls();
		deletemap(map1);
		break;
	}

	case 2: {
		printDifficulty();
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map2 = createmap(s);
		printui(map2);
		printmap(map2);
		map::pos_t footprint = getOperate(map2);
		initmap(map2, s, footprint);
		openblock(map2, footprint);
		printmap(map2);
		printhalt();
		cct_cls();
		deletemap(map2);
		break;
	}


	case 3: {
		printDifficulty();
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map3 = createmap(s);
		printui(map3);
		printmap(map3);
		map::pos_t footprint = getOperate(map3);
		initmap(map3, s, footprint);
		openblock(map3, footprint);
		cct_cls();
		printui(map3);
		printmap(map3, 1);
		operate3(map3, s);
		printhalt();
		cct_cls();
		deletemap(map3);
		break;
	}

	case 4: {
		printDifficulty();
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map4 = createmap(s);
		printui(map4);
		printmap(map4);
		exPrint();
		map::pos_t footprint = gettwoopt(map4);
		if (footprint.x == -2) {
			cct_cls();
			break;
		}
		else {
			initmap(map4, s, footprint);
			openblock(map4, footprint);
			cct_cls();
			printui(map4);
			printmap(map4, 1);
			exPrint();
			operate4(map4, s);
			printhalt();
			cct_cls();
			deletemap(map4);
			break;
		}
	}


	case 5: {
		printDifficulty();
		cct_setfontsize("点阵字体", 16, 8);
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map5 = createmap(s);
		printgraphui(map5);
		initmap(map5, s, map::GLOBAL_INVALID_POS);
		printgraphmap(map5, false, true);
		printhalt();
		cct_cls();
		deletemap(map5);
		cct_setfontsize("新宋体", 28);
		break;
	}

	case 6: {
		printDifficulty();
		cct_setfontsize("点阵字体", 16, 8);
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map6 = createmap(s);
		printgraphui(map6);
		initmap(map6, s, map::GLOBAL_INVALID_POS);
		printgraphmap(map6, false, true);
		cct_enable_mouse();

		while (1) {
			int x1 = 0, y1 = 0, maction, keycode1, keycode2, ret;
			ret = cct_read_keyboard_and_mouse(x1, y1, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (maction == MOUSE_LEFT_BUTTON_CLICK) break;
			}

			operate6(map6, x1, y1);
		}

		printhalt();
		cct_cls();
		deletemap(map6);
		cct_setfontsize("新宋体", 28);
		break;
	}

	case 7: {
		printDifficulty();
		cct_setfontsize("点阵字体", 16, 8);
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map7 = createmap(s);
		int x1 = 0, y1 = 0;
		int maction, keycode1, keycode2, ret;
		cct_enable_mouse();
		printgraphui(map7);
		printgraphmap(map7, true, true);
		map::pos_t footprint;
		while (1) {
			cct_enable_mouse();
			int x, y;
			cct_getxy(x, y);
			ret = cct_read_keyboard_and_mouse(x1, y1, maction, keycode1, keycode2);
			int xtemp = x1, ytemp = y1;
			operate6(map7, x1, y1);
			x1 = xtemp, y1 = ytemp;
			if (ret == CCT_MOUSE_EVENT) {
				if (maction == MOUSE_LEFT_BUTTON_CLICK) {
					operate6(map7, x1, y1);
					footprint = { size_t(x1), size_t(y1) };
					if (footprint.x == -1 || footprint.y == -1)continue;
					break;
				}
			}

		}
		cct_cls();
		initmap(map7, s, footprint);
		openblock(map7, footprint);
		printgraphui(map7);
		printgraphmap(map7, true, true);
		printhalt();
		cct_cls();
		deletemap(map7);
		cct_setfontsize("新宋体", 28);
		break;
	}

	case 8: {
		printDifficulty();
		cct_setfontsize("点阵字体", 16, 8);
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map8 = createmap(s);
		int x1 = 0, y1 = 0;
		int maction, keycode1, keycode2, ret;
		cct_enable_mouse();
		printgraphui(map8);
		printgraphmap(map8, true, true);
		map::pos_t footprint;
		while (1) {
			operate6(map8, x1, y1);
			ret = cct_read_keyboard_and_mouse(x1, y1, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (maction == MOUSE_LEFT_BUTTON_CLICK) {
					operate6(map8, x1, y1);
					footprint = { size_t(x1), size_t(y1) };
					if (footprint.x == -1 || footprint.y == -1)continue;
					break;
				}
			}
		}
		cct_cls();
		initmap(map8, s, footprint);
		openblock(map8, footprint);
		printgraphui(map8);
		printgraphmap(map8, true, true);
		operate8(map8, s);
		printhalt();
		cct_cls();
		deletemap(map8);
		cct_setfontsize("新宋体", 28);
		break;
	}

	case 9: {
		printDifficulty();
		cct_setfontsize("点阵字体", 16, 8);
		char temp;
		while (1) {
			temp = _getch();
			if (temp >= '1' && temp <= '3') break;
			else continue;
		}
		int s = temp - '1';
		cct_cls();
		map map9 = createmap(s);
		int x1 = 0, y1 = 0;
		int maction, keycode1, keycode2, ret;
		cct_enable_mouse();
		printgraphui(map9);
		printgraphmap(map9, true, true);
		map::pos_t footprint;
		while (1) {
			operate6(map9, x1, y1);
			ret = cct_read_keyboard_and_mouse(x1, y1, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (maction == MOUSE_LEFT_BUTTON_CLICK) {
					operate6(map9, x1, y1);
					footprint = { size_t(x1), size_t(y1) };
					if (footprint.x == -1 || footprint.y == -1)continue;
					break;
				}
			}
		}
		cct_cls();
		initmap(map9, s, footprint);
		openblock(map9, footprint);
		printgraphui(map9);
		printgraphmap(map9, true, true);
		operate9(map9, s);
		printhalt();
		cct_cls();
		deletemap(map9);
		cct_setfontsize("新宋体", 28);
		break;

	}

	}

}