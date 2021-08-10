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
//���ݳ�����Ϣ��¼�ļ�
#define FILE "record.txt"
struct Record
{
	//�˿ͱ��
	int id;
	//���
	int start;
	//�յ�
	int end;
	//�������ݵ�ʱ��
	string times;
};
//�����ṹ��
struct BK
{
	//¥��x����
	int x[7][2];
	//¥��y����
	int y[7][2];
};
//���ݽṹ��
struct Elevator
{
	//���ݵ�ǰ¥��
	int floor;
	//������������
	int top;
	int bottom;
	int left;
	int right;
	//�жϵ����Ƿ�ͣ��
	bool Stop;
	//�����ƶ�����
	int flag;
};
//���ݰ�ť�ṹ��
struct Button
{
	//��ťԲ��x����
	int x;
	//��ťԲ��y����
	int y;
};
//�˿ͽṹ��
struct People
{
	//ͼƬ
	IMAGE img;
	//��ʼ¥��
	int start;
	//�յ�¥��
	int end;
	//x����
	int x;
	//y����
	int y;
	//�Ƿ��ڵ�����
	bool In;
	//�Ƿ񵽴�Ŀ��¥��
	bool Get;
	//�ڵ�����վ����λ��
	int ex;
	//�Ƿ񻭳˿�
	bool Ispicture;
};
//������
class Manager
{
private:
	Button button[7];
	//People people[13];
	vector<People>people;
	BK bk;
	Elevator elevator;
	//��¼�˿�����
	int num;
	//ģ��������д���
	int times;
public:
	Manager();
	//��ȡ��ǰϵͳʱ��
	string getTime();
	//�жϵ����Ƿ���Ե�ͷ
	bool IfReturn();
	//��ʼ���˿�
	void InitPeople();
	//�˵���
	void Menu();
	//��ͼ����
	void Picture();
	//���غ���
	void Load();
	//��ʾ��ť �������ݺ���ʹ��
	void ShowButton1();
	//���ݳ�������
	void TakeElevator();
	//���³�ʼ���˿�����
	bool InitPeopleNum();
	//���³�ʼ���˿�
	void InitPeople(int i);
	//��ʾ��ť ģ����ݺ���ʹ��
	void ShowButton2();
	//ģ��߷�׶ε����������
	void RandElevator();
	//���Ҽ�¼
	void FindRecord();
	//��Ų���
	void FindId();
	//������
	void FindStart();
	//�յ����
	void FindEnd();
	//ʱ�����
	void FindTime();
	//���޼�¼
	void NotFind();
	//����һҳ����һҳ��ť ��һ������Ϊmap��ֵ���ڶ�����ҳ��
	void UpDownButton(int key, int index);
	//�˳�����ϵͳ
	void Exit();
};
#endif