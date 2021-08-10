#ifndef MANAGER_H
#define MANAGER_H
#include<graphics.h>
#include<string>
#include<conio.h>
#include<mmsystem.h>
#include<stdio.h>
#include<ctime>
#include<Windows.h>
#include<vector>
#include<algorithm>
#include<fstream>
#include<cstdlib>
#include<map>
using namespace std;
#pragma comment(lib,"winmm.lib")
//电梯乘坐信息记录文件
#define FILE "record.txt"
struct Record
{
	//乘客编号
	int id;
	//起点
	int start;
	//终点
	int end;
	//乘坐电梯的时间
	string times;
};
//背景结构体
struct BK
{
	//楼层x坐标
	int x[7][2];
	//楼层y坐标
	int y[7][2];
};
//电梯结构体
struct Elevator
{
	//电梯当前楼层
	int floor;
	//上下左右坐标
	int top;
	int bottom;
	int left;
	int right;
	//判断电梯是否停下
	bool Stop;
	//电梯移动方向
	int flag;
};
//电梯按钮结构体
struct Button
{
	//按钮圆心x坐标
	int x;
	//按钮圆心y坐标
	int y;
};
//乘客结构体
struct People
{
	//图片
	IMAGE img;
	//起始楼层
	int start;
	//终点楼层
	int end;
	//x坐标
	int x;
	//y坐标
	int y;
	//是否在电梯内
	bool In;
	//是否到达目标楼层
	bool Get;
	//在电梯中站立的位置
	int ex;
	//是否画乘客
	bool Ispicture;
};
//管理类
class Manager
{
private:
	Button button[7];
	//People people[13];
	vector<People>people;
	BK bk;
	Elevator elevator;
	//记录乘客人数
	int num;
	//模拟电梯运行次数
	int times;
public:
	Manager();
	//获取当前系统时间
	string getTime();
	//判断电梯是否可以掉头
	bool IfReturn();
	//初始化乘客
	void InitPeople();
	//菜单栏
	void Menu();
	//画图函数
	void Picture();
	//加载函数
	void Load();
	//显示按钮 乘坐电梯函数使用
	void ShowButton1();
	//电梯乘坐函数
	void TakeElevator();
	//重新初始化乘客数量
	bool InitPeopleNum();
	//重新初始化乘客
	void InitPeople(int i);
	//显示按钮 模拟电梯函数使用
	void ShowButton2();
	//模拟高峰阶段电梯随机函数
	void RandElevator();
	//查找记录
	void FindRecord();
	//编号查找
	void FindId();
	//起点查找
	void FindStart();
	//终点查找
	void FindEnd();
	//时间查找
	void FindTime();
	//查无记录
	void NotFind();
	//画上一页和下一页按钮 第一个参数为map键值，第二个是页数
	void UpDownButton(int key, int index);
	//退出电梯系统
	void Exit();
};
#endif