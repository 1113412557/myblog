#include "stdafx.h"
#include "Monitor.h"


Monitor::Monitor()
{
	buffer = new char[20];
	count = 0;
	nextin = 0;
	nextout = 0;
	NUM = 0;
	/*���������ź������ź����ֱ���'notempty''notfull'*/
	notempty = CreateSemaphore(NULL, 0, 1,_T("notem"));
	notfull = CreateSemaphore(NULL, 20, 20, _T("notfu"));
	control = CreateSemaphore(NULL, 1, 1, _T("ct"));
}


Monitor::~Monitor()
{
	CloseHandle(notfull);
	CloseHandle(notempty);
	CloseHandle(control);
}
/*��������д���ݣ�ǰ���ǵõõ�notfull�ź����Ҽ�contr�ź��������д����֮�󣬸���Ӧ���ź���������Ӧ��ֵ*/
void Monitor::Append(char x)
{
	static int p_count = 1;
	int p = p_count++;
	while (1)
	{
		P(notfull);
		P(control);
		buffer[nextin] = x;
		nextin = (nextin + 1) % bufferlength;
		count++;
		Wait(p, 1, 3, "�����߿�ʼ������Ʒ");
		Wait(p, 1, 3, "�������������Ʒ");
		V(control);
		V(notempty);
	}
}
/*�ӻ������ж����ݣ�ǰ���ǻ��notempty�Լ�control�ź�������ɶ�����֮��Ҫ��control�ź�����notfull�ź�������Ӧ���޸�*/
void Monitor::Take()
{
	static int c_count = 1;
	int c = count++;
	while (1)
	{
		P(notempty);
		P(control);
		char x;
		x = buffer[nextout];
		nextout = (nextout + 1) % bufferlength;
		count--;
		Wait(c, 1, 2, "�����������������߿�ʼ���Ѳ�Ʒ");
		Wait(c, 1, 2, "�������������������������Ʒ");
		V(control);
		V(notempty);
	}
}
void Monitor::Wait(int NUM, int min, int max, LPCSTR info)
{
	char s_out[128];
	const int BASETIME = 500;
	int wait_time = 0;
		if (max == min)
			wait_time = min * BASETIME;
		else
			wait_time = rand() % (max*BASETIME - min * BASETIME) + min * BASETIME;
	sprintf_s(s_out, "No%d%s\n", NUM, info);
	printf(s_out);
	Sleep(wait_time);
}
