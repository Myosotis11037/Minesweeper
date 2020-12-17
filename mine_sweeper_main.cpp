#include<iostream>
#include<windows.h>
#include"cmd_console_tools.h"
#include"mine_sweeper.h"
using namespace std;
int main() {
	cct_setconsoleborder(120, 40, 120, 9000);
	int cmd;
	while (1) {	
		cmd = menu();
		if (cmd == 0) {
			break;
		}
		cct_cls();
		choose(cmd);
	}
	return 0;
}
