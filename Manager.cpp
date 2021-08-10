#include"Manager.h"
#include<iostream>
using namespace std;
Manager::Manager()
{
	this->num = 13;
	this->times = 5 + rand() % 10;
	//��ʼ������
	for (int i = 0; i < 7; i++)
	{
		this->bk.x[i][0] = 0;
		this->bk.x[i][1] = 400;
		this->bk.y[i][0] = 695 - 100 * i;
		this->bk.y[i][1] = 700 - 100 * i;
	}
	//��ʼ������
	this->elevator.floor = 0;
	this->elevator.left = 400;
	this->elevator.right = 600;
	this->elevator.top = this->bk.y[this->elevator.floor][0];
	this->elevator.bottom = this->bk.y[this->elevator.floor][1];
	this->elevator.Stop = false;
	this->elevator.flag = 0;//0Ϊ���ϣ�1Ϊ����
	//��ʼ����ť
	for (int i = 0; i < 7; i++)
	{
		this->button[i].x = 800 + 60 * (i % 4);
		this->button[i].y = 40 + (i / 4) * 60;
	}
	//��ʼ���˿�
	this->InitPeople();
}
//��ȡ��ǰϵͳʱ��
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
//�жϵ����Ƿ���Ե�ͷ
bool Manager::IfReturn()
{
	if (this->elevator.flag == 0)
	{
		//���������˶�ʱ
		for (int i = 0; i < this->people.size(); i++)
		{
			//������������¥������Ҫ���ҵ���
			if (this->people[i].start > this->elevator.floor
				&& this->people[i].Ispicture && !this->people[i].In)
				return false;
			//�������Ҫ�ӵ��������¥���µ���
			if (this->people[i].end > this->elevator.floor
				&& this->people[i].Ispicture && this->people[i].In)
				return false;
		}
	}
	else
	{
		//���������˶�ʱ
		for (int i = 0; i < this->people.size(); i++)
		{
			//������������¥������Ҫ������
			if (this->people[i].start < this->elevator.floor
				&& this->people[i].Ispicture && !this->people[i].In)
				return false;
			//�������Ҫ�ӵ��������¥���µ���
			if (this->people[i].end < this->elevator.floor
				&& this->people[i].Ispicture && this->people[i].In)
				return false;
		}
	}
	//���û��
	if (this->num == 0)
		return false;
	return true;
}
//��ʼ���˿�
void Manager::InitPeople()
{
	//���people����
	people.clear();
	People p;
	//�˿�������Ϊ13��ģ��������������
	for (int i = 0; i < 13; i++)
	{
		//���س˿�ͼƬ
		loadimage(&p.img, "�˿�.png", 40, 60);
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
//���ݲ˵�����
void Manager::Menu()
{
	MOUSEMSG msg;
	setbkcolor(RGB(30, 39, 80));
	while (1)
	{
		setfillcolor(BLUE);
		settextstyle(40, 0, "΢���ź�");
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
			outtextxy(450, 80, "���ݳ���");
			outtextxy(450, 240, "ģ�����");
			outtextxy(450, 400, "��ѯ��¼");
			outtextxy(450, 560, "�˳�ϵͳ");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//���غ���
				this->Load();
				//��������
				this->TakeElevator();
				//���³�ʼ���˿�
				this->InitPeople();
				//���³�ʼ������
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
			outtextxy(450, 80, "���ݳ���");
			outtextxy(450, 240, "ģ�����");
			outtextxy(450, 400, "��ѯ��¼");
			outtextxy(450, 560, "�˳�ϵͳ");
			BeginBatchDraw();
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//����������
				if (this->InitPeopleNum())
				{
					//���غ���
					this->Load();
					//ģ�����
					this->RandElevator();
				}
				//���³�ʼ���˿�
				this->InitPeople();
				//���³�ʼ������
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
			outtextxy(450, 80, "���ݳ���");
			outtextxy(450, 240, "ģ�����");
			outtextxy(450, 400, "��ѯ��¼");
			outtextxy(450, 560, "�˳�ϵͳ");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//���Ҽ�¼
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
			outtextxy(450, 80, "���ݳ���");
			outtextxy(450, 240, "ģ�����");
			outtextxy(450, 400, "��ѯ��¼");
			outtextxy(450, 560, "�˳�ϵͳ");
			EndBatchDraw();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//�˳�����ϵͳ
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
			outtextxy(450, 80, "���ݳ���");
			outtextxy(450, 240, "ģ�����");
			outtextxy(450, 400, "��ѯ��¼");
			outtextxy(450, 560, "�˳�ϵͳ");
			EndBatchDraw();
		}
	}
}
//��ͼ����
void Manager::Picture()
{
	setfillcolor(RGB(116, 118, 117));
	//������
	for (int i = 0; i < 7; i++)
	{
		fillrectangle(this->bk.x[i][0], this->bk.y[i][0],
			this->bk.x[i][1], this->bk.y[i][1]);
	}
	//������
	fillrectangle(this->elevator.left, this->elevator.top,
		this->elevator.right, this->elevator.bottom);
	fillrectangle(this->elevator.left, this->elevator.top - 100,
		this->elevator.left + 5, this->elevator.top);
	fillrectangle(this->elevator.right - 5, this->elevator.top - 100,
		this->elevator.right, this->elevator.top);
	fillrectangle(this->elevator.left, this->elevator.top - 100,
		this->elevator.right, this->elevator.bottom - 100);
	//���˿�
	for (int i = 0; i < people.size(); i++)
	{
		if (this->people[i].Ispicture)
			putimage(this->people[i].x, this->people[i].y, &this->people[i].img);
	}
}
//���غ���
void Manager::Load()
{
	IMAGE img;
	loadimage(&img, "����2.jpg", 1080, 720);
	settextstyle(50, 0, "΢���ź�");
	settextcolor(WHITE);
	putimage(0, 0, &img);
	outtextxy(450, 550, "������...");
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
//��ʾ���ݰ�ť
void Manager::ShowButton1()
{
	int arr[7];
	for (int i = 0; i < 7; i++)
		arr[i] = 0;
	for (int i = 0; i < people.size(); i++)
	{
		//���Ϊ�����յ㣬ֱ������
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
		if (arr[j] == 0)//�����¥��û��ǰ������ð�ť��ʾ��ɫ
			setfillcolor(RGB(249, 249, 249));
		else//�����¥������ǰ������ð�ť��ʾ��ɫ
			setfillcolor(YELLOW);
		//��ӡ��ť
		fillcircle(this->button[j].x, this->button[j].y, 20);
	}
	settextcolor(BLACK);
	settextstyle(30, 0, "΢���ź�");
	for (int j = 0; j < 7; j++)
	{
		//��ӡ��ť����
		char ch = (j + 1) + '0';
		outtextxy(this->button[j].x - 5, this->button[j].y - 15, ch);
	}
}
//���ݳ�������
void Manager::TakeElevator()
{
	//�򿪼�¼�ļ�
	ofstream ofs(FILE, ios::out | ios::app);
	setbkcolor(RGB(30, 39, 80));
	//�����г˿͵��յ�վ��Ϊ-1����ʾδ�����յ�վ
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
				//���ݵ����¥���ҳ˿�Ϊ������ʱ
				if (this->people[i].start == this->elevator.floor && !this->people[i].In)
				{
					flag = true;
					break;
				}
				else if (this->people[i].start == this->elevator.floor && this->people[i].In
					&& this->people[i].end == -1)//�˿��ڵ����ڵ��ǳ˿�Ϊ�����յ�λ��ʱ
				{
					flag = true;
					break;
				}
				else if (this->people[i].end == this->elevator.floor && this->people[i].In)
				{
					//�˿͵����յ�վʱ
					flag = true;
					break;
				}
			}
		}
		//�жϵ����Ƿ�Ҫͣ��
		if (flag)
			this->elevator.Stop = true;
		else
			this->elevator.Stop = false;
		//������ͣ��ʱ
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
			//��ͼ
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
						//�˿ͽ�����ݺ��������յ�վ
						InputBox(ch, 2, "�������յ㣺", "����", 0, 100, 40);
						this->people[i].end = (ch[0] - '0') - 1;
						//���壬��ʾ�Ѿ����ú��յ�վ
						cout << '\a';
						//��¼ ��� ��� �յ� ʱ��
						string nowtimes = this->getTime();
						ofs << i << " " << this->people[i].start << " "
							<< this->people[i].end << " " << nowtimes << endl;
					}
				}
			}
			//����ť
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
//���³�ʼ���˿�����
bool Manager::InitPeopleNum()
{
	setbkcolor(RGB(30, 39, 80));
	cleardevice();
	MOUSEMSG msg;
	settextcolor(WHITE);
	settextstyle(40, 0, "΢���ź�");
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
			outtextxy(450, 120, "��������");
			outtextxy(450, 280, "��������");
			outtextxy(450, 440, "��������");
			outtextxy(480, 600, "����");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//ģ�����������
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
			outtextxy(450, 120, "��������");
			outtextxy(450, 280, "��������");
			outtextxy(450, 440, "��������");
			outtextxy(480, 600, "����");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//ģ������������
				//����֮ǰ�Ѿ�����Ϊ13�ˣ����������������ֱ������
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
			outtextxy(450, 120, "��������");
			outtextxy(450, 280, "��������");
			outtextxy(450, 440, "��������");
			outtextxy(480, 600, "����");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//ģ��϶�������
				this->people.clear();
				People p;
				for (int i = 0; i < 20; i++)
				{
					//���س˿�ͼƬ
					loadimage(&p.img, "�˿�.png", 40, 60);
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
			outtextxy(450, 120, "��������");
			outtextxy(450, 280, "��������");
			outtextxy(450, 440, "��������");
			outtextxy(480, 600, "����");
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
			outtextxy(450, 120, "��������");
			outtextxy(450, 280, "��������");
			outtextxy(450, 440, "��������");
			outtextxy(480, 600, "����");
		}
	}
	Sleep(500);
	return true;
}
//���³�ʼ���˿�
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
//��ʾ��ť ģ����ݺ���ʹ��
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
		if (arr[i] == 0)//�����¥������ǰ������ťΪ��ɫ
			setfillcolor(RGB(249, 249, 249));
		else//�����¥������ǰ������ťΪ��ɫ
			setfillcolor(YELLOW);
		fillcircle(this->button[i].x, this->button[i].y, 20);
	}
	settextcolor(BLACK);
	settextstyle(30, 0, "΢���ź�");
	for (int j = 0; j < 7; j++)
	{
		//��ӡ��ť����
		char ch = (j + 1) + '0';
		outtextxy(this->button[j].x - 5, this->button[j].y - 15, ch);
	}
}
//ģ��߷�׶ε����������
void Manager::RandElevator()
{
	//�򿪼�¼�ļ�
	ofstream ofs(FILE, ios::out | ios::app);
	bool flag = false;
	setbkcolor(RGB(30, 39, 80));
	while (1)
	{
		cleardevice();
		BeginBatchDraw();
		flag = false;
		this->num = 1;
		//�жϵ����Ƿ�Ҫͣ��
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
			//����ͣ��ʱ
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
							//��¼
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
			//�����ƶ�ʱ
			if (this->elevator.flag == 0)
			{
				//���������ƶ�
				this->elevator.top -= 5;
				this->elevator.bottom -= 5;
				for (int i = 0; i < people.size(); i++)
				{
					if (this->people[i].In)
						this->people[i].y -= 5;
				}
				//������һ��ʱ�����µ��ݵ�ǰ¥��
				if (this->elevator.top == this->bk.y[this->elevator.floor + 1][0])
					this->elevator.floor++;
				//�������ʱ�����ĵ��ݷ���
				if (this->elevator.floor == 6)
					this->elevator.flag = 1;
			}
			else
			{
				//���������ƶ�
				this->elevator.top += 5;
				this->elevator.bottom += 5;
				for (int i = 0; i < people.size(); i++)
				{
					if (this->people[i].In)
						this->people[i].y += 5;
				}
				//������һ��ʱ�����µ��ݵ�ǰ¥��
				if (this->elevator.top == this->bk.y[this->elevator.floor - 1][0])
					this->elevator.floor--;
				//������ײ�ʱ�����µ����ƶ�����
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
		//��ͼ
		this->Picture();
		//����ť����ʾҪ�����¥��
		this->ShowButton2();
		EndBatchDraw();
		Sleep(30);
	}
	ofs.close();
}

//���Ҽ�¼
void Manager::FindRecord()
{
	setbkcolor(RGB(30, 39, 80));
	settextstyle(30, 0, "΢���ź�");
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
			outtextxy(300, 165, "���");
			outtextxy(740, 165, "���");
			outtextxy(300, 525, "�յ�");
			outtextxy(740, 525, "ʱ��");
			outtextxy(520, 345, "����");
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
			outtextxy(300, 165, "���");
			outtextxy(740, 165, "���");
			outtextxy(300, 525, "�յ�");
			outtextxy(740, 525, "ʱ��");
			outtextxy(520, 345, "����");
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
			outtextxy(300, 165, "���");
			outtextxy(740, 165, "���");
			outtextxy(300, 525, "�յ�");
			outtextxy(740, 525, "ʱ��");
			outtextxy(520, 345, "����");
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
			outtextxy(300, 165, "���");
			outtextxy(740, 165, "���");
			outtextxy(300, 525, "�յ�");
			outtextxy(740, 525, "ʱ��");
			outtextxy(520, 345, "����");
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
			outtextxy(300, 165, "���");
			outtextxy(740, 165, "���");
			outtextxy(300, 525, "�յ�");
			outtextxy(740, 525, "ʱ��");
			outtextxy(520, 345, "����");
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
			outtextxy(300, 165, "���");
			outtextxy(740, 165, "���");
			outtextxy(300, 525, "�յ�");
			outtextxy(740, 525, "ʱ��");
			outtextxy(520, 345, "����");
			EndBatchDraw();
		}
	}
	cleardevice();
}
//��Ų���
void Manager::FindId()
{
	ifstream ifs(FILE, ios::in);
	int id, start, end;
	string ttime;
	settextcolor(WHITE);
	settextstyle(30, 0, "΢���ź�");
	cleardevice();
	//��ȡ����
	char ch[3];
	InputBox(ch, 3, "������Ҫ���ҵı��", "����", 0, 200, 40);
	int findid = 0;
	findid = atoi(ch);
	MOUSEMSG msg;
	//��¼����
	int recordnum = 0;
	//�洢��¼������
	map<int, vector<Record>>m;
	//��¼ҳ��
	int index = 0;
	//��ʱ��¼
	Record temp;
	while (ifs >> id && ifs >> start && ifs >> end && ifs >> ttime)
	{
		if (findid == id)
		{
			temp.id = id;
			temp.start = start;
			temp.end = end;
			temp.times = ttime;
			//ÿһҳ��ӡ17����¼
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//���޼�¼
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
			outtextxy(1005, 5, "����");
			outtextxy(0, 0, "���");
			outtextxy(100, 0, "���");
			outtextxy(200, 0, "�յ�");
			outtextxy(300, 0, "ʱ��");
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
				//key����0ʱû����һҳ
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "��һҳ");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key--;
						cleardevice();
					}
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key����indexʱû����һҳ
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "��һҳ");
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
				outtextxy(1005, 5, "����");
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
	settextstyle(30, 0, "΢���ź�");
	char ch[2];
	InputBox(ch, 2, "��������ҵ����", "����", 0, 200, 40);
	int findstart = ch[0] - '0';
	int id, start, end;
	string ttime;
	ifstream ifs(FILE, ios::in);
	MOUSEMSG msg;
	//��¼����
	int recordnum = 0;
	//�洢��¼������
	map<int, vector<Record>>m;
	//��¼ҳ��
	int index = 0;
	//��ʱ��¼
	Record temp;
	while (ifs >> id && ifs >> start && ifs >> end && ifs >> ttime)
	{

		if (findstart == start + 1)
		{
			temp.id = id;
			temp.start = start;
			temp.end = end;
			temp.times = ttime;
			//ÿһҳ��ӡ17����¼
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//���޼�¼
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
			outtextxy(1005, 5, "����");
			outtextxy(0, 0, "���");
			outtextxy(100, 0, "���");
			outtextxy(200, 0, "�յ�");
			outtextxy(300, 0, "ʱ��");
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
				//key����0ʱû����һҳ
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "��һҳ");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key--;
						cleardevice();
					}
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key����indexʱû����һҳ
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "��һҳ");
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
				outtextxy(1005, 5, "����");
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
	settextstyle(30, 0, "΢���ź�");
	char ch[2];
	InputBox(ch, 2, "��������ҵ��յ�", "����", 0, 200, 40);
	int findend = ch[0] - '0';
	int id, start, end;
	string ttime;
	ifstream ifs(FILE, ios::in);
	MOUSEMSG msg;
	//��¼����
	int recordnum = 0;
	//�洢��¼������
	map<int, vector<Record>>m;
	//��¼ҳ��
	int index = 0;
	//��ʱ��¼
	Record temp;
	while (ifs >> id && ifs >> start && ifs >> end && ifs >> ttime)
	{
		if (findend == end + 1)
		{
			temp.id = id;
			temp.start = start;
			temp.end = end;
			temp.times = ttime;
			//ÿһҳ��ӡ17����¼
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//���޼�¼
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
			outtextxy(1005, 5, "����");
			outtextxy(0, 0, "���");
			outtextxy(100, 0, "���");
			outtextxy(200, 0, "�յ�");
			outtextxy(300, 0, "ʱ��");
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
				//key����0ʱû����һҳ
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "��һҳ");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						key--;
						cleardevice();
					}
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key����indexʱû����һҳ
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "��һҳ");
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
				outtextxy(1005, 5, "����");
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
	settextstyle(30, 0, "΢���ź�");
	char ch[20];
	InputBox(ch, 20, "��������ҵ�ʱ��", "����", 0, 200, 40);
	//��¼��ѯʱ��ľ���
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
	//��¼����
	int recordnum = 0;
	//�洢��¼������
	map<int, vector<Record>>m;
	//��¼ҳ��
	int index = 0;
	//��ʱ��¼
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
			//ÿһҳ��ӡ17����¼
			index = recordnum / 17;
			m[index].push_back(temp);
			recordnum++;
		}
	}
	//���޼�¼
	if (recordnum == 0)
	{
		this->NotFind();
	}
	else
	{
		//map��ֵ��Ϊ0
		int key = 0;
		while (1)
		{
			cleardevice();
			BeginBatchDraw();
			setfillcolor(BLUE);
			fillrectangle(1000, 0, 1080, 40);
			outtextxy(1005, 5, "����");
			msg = GetMouseMsg();
			ifs.seekg(0);
			outtextxy(0, 0, "���");
			outtextxy(100, 0, "���");
			outtextxy(200, 0, "�յ�");
			outtextxy(300, 0, "ʱ��");
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
				//key����0ʱû����һҳ
				if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 80 && msg.y <= 120 && key != 0)
				{
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 80, 1080, 120);
					outtextxy(1005, 85, "��һҳ");
					if (msg.uMsg == WM_LBUTTONDOWN)
						key--;
				}
				else if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 160 && msg.y <= 200 && key != index)
				{
					//key����indexʱû����һҳ
					setfillcolor(RGB(205, 205, 88));
					fillrectangle(1000, 160, 1080, 200);
					outtextxy(1005, 165, "��һҳ");
					if (msg.uMsg == WM_LBUTTONDOWN)
						key++;
				}
			}
			if (msg.x >= 1000 && msg.x <= 1080 && msg.y >= 0 && msg.y <= 40)
			{
				setfillcolor(RGB(205, 205, 88));
				fillrectangle(1000, 0, 1080, 40);
				outtextxy(1005, 5, "����");
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
//���޼�¼
void Manager::NotFind()
{
	MOUSEMSG msg;
	settextcolor(WHITE);
	settextstyle(30, 0, "΢���ź�");
	while (1)
	{
		msg = GetMouseMsg();
		setfillcolor(BLUE);
		fillrectangle(1000, 0, 1060, 40);
		outtextxy(1005, 5, "����");
		outtextxy(5, 5, "���޼�¼");
		if (msg.x >= 1000 && msg.x <= 1060 && msg.y >= 0 && msg.y <= 40)
		{
			setfillcolor(RGB(205, 205, 88));
			fillrectangle(1000, 0, 1060, 40);
			outtextxy(1005, 5, "����");
			if (msg.uMsg == WM_LBUTTONDOWN)
				break;
		}
	}
}
//����һҳ����һҳ��ť ��һ������Ϊmap��ֵ���ڶ�����ҳ��
void Manager::UpDownButton(int key, int index)
{
	if (key < index)
	{
		setfillcolor(BLUE);
		fillrectangle(1000, 160, 1080, 200);
		outtextxy(1005, 165, "��һҳ");
		if (key != 0)
		{
			setfillcolor(BLUE);
			fillrectangle(1000, 80, 1080, 120);
			outtextxy(1005, 85, "��һҳ");
		}
	}
	else if (key == index)
	{
		fillrectangle(1000, 80, 1080, 120);
		outtextxy(1005, 85, "��һҳ");
	}
}
//�˳�ϵͳ
void Manager::Exit()
{
	setbkcolor(RGB(30, 39, 80));
	cleardevice();
	settextstyle(50, 0, "΢���ź�");
	settextcolor(RGB(249, 249, 249));
	outtextxy(440, 330, "���˳�");
	_getch();
	exit(0);
}
