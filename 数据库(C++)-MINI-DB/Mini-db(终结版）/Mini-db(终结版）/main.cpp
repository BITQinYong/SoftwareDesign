#include<iostream>
#include<string>
#include<regex>
#include"syntax.h"
#include"support.h"

using namespace std;



int main()
{
	string command;
	cout << "                                 =======================================================================" << endl;
	cout << "                                ��                                                                     ��" << endl;
	cout << "                                ��                         ��ӭʹ��BeOne���ݿ�ϵͳ                     ��" << endl;
	cout << "                                ��                                                                     ��" << endl;
	cout << "                                ��               �򿪲���ָ�ϣ�help;       ��ѯ��ʷ������history;      ��" << endl;
	cout << "                                ��                                                                     ��" << endl;
	cout << "                                 =======================================================================" << endl;

	while (1)
	{

		command = input();

		if (command == "quit;") break;
		else syntax_analysis(command);
	}

}
