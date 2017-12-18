#pragma once
#include<string>
#include<iostream>
#include<regex>
#include<iomanip>
#include"data_structure.h"
using namespace std;
regex pattern("^.*[^/];$");//���в���������ʽ
regex r_date("(^([0-9])([0-9])([0-9])([0-9])([-])([0-1])([0-9])([-])([0-3])([0-9]))$", regex::icase);
string input();
bool type_judge(string type[], int);
bool type_data_judge(string, int);
bool output(Table *);
bool output_order(Table *);
bool output_logic(Table *);
bool output_logic_order(Table *);



string input()//����
{
	string str;
	string command;
	while (getline(cin, str))
	{
		command = command + str;
		if (regex_match(str, pattern))
		{
			break;
		}
	}
	return command;
}

bool type_judge(string type[], int flied_num)//�ڽ���ʱ�����͵ļ��
{
	for (int i = 1; i <= flied_num; i++)
	{
		if (type[i] != "char"&&type[i] != "int"&&type[i] != "float"&&type[i] != "date"&&type[i] != "bool")
			return false;
	}
	return true;
}

bool type_data_judge(string data, int type)//���������͸�ʽ�ļ��
{
	smatch results;

	//string stringname;
	if (data == "-1")return true;

	if (type == 3)
	{
		 if (regex_search(data, results, r_date))
			return true;
		else
		{
			/*cout << data << endl;*/
			cout << "Error: Wrong date format." << endl;;
			return false;
		}

	}
	if (type == 4)
	{
		if (data != "FALSE"&&data != "TRUE")
		{
			cout << "Error: Wrong bool format." << endl;
			return false;
		}
		else return true;
	}
	return true;
}

bool output(Table * table_now)//select_all ���
{

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	cout << '|';
	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << setw(10) << table_now->table_head[i] << "|";
	}
	cout << endl;

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;


	int cnt = 0;
	for (int i = 1; i <= table_now->max_line_num; i++)
	{
		if (table_now->Map[i].is_exist)
		{
			cout << '|';
			for (int j = 0; j < table_now->table_head_number; j++)
			{
				cout << setw(10) << table_now->Map[i].data_list[j] << "|";
			}
			cout << endl;
			cnt++;
		}
		else continue;
	}

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	cout << "Done. Found " << cnt << " records." << endl;;
	return true;
}

bool output_order(Table * table_now)//select_all_order ���
{
	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	cout << '|';

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << setw(10) << table_now->table_head[i] << "|";
	}
	cout << endl;

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	int end = 0;
	int cnt = 0;
	for (unsigned int i = 0; i< table_now->ans_order.size(); i++)
	{
		int tmp = table_now->ans_order[i];//���
		if (table_now->Map[tmp].is_exist == false)continue;
		end = table_now->Map[tmp].data_list.size();
		cout << '|';
		for (int j = 0; j < end; j++){
			cout << setw(10) << table_now->Map[tmp].data_list[j] << '|';
		}
		cnt++;
		cout << endl;
	}

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	cout << "Done. Found " << cnt << " records." << endl;
	return true;
}

bool output_logic(Table * table_now)//select(����where) ���
{
	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	cout << '|';
	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << setw(10) << table_now->table_head[i] << "|";
	}
	cout << endl;

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	set<int> ::iterator it;
	int end = 0;
	int cnt = 0;
	for (it = table_now->ans_list.begin(); it != table_now->ans_list.end(); it++){
		if (table_now->Map[*it].is_exist == false)continue;
		end = table_now->Map[*it].data_list.size();
		cout << "|";
		for (int i = 0; i < end; i++){
			cout << setw(10) << table_now->Map[*it].data_list[i] << '|';
		}
		cout << endl;
		cnt++;
	}

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	cout << "Done. Found " << cnt << " records." << endl;
	return true;
}

bool output_logic_order(Table * table_now)//select(����where)_order ���
{
	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	cout << '|';
	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << setw(10) << table_now->table_head[i] << "|";
	}
	cout << endl;

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;

	int end = 0;
	int cnt = 0;
	for (unsigned int i = 0; i< table_now->ans_order.size(); i++)
	{

		int tmp = table_now->ans_order[i];//���
		if (table_now->Map[tmp].is_exist == false)continue;

		end = table_now->Map[tmp].data_list.size();
		cout << '|';
		for (int j = 0; j < end; j++){
			cout << setw(10) << table_now->Map[tmp].data_list[j] << '|';
		}
		cnt++;
		cout << endl;
	}

	for (int i = 1; i <= table_now->table_head_number; i++)
	{
		cout << "+";
		cout << "----------";
	}
	cout << '+' << endl;


	cout << "Done. Found " << cnt << " records." << endl;
	return true;
}
