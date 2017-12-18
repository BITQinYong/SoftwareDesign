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
	cout << "                                ‖                                                                     ‖" << endl;
	cout << "                                ‖                         欢迎使用BeOne数据库系统                     ‖" << endl;
	cout << "                                ‖                                                                     ‖" << endl;
	cout << "                                ‖               打开操作指南：help;       查询历史操作：history;      ‖" << endl;
	cout << "                                ‖                                                                     ‖" << endl;
	cout << "                                 =======================================================================" << endl;

	while (1)
	{

		command = input();

		if (command == "quit;") break;
		else syntax_analysis(command);
	}

}
