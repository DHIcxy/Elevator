#include"Manager.h"
#include<iostream>
using namespace std;
Manager::Manager()
{
	this->num = 13;
	this->times = 5 + rand() % 10;
	//初始化背景
	for (int i = 0; i < 7; i++)
	{
		this->bk.x[i][0] = 0;
		this->bk.x[i][1] = 400;
		this->bk.y[i][0] = 695 - 100 * i;
		this->bk.y[i][1] = 700 - 100 * i;
	}
	//初始化电梯
	this->elevator.floor = 0;
	this->elevator.left = 400;
	this->elevator.right = 600;
	this->elevator.top = this->bk.y[this->elevator.floor][0];
	this->elevator.bottom = this->bk.y[this->elevator.floor][1];
	this->elevator.Stop = false;
	this->elevator.flag = 0;//0为向上，1为向下
	//初始化按钮
	for (int i = 0; i < 7; i++)
	{
		this->button[i].x = 800 + 60 * (i % 4);
		this->button[i].y = 40 + (i / 4) * 60;
	}
	//初始化乘客
	this->InitPeople();
}
//获取当前系统时间
string Manager::getTime()
{
	string times;
	time_t now_sec = time(0);
	struct tm now_time;
	localtime_s(&now_time, &now_sec);
	times = to_string(now_time.tm_year + 1900) + "/" + to_string(now_time.tm_mon + 1) + "/"
		+ to_string(now_time.tm_mday) + "/" + to_string(now_time.tm_hour) + ":" + to_string(now_time.tm_min)
		+ ":" + to_string(now_time.tm_sec);
	return times;
}
//判断电梯是否可以掉头
bool Manager::IfReturn()
{
	if (this->elevator.flag == 0)
	{
		//电梯向上运动时
		for (int i = 0; i < this->people.size(); i++)
		{
			//如果电梯上面的楼层有人要查找电梯
			if (this->people[i].start > this->elevator.floor
				&& this->people[i].Ispicture && !this->people[i].In)
				return false;
			//如果有人要从电梯上面的楼层下电梯
			if (this->people[i].end > this->elevator.floor
				&& this->people[i].Ispicture && this->people[i].In)
				return false;
		}
	}
	else
	{
		//电梯向下运动时
		for (int i = 0; i < this->people.size(); i++)
		{
			//如果电梯下面的楼层有人要坐电梯
			if (this->people[i].start < this->elevator.floor
				&& this->people[i].Ispicture && !this->people[i].In)
				return false;
			//如果有人要从电梯下面的楼层下电梯
			if (this->people[i].end < this->elevator.floor
				&& this->people[i].Ispicture && this->people[i].In)
				return false;
		}
	}
	//如果没人
	if (this->num == 0)
		return false;
	return true;
}
//初始化乘客
void Manager::InitPeople()
{
	//清空people容器
	people.clear();
	People p;
	//乘客人数设为13，模拟正常的人流量
	for (int i = 0; i < 13; i++)
	{
		//加载乘客图片
		loadimage(&p.img, "乘客.png", 40, 60);
		p.start = rand() % 7;
		p.x = 200 + rand() % 150;
		p.ex = p.x + 200;
		p.y = this->bk.y[p.start][0] - 60;
		p.In = false;
		p.Get = false;
		p.end = rand() % 7;
		p.Ispicture = true;
		while (p.end == p.start)
			p.end = rand() % 7;
		people.push_back(p);
	}
}
//电梯菜单界面
void Manager::Menu()
{
	MOUSEMSG msg;
	setbkcolor(RGB(30, 39, 80));
	while (1)
	{
		setfillcolor(BLUE);
		settextstyle(40, 0, "微软雅黑");
		settextcolor(WHITE);
		msg = GetMouseMsg();
		BeginBatchDraw();
		if (msg.x >= 440 && msg.x <= 600 && msg.y >= 70 && msg.y <= 130)
		{
			fillrectangle(440, 230, 600, 290);
			fillrectangle(440, 390, 600, 450);
			fillrectangle(440, 550, 600, 610);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 70, 600, 130);
			outtextxy(450, 80, "电梯乘坐");
			outtextxy(450, 240, "模拟电梯");
			outtextxy(450, 400, "查询记录");
			outtextxy(450, 560, "退出系统");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//加载函数
				this->Load();
				//乘坐电梯
				this->TakeElevator();
				//重新初始化乘客
				this->InitPeople();
				//重新初始化电梯
				this->elevator.top = this->bk.y[0][0];
				this->elevator.bottom = this->bk.y[0][1];
				this->elevator.floor = 0;
				this->elevator.flag = 0;
				this->elevator.Stop = false;
				continue;
			}
		}
		else if (msg.x >= 440 && msg.x <= 600 && msg.y >= 230 && msg.y <= 290)
		{
			fillrectangle(440, 70, 600, 130);
			fillrectangle(440, 390, 600, 450);
			fillrectangle(440, 550, 600, 610);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 230, 600, 290);
			outtextxy(450, 80, "电梯乘坐");
			outtextxy(450, 240, "模拟电梯");
			outtextxy(450, 400, "查询记录");
			outtextxy(450, 560, "退出系统");
			BeginBatchDraw();
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//设置人流量
				if (this->InitPeopleNum())
				{
					//加载函数
					this->Load();
					//模拟电梯
					this->RandElevator();
				}
				//重新初始化乘客
				this->InitPeople();
				//重新初始化电梯
				this->elevator.top = this->bk.y[0][0];
				this->elevator.bottom = this->bk.y[0][1];
				this->elevator.floor = 0;
				this->elevator.flag = 0;
				this->elevator.Stop = false;
				continue;
			}
		}
		else if (msg.x >= 440 && msg.x <= 600 && msg.y >= 390 && msg.y <= 450)
		{
			fillrectangle(440, 70, 600, 130);
			fillrectangle(440, 230, 600, 290);
			fillrectangle(440, 550, 600, 610);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 390, 600, 450);
			outtextxy(450, 80, "电梯乘坐");
			outtextxy(450, 240, "模拟电梯");
			outtextxy(450, 400, "查询记录");
			outtextxy(450, 560, "退出系统");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//查找记录
				this->FindRecord();
				continue;
			}
		}
		else if (msg.x >= 440 && msg.x <= 600 && msg.y >= 550 && msg.y <= 610)
		{
			fillrectangle(440, 70, 600, 130);
			fillrectangle(440, 230, 600, 290);
			fillrectangle(440, 390, 600, 450);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 550, 600, 610);
			outtextxy(450, 80, "电梯乘坐");
			outtextxy(450, 240, "模拟电梯");
			outtextxy(450, 400, "查询记录");
			outtextxy(450, 560, "退出系统");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//退出电梯系统
				this->Exit();
				break;
			}
		}
		else
		{
			fillrectangle(440, 70, 600, 130);
			fillrectangle(440, 230, 600, 290);
			fillrectangle(440, 390, 600, 450);
			fillrectangle(440, 550, 600, 610);
			outtextxy(450, 80, "电梯乘坐");
			outtextxy(450, 240, "模拟电梯");
			outtextxy(450, 400, "查询记录");
			outtextxy(450, 560, "退出系统");
			EndBatchDraw();
		}
	}
}
//画图函数
void Manager::Picture()
{
	setfillcolor(RGB(116, 118, 117));
	//画背景
	for (int i = 0; i < 7; i++)
	{
		fillrectangle(this->bk.x[i][0], this->bk.y[i][0],
			this->bk.x[i][1], this->bk.y[i][1]);
	}
	//画电梯
	fillrectangle(this->elevator.left, this->elevator.top,
		this->elevator.right, this->elevator.bottom);
	fillrectangle(this->elevator.left, this->elevator.top - 100,
		this->elevator.left + 5, this->elevator.top);
	fillrectangle(this->elevator.right - 5, this->elevator.top - 100,
		this->elevator.right, this->elevator.top);
	fillrectangle(this->elevator.left, this->elevator.top - 100,
		this->elevator.right, this->elevator.bottom - 100);
	//画乘客
	for (int i = 0; i < people.size(); i++)
	{
		if (this->people[i].Ispicture)
			putimage(this->people[i].x, this->people[i].y, &this->people[i].img);
	}
}
//加载函数
void Manager::Load()
{
	IMAGE img;
	loadimage(&img, "加载2.jpg", 1080, 720);
	settextstyle(50, 0, "微软雅黑");
	settextcolor(WHITE);
	putimage(0, 0, &img);
	outtextxy(450, 550, "加载中...");
	setfillcolor(WHITE);
	int x = 300;
	solidrectangle(300, 600, 780, 610);
	setfillcolor(RGB(187, 202, 37));
	while (1)
	{
		fillrectangle(300, 600, x, 610);
		if (x >= 780)
			break;
		x += 5;
		Sleep(25);
	}
}
//显示电梯按钮
void Manager::ShowButton1()
{
	int arr[7];
	for (int i = 0; i < 7; i++)
		arr[i] = 0;
	for (int i = 0; i < people.size(); i++)
	{
		//如果为设置终点，直接跳过
		if (this->people[i].end == -1)
			continue;
		else
		{
			if (this->people[i].Get)
				continue;
			else
				arr[this->people[i].end] = 1;
		}
	}
	for (int j = 0; j < 7; j++)
	{
		if (arr[j] == 0)//如果该楼层没人前往，则该按钮显示灰色
			setfillcolor(RGB(249, 249, 249));
		else//如果该楼层有人前往，则该按钮显示黄色
			setfillcolor(YELLOW);
		//打印按钮
		fillcircle(this->button[j].x, this->button[j].y, 20);
	}
	settextcolor(BLACK);
	settextstyle(30, 0, "微软雅黑");
	for (int j = 0; j < 7; j++)
	{
		//打印按钮数字
		char ch = (j + 1) + '0';
		outtextxy(this->button[j].x - 5, this->button[j].y - 15, ch);
	}
}
//电梯乘坐函数
void Manager::TakeElevator()
{
	//打开记录文件
	ofstream ofs(FILE, ios::out | ios::app);
	setbkcolor(RGB(30, 39, 80));
	//将所有乘客的终点站设为-1，表示未设置终点站
	for (int i = 0; i < people.size(); i++)
		this->people[i].end = -1;
	bool flag = false;
	while (1)
	{
		this->num = 1;
		flag = false;
		cleardevice();
		BeginBatchDraw();
		for (int i = 0; i < 13; i++)
		{
			if (this->people[i].Ispicture)
			{
				//电梯到达该楼层且乘客为进电梯时
				if (this->people[i].start == this->elevator.floor && !this->people[i].In)
				{
					flag = true;
					break;
				}
				else if (this->people[i].start == this->elevator.floor && this->people[i].In
					&& this->people[i].end == -1)//乘客在电梯内但是乘客为设置终点位置时
				{
					flag = true;
					break;
				}
				else if (this->people[i].end == this->elevator.floor && this->people[i].In)
				{
					//乘客到达终点站时
					flag = true;
					break;
				}
			}
		}
		//判断电梯是否要停下
		if (flag)
			this->elevator.Stop = true;
		else
			this->elevator.Stop = false;
		//当电梯停下时
		if (this->elevator.Stop)
		{
			for (int i = 0; i < people.size(); i++)
			{
				if (this->people[i].Ispicture)
				{
					if (this->people[i].start == this->elevator.floor
						&& !this->people[i].In && !this->people[i].Get)
					{
						this->people[i].x += 5;
						if (this->people[i].x >= this->people[i].ex)
						{
							this->people[i].In = true;
						}
					}
					else if (this->people[i].end == this->elevator.floor && this->people[i].In)
					{
						this->people[i].x -= 5;
						if (this->people[i].x <= 350)
						{
							this->people[i].In = false;
							this->people[i].Get = true;
						}
					}
				}
			}
			//画图
			this->Picture();
			for (int i = 0; i < people.size(); i++)
			{
				if (this->people[i].Ispicture)
				{
					if (this->people[i].In && this->people[i].end == -1)
					{
						setfillcolor(RED);
						fillrectangle(this->people[i].x - 20, this->people[i].y - 20,
							this->people[i].x + 70, this->people[i].y + 70);
						putimage(this->people[i].x, this->people[i].y, &this->people[i].img);
						Sleep(200);
						char ch[2];
						//乘客进入电梯后输入其终点站
						InputBox(ch, 2, "请输入终点：", "电梯", 0, 100, 40);
						this->people[i].end = (ch[0] - '0') - 1;
						//响铃，提示已经设置好终点站
						cout << '\a';
						//记录 编号 起点 终点 时间
						string nowtimes = this->getTime();
						ofs << i << " " << this->people[i].start << " "
							<< this->people[i].end << " " << nowtimes << endl;
					}
				}
			}
			//画按钮
			this->ShowButton1();
		}
		else
		{
			if (this->elevator.flag == 0)
			{
				this->elevator.top -= 5;
				this->elevator.bottom -= 5;
				for (int i = 0; i < 13; i++)
				{
					if (this->people[i].Ispicture && this->people[i].In)
						this->people[i].y -= 5;
				}
				if (this->elevator.top == this->bk.y[this->elevator.floor + 1][0])
					this->elevator.floor++;
				if (this->elevator.floor == 6)
					this->elevator.flag = 1;
			}
			else
			{
				this->elevator.top += 5;
				this->elevator.bottom += 5;
				for (int i = 0; i < 13; i++)
				{
					if (this->people[i].Ispicture && this->people[i].In)
						this->people[i].y += 5;
				}
				if (this->elevator.top == this->bk.y[this->elevator.floor - 1][0])
					this->elevator.floor--;
				if (this->elevator.floor == 0)
					this->elevator.flag = 0;
			}
			this->Picture();
			this->ShowButton1();
		}
		for (int i = 0; i < people.size(); i++)
		{
			if (this->people[i].Get && this->people[i].Ispicture)
			{
				if (this->people[i].x > -50)
					this->people[i].x -= 5;
				else
					this->people[i].Ispicture = false;
			}
		}
		this->num = 0;
		for (int i = 0; i < people.size(); i++)
		{
			if (this->people[i].Ispicture)
				this->num++;
		}
		if (this->num == 0)
		{
			cleardevice();
			break;
		}
		EndBatchDraw();
		Sleep(30);
	}
	ofs.close();
}
//重新初始化乘客数量
bool Manager::InitPeopleNum()
{
	setbkcolor(RGB(30, 39, 80));
	cleardevice();
	MOUSEMSG msg;
	settextcolor(WHITE);
	settextstyle(40, 0, "微软雅黑");
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.x >= 440 && msg.x <= 600 && msg.y >= 110 && msg.y <= 170)
		{
			setfillcolor(BLUE);
			fillrectangle(440, 270, 600, 330);
			fillrectangle(440, 430, 600, 490);
			fillrectangle(440, 590, 600, 650);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 110, 600, 170);
			outtextxy(450, 120, "人流量低");
			outtextxy(450, 280, "人流量中");
			outtextxy(450, 440, "人流量高");
			outtextxy(480, 600, "返回");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//模拟较少人流量
				this->people.resize(6);
				this->times /= 2;
				break;
			}
		}
		else if (msg.x >= 440 && msg.x <= 600 && msg.y >= 270 && msg.y <= 330)
		{
			setfillcolor(BLUE);
			fillrectangle(450, 110, 600, 170);
			fillrectangle(440, 430, 600, 490);
			fillrectangle(440, 590, 600, 650);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 270, 600, 330);
			outtextxy(450, 120, "人流量低");
			outtextxy(450, 280, "人流量中");
			outtextxy(450, 440, "人流量高");
			outtextxy(480, 600, "返回");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//模拟正常人流量
				//由于之前已经设置为13了，故无需继续操作，直接跳过
				break;
			}
		}
		else if (msg.x >= 440 && msg.x <= 600 && msg.y >= 430 && msg.y <= 490)
		{
			setfillcolor(BLUE);
			fillrectangle(440, 270, 600, 330);
			fillrectangle(440, 110, 600, 170);
			fillrectangle(440, 590, 600, 650);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 430, 600, 490);
			outtextxy(450, 120, "人流量低");
			outtextxy(450, 280, "人流量中");
			outtextxy(450, 440, "人流量高");
			outtextxy(480, 600, "返回");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//模拟较多人流量
				this->people.clear();
				People p;
				for (int i = 0; i < 20; i++)
				{
					//加载乘客图片
					loadimage(&p.img, "乘客.png", 40, 60);
					p.start = rand() % 7;
					p.x = 200 + rand() % 150;
					p.ex = p.x + 200;
					p.y = this->bk.y[p.start][0] - 60;
					p.In = false;
					p.Get = false;
					p.end = rand() % 7;
					p.Ispicture = true;
					while (p.end == p.start)
						p.end = rand() % 7;
					people.push_back(p);
					this->times = this->times * 3 / 2;
				}
				break;
			}
		}
		else if (msg.x >= 440 && msg.x <= 600 && msg.y >= 590 && msg.y <= 650)
		{
			setfillcolor(BLUE);
			fillrectangle(440, 270, 600, 330);
			fillrectangle(440, 110, 600, 170);
			fillrectangle(440, 430, 600, 490);
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(440, 590, 600, 650);
			outtextxy(450, 120, "人流量低");
			outtextxy(450, 280, "人流量中");
			outtextxy(450, 440, "人流量高");
			outtextxy(480, 600, "返回");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				return false;
			}
		}
		else
		{
			setfillcolor(BLUE);
			fillrectangle(440, 110, 600, 170);
			fillrectangle(440, 270, 600, 330);
			fillrectangle(440, 430, 600, 490);
			fillrectangle(440, 590, 600, 650);
			outtextxy(450, 120, "人流量低");
			outtextxy(450, 280, "人流量中");
			outtextxy(450, 440, "人流量高");
			outtextxy(480, 600, "返回");
		}
	}
	Sleep(500);
	return true;
}
//重新初始化乘客
void Manager::InitPeople(int i)
{
	this->people[i].start = rand() % 7;
	this->people[i].x = 0;
	this->people[i].y = this->bk.y[this->people[i].start][0] - 60;
	this->people[i].In = false;
	this->people[i].Get = false;
	this->people[i].end = rand() % 7;
	while (this->people[i].end == this->people[i].start)
		this->people[i].end = rand() % 7;
	this->people[i].Ispicture = true;
}
//显示按钮 模拟电梯函数使用
void Manager::ShowButton2()
{
	int arr[7];
	for (int i = 0; i < 7; i++)
		arr[i] = 0;
	for (int i = 0; i < people.size(); i++)
	{
		if (!this->people[i].Ispicture)
			continue;
		else
		{
			if (this->people[i].In)
				arr[this->people[i].end] = 1;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (arr[i] == 0)//如果该楼层无人前往，则按钮为灰色
			setfillcolor(RGB(249, 249, 249));
		else//如果该楼层有人前往，则按钮为黄色
			setfillcolor(YELLOW);
		fillcircle(this->button[i].x, this->button[i].y, 20);
	}
	settextcolor(BLACK);
	settextstyle(30, 0, "微软雅黑");
	for (int j = 0; j < 7; j++)
	{
		//打印按钮数字
		char ch = (j + 1) + '0';
		outtextxy(this->button[j].x - 5, this->button[j].y - 15, ch);
	}
}
//模拟高峰阶段电梯随机函数
void Manager::RandElevator()
{
	//打开记录文件
	ofstream ofs(FILE, ios::out | ios::app);
	bool flag = false;
	setbkcolor(RGB(30, 39, 80));
	while (1)
	{
		cleardevice();
		BeginBatchDraw();
		flag = false;
		this->num = 1;
		//判断电梯是否要停下
		for (int i = 0; i < people.size(); i++)
		{
			if (this->people[i].Ispicture)
			{
				if (this->people[i].start == this->elevator.floor
					&& !this->people[i].In && !this->people[i].Get)
				{
					flag = true;
					break;
				}
				else if (this->people[i].end == this->elevator.floor && this->people[i].In)
				{
					flag = true;
					break;
				}
			}
		}
		if (flag)
			this->elevator.Stop = true;
		else
			this->elevator.Stop = false;
		bool flag2 = true;
		for (int i = 0; i < this->people.size(); i++)
		{
			if (this->people[i].Ispicture && this->people[i].end == this->elevator.floor
				&& !this->people[i].Get)
				flag2 = false;
		}
		if (this->elevator.Stop)
		{
			//电梯停下时
			for (int i = 0; i < people.size(); i++)
			{
				if (this->people[i].Ispicture)
				{
					if (this->people[i].start == this->elevator.floor && !this->people[i].In)
					{
						this->people[i].x += 5;
						if (this->people[i].x >= this->people[i].ex)
						{
							this->people[i].In = true;
							//记录
							string nowtimes = this->getTime();
							ofs << i << " " << this->people[i].start << " "
								<< this->people[i].end << " " << nowtimes << endl;
						}
					}
					if (this->people[i].end == this->elevator.floor && this->people[i].In)
					{
						this->people[i].x -= 5;
						if (this->people[i].x < 350)
						{
							this->people[i].In = false;
							this->people[i].Get = true;
						}
					}
				}
			}
		}
		else
		{
			//电梯移动时
			if (this->elevator.flag == 0)
			{
				//电梯向上移动
				this->elevator.top -= 5;
				this->elevator.bottom -= 5;
				for (int i = 0; i < people.size(); i++)
				{
					if (this->people[i].In)
						this->people[i].y -= 5;
				}
				//到达下一层时，更新电梯当前楼层
				if (this->elevator.top == this->bk.y[this->elevator.floor + 1][0])
					this->elevator.floor++;
				//到达最顶层时，更改电梯方向
				if (this->elevator.floor == 6)
					this->elevator.flag = 1;
			}
			else
			{
				//电梯向下移动
				this->elevator.top += 5;
				this->elevator.bottom += 5;
				for (int i = 0; i < people.size(); i++)
				{
					if (this->people[i].In)
						this->people[i].y += 5;
				}
				//到达下一层时，更新电梯当前楼层
				if (this->elevator.top == this->bk.y[this->elevator.floor - 1][0])
					this->elevator.floor--;
				//到达最底层时，更新电梯移动方向
				if (this->elevator.floor == 0)
					this->elevator.flag = 0;
			}
		}
		if (this->IfReturn())
		{
			if (this->elevator.flag == 0)
				this->elevator.flag = 1;
			else
				this->elevator.flag = 0;
		}
		for (int i = 0; i < people.size(); i++)
		{
			if (this->people[i].Get)
			{
				if (this->people[i].x > -50)
				{
					this->people[i].x -= 5;
				}
				else
					this->people[i].Ispicture = false;
			}
			//else
			//	this->num++;
		}
		this->num = 0;
		for (int i = 0; i < people.size() / 2; i++)
		{
			if (this->people[i].Ispicture)
			{
				//this->InitPeople(i);
				this->num++;
			}
			else
			{
				if (this->times > 0)
				{
					this->InitPeople(i);
					this->times--;
				}
			}
		}
		if (this->num == 0)
			break;
		//画图
		this->Picture();
		//画按钮，显示要到达的楼层
		this->ShowButton2();
		EndBatchDraw();
		Sleep(30);
	}
	ofs.close();
}

//查找记录
void Manager::FindRecord()
{
	setbkcolor(RGB(30, 39, 80));
	settextstyle(30, 0, "微软雅黑");
	settextcolor(WHITE);
	cleardevice();
	MOUSEMSG msg;
	while (1)
	{
		setfillcolor(RGB(120, 173, 191));
		msg = GetMouseMsg();
		BeginBatchDraw();
		if ((msg.x - 320) * (msg.x - 320) + (msg.y - 180) * (msg.y - 180) <= 50 * 50)
		{
			fillcircle(540, 360, 50);
			fillcircle(760, 180, 50);
			fillcircle(320, 540, 50);
			fillcircle(760, 540, 50);
			setfillcolor(RGB(205, 205, 88));
			fillcircle(320, 180, 50);
			outtextxy(300, 165, "编号");
			outtextxy(740, 165, "起点");
			outtextxy(300, 525, "终点");
			outtextxy(740, 525, "时间");
			outtextxy(520, 345, "返回");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				this->FindId();
			}
		}
		else if ((msg.x - 760) * (msg.x - 760) + (msg.y - 180) * (msg.y - 180) <= 50 * 50)
		{
			fillcircle(540, 360, 50);
			fillcircle(320, 180, 50);
			fillcircle(320, 540, 50);
			fillcircle(760, 540, 50);
			setfillcolor(RGB(205, 205, 88));
			fillcircle(760, 180, 50);
			outtextxy(300, 165, "编号");
			outtextxy(740, 165, "起点");
			outtextxy(300, 525, "终点");
			outtextxy(740, 525, "时间");
			outtextxy(520, 345, "返回");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				this->FindStart();
			}
		}
		else if ((msg.x - 320) * (msg.x - 320) + (msg.y - 540) * (msg.y - 540) <= 50 * 50)
		{
			fillcircle(540, 360, 50);
			fillcircle(320, 180, 50);
			fillcircle(760, 180, 50);
			fillcircle(760, 540, 50);
			setfillcolor(RGB(205, 205, 88));
			fillcircle(320, 540, 50);
			outtextxy(300, 165, "编号");
			outtextxy(740, 165, "起点");
			outtextxy(300, 525, "终点");
			outtextxy(740, 525, "时间");
			outtextxy(520, 345, "返回");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				this->FindEnd();
			}
		}
		else if ((msg.x - 760) * (msg.x - 760) + (msg.y - 540) * (msg.y - 540) <= 50 * 50)
		{
			fillcircle(540, 360, 50);
			fillcircle(320, 180, 50);
			fillcircle(760, 180, 50);
			fillcircle(320, 540, 50);
			setfillcolor(RGB(205, 205, 88));
			fillcircle(760, 540, 50);
			outtextxy(300, 165, "编号");
			outtextxy(740, 165, "起点");
			outtextxy(300, 525, "终点");
			outtextxy(740, 525, "时间");
			outtextxy(520, 345, "返回");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				this->FindTime();
			}
		}
		else if ((msg.x - 540) * (msg.x - 540) + (msg.y - 360) * (msg.y - 360) <= 50 * 50)
		{
			fillcircle(320, 180, 50);
			fillcircle(760, 180, 50);
			fillcircle(320, 540, 50);
			fillcircle(760, 540, 50);
			setfillcolor(RGB(205, 205, 88));
			fillcircle(540, 360, 50);
			outtextxy(300, 165, "编号");
			outtextxy(740, 165, "起点");
			outtextxy(300, 525, "终点");
			outtextxy(740, 525, "时间");
			outtextxy(520, 345, "返回");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
				break;
		}
		else
		{
			fillcircle(540, 360, 50);
			fillcircle(320, 180, 50);
			fillcircle(760, 180, 50);
			fillcircle(320, 540, 50);
			fillcircle(760, 540, 50);
			outtextxy(300, 165, "编号");
			outtextxy(740, 165, "起点");
			outtextxy(300, 525, "终点");
			outtextxy(740, 525, "时间");
			outtextxy(520, 345, "返回");
			EndBatchDraw();
		}
	}
	cleardevice();
}
//编号查找
void Manager::FindId()
{
	ifstream ifs(FILE, ios::in);
	int id, start, end;
	string ttime;
	settextcolor(WHITE);
	settextstyle(30, 0, "微软雅黑");
	cleardevice();
	//获取输入
	char ch[3];
	InputBox(ch, 3, "请输入要查找的编号", "查找", 0, 200, 40);
	int findid = 0;
	findid = atoi(ch);
	MOUSEMSG msg;
	//记录条数
	int recordnum = 0;
	//存储记录的容器
	map<int, vector<Record>>m;
	//记录页数
	int index = 0;
	//临时记录
	Record temp;
	while (ifs >> id && ifs >> start && ifs >> end && ifs >> ttime)
	{
		if (findid == id)
		{
			temp.id = id;
			temp.start = start;
			temp.end = end;
			temp.times = ttime;
			//每一页打印17条记录
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//查无记录
	if (recordnum == 0)
	{
		this->NotFind();
	}
	else
	{
		int key = 0;
		while (1)
		{
			msg = GetMouseMsg();
			setfillcolor(BLUE);
			fillrectangle(1000, 0, 1080, 40);
			outtextxy(1005, 5, "返回");
			outtextxy(0, 0, "编号");
			outtextxy(100, 0, "起点");
			outtextxy(200, 0, "终点");
			outtextxy(300, 0, "时间");
			if (index > 0)
			{
				this->UpDownButton(key, index);
			}
			int y = 40;
			for (vector<Record>::iterator it = m[key].begin(); it != m[key].end(); it++)
			{
				outtextxy(0, y, to_string(it->id).c_str());
				outtextxy(100, y, (it->start + 1) + '0');
				outtextxy(200, y, (it->end + 1) + '0');
				outtextxy(300, y, it->times.c_str());
				y += 40;
			}
			if (index != 0)
			{
				//key等于0时没有上一页
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "上一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key--;
						cleardevice();
					}
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key等于index时没有下一页
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "下一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key++;
						cleardevice();
					}
				}
			}
			if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 0 && msg.y <= 40)
			{
				setfillcolor(RGB(205, 205, 88));
				fillrectangle(1000, 0, 1080, 40);
				outtextxy(1005, 5, "返回");
				if (msg.uMsg == WM_LBUTTONDOWN)
					break;
			}
		}
	}
	cleardevice();
	ifs.close();
}
void Manager::FindStart()
{
	cleardevice();
	settextcolor(WHITE);
	settextstyle(30, 0, "微软雅黑");
	char ch[2];
	InputBox(ch, 2, "请输入查找的起点", "查找", 0, 200, 40);
	int findstart = ch[0] - '0';
	int id, start, end;
	string ttime;
	ifstream ifs(FILE, ios::in);
	MOUSEMSG msg;
	//记录条数
	int recordnum = 0;
	//存储记录的容器
	map<int, vector<Record>>m;
	//记录页数
	int index = 0;
	//临时记录
	Record temp;
	while (ifs >> id && ifs >> start && ifs >> end && ifs >> ttime)
	{

		if (findstart == start + 1)
		{
			temp.id = id;
			temp.start = start;
			temp.end = end;
			temp.times = ttime;
			//每一页打印17条记录
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//查无记录
	if (recordnum == 0)
	{
		this->NotFind();
	}
	else
	{
		int key = 0;
		while (1)
		{
			msg = GetMouseMsg();
			setfillcolor(BLUE);
			fillrectangle(1000, 0, 1080, 40);
			outtextxy(1005, 5, "返回");
			outtextxy(0, 0, "编号");
			outtextxy(100, 0, "起点");
			outtextxy(200, 0, "终点");
			outtextxy(300, 0, "时间");
			if (index > 0)
			{
				this->UpDownButton(key, index);
			}
			int y = 40;
			for (vector<Record>::iterator it = m[key].begin(); it != m[key].end(); it++)
			{
				outtextxy(0, y, to_string(it->id).c_str());
				outtextxy(100, y, (it->start + 1) + '0');
				outtextxy(200, y, (it->end + 1) + '0');
				outtextxy(300, y, it->times.c_str());
				y += 40;
			}
			if (index != 0)
			{
				//key等于0时没有上一页
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "上一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key--;
						cleardevice();
					}
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key等于index时没有下一页
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "下一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key++;
						cleardevice();
					}
				}
			}
			if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 0 && msg.y <= 40)
			{
				setfillcolor(RGB(205, 205, 88));
				fillrectangle(1000, 0, 1080, 40);
				outtextxy(1005, 5, "返回");
				if (msg.uMsg == WM_LBUTTONDOWN)
					break;
			}
		}
	}
	cleardevice();
	ifs.close();
}
void Manager::FindEnd()
{
	cleardevice();
	settextcolor(WHITE);
	settextstyle(30, 0, "微软雅黑");
	char ch[2];
	InputBox(ch, 2, "请输入查找的终点", "查找", 0, 200, 40);
	int findend = ch[0] - '0';
	int id, start, end;
	string ttime;
	ifstream ifs(FILE, ios::in);
	MOUSEMSG msg;
	//记录条数
	int recordnum = 0;
	//存储记录的容器
	map<int, vector<Record>>m;
	//记录页数
	int index = 0;
	//临时记录
	Record temp;
	while (ifs >> id && ifs >> start && ifs >> end && ifs >> ttime)
	{
		if (findend == end + 1)
		{
			temp.id = id;
			temp.start = start;
			temp.end = end;
			temp.times = ttime;
			//每一页打印17条记录
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//查无记录
	if (recordnum == 0)
	{
		this->NotFind();
	}
	else
	{
		int key = 0;
		while (1)
		{
			msg = GetMouseMsg();
			setfillcolor(BLUE);
			fillrectangle(1000, 0, 1080, 40);
			outtextxy(1005, 5, "返回");
			outtextxy(0, 0, "编号");
			outtextxy(100, 0, "起点");
			outtextxy(200, 0, "终点");
			outtextxy(300, 0, "时间");
			if (index > 0)
			{
				this->UpDownButton(key, index);
			}
			int y = 40;
			for (vector<Record>::iterator it = m[key].begin(); it != m[key].end(); it++)
			{
				outtextxy(0, y, to_string(it->id).c_str());
				outtextxy(100, y, (it->start + 1) + '0');
				outtextxy(200, y, (it->end + 1) + '0');
				outtextxy(300, y, it->times.c_str());
				y += 40;
			}
			if (index != 0)
			{
				//key等于0时没有上一页
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "上一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key--;
						cleardevice();
					}
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key等于index时没有下一页
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "下一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key++;
						cleardevice();
					}
				}
			}
			if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 0 && msg.y <= 40)
			{
				setfillcolor(RGB(205, 205, 88));
				fillrectangle(1000, 0, 1080, 40);
				outtextxy(1005, 5, "返回");
				if (msg.uMsg == WM_LBUTTONDOWN)
					break;
			}
		}
	}
	cleardevice();
	ifs.close();
}
void Manager::FindTime()
{
	cleardevice();
	settextcolor(WHITE);
	settextstyle(30, 0, "微软雅黑");
	char ch[20];
	InputBox(ch, 20, "请输入查找的时间", "查找", 0, 200, 40);
	//记录查询时间的精度
	int jindu = 0;
	for (int i = 0; i < 20; i++)
	{
		if (ch[i] != '\0')
			jindu++;
		else
			break;
	}
	int id, start, end;
	string ttime;
	ifstream ifs(FILE, ios::in);
	MOUSEMSG msg;
	//记录条数
	int recordnum = 0;
	//存储记录的容器
	map<int, vector<Record>>m;
	//记录页数
	int index = 0;
	//临时记录
	Record temp;
	while (ifs >> id && ifs >> start && ifs >> end && ifs >> ttime)
	{
		bool flag = true;
		for (int i = 0; i < jindu; i++)
		{
			if (ch[i] != ttime[i])
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			temp.id = id;
			temp.start = start;
			temp.end = end;
			temp.times = ttime;
			//每一页打印17条记录
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//查无记录
	if (recordnum == 0)
	{
		this->NotFind();
	}
	else
	{
		//map键值设为0
		int key = 0;
		while (1)
		{
			cleardevice();
			BeginBatchDraw();
			setfillcolor(BLUE);
			fillrectangle(1000, 0, 1080, 40);
			outtextxy(1005, 5, "返回");
			msg = GetMouseMsg();
			ifs.seekg(0);
			outtextxy(0, 0, "编号");
			outtextxy(100, 0, "起点");
			outtextxy(200, 0, "终点");
			outtextxy(300, 0, "时间");
			if (index > 0)
			{
				this->UpDownButton(key, index);
			}
			int y = 40;
			for (vector<Record>::iterator it = m[key].begin(); it != m[key].end(); it++)
			{
				outtextxy(0, y, to_string(it->id).c_str());
				outtextxy(100, y, (it->start + 1) + '0');
				outtextxy(200, y, (it->end + 1) + '0');
				outtextxy(300, y, it->times.c_str());
				y += 40;
			}
			if (index != 0)
			{
				//key等于0时没有上一页
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "上一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
						key--;
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key等于index时没有下一页
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "下一页");
					if (msg.uMsg == WM_LBUTTONDOWN)
						key++;
				}
			}
			if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 0 && msg.y <= 40)
			{
				setfillcolor(RGB(205, 205, 88));
				fillrectangle(1000, 0, 1080, 40);
				outtextxy(1005, 5, "返回");
				if (msg.uMsg == WM_LBUTTONDOWN)
					break;
			}
			EndBatchDraw();
			//Sleep(30);
		}
	}
	cleardevice();
	ifs.close();
}
//查无记录
void Manager::NotFind()
{
	MOUSEMSG msg;
	settextcolor(WHITE);
	settextstyle(30, 0, "微软雅黑");
	while (1)
	{
		msg = GetMouseMsg();
		setfillcolor(BLUE);
		fillrectangle(1000, 0, 1060, 40);
		outtextxy(1005, 5, "返回");
		outtextxy(5, 5, "查无记录");
		if (msg.x >= 1000 && msg.x <= 1060 && msg.y >= 0 && msg.y <= 40)
		{
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(1000, 0, 1060, 40);
			outtextxy(1005, 5, "返回");
			if (msg.uMsg == WM_LBUTTONDOWN)
				break;
		}
	}
}
//画上一页和下一页按钮 第一个参数为map键值，第二个是页数
void Manager::UpDownButton(int key, int index)
{
	if (key < index)
	{
		setfillcolor(BLUE);
		fillrectangle(1000, 160, 1080, 200);
		outtextxy(1005, 165, "下一页");
		if (key != 0)
		{
			setfillcolor(BLUE);
			fillrectangle(1000, 80, 1080, 120);
			outtextxy(1005, 85, "上一页");
		}
	}
	else if (key == index)
	{
		fillrectangle(1000, 80, 1080, 120);
		outtextxy(1005, 85, "上一页");
	}
}
//退出系统
void Manager::Exit()
{
	setbkcolor(RGB(30, 39, 80));
	cleardevice();
	settextstyle(50, 0, "微软雅黑");
	settextcolor(RGB(249, 249, 249));
	outtextxy(440, 330, "已退出");
	_getch();
	exit(0);
}
