#include<iostream>
#include"Manager.h"

int main()
{
	srand(time(0));
	initgraph(1080, 720);
	setbkcolor(RGB(30, 39, 80));
	setbkmode(TRANSPARENT);
	cleardevice();
	Manager manager;
	manager.Menu();
	_getch();
	closegraph();
	return 0;
}