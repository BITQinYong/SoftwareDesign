#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "data_structure.h"
#include <direct.h>
#include <vector>
#include <sys/stat.h>
#include <map>
#include"support.h"
using namespace std;

struct table_node//表节点
{
	Table *current_table;
	bool if_read;
};

class DataBase{//基本结构（包含各种功能、调用函数）
public:
	DataBase();//构造函数
	bool Create_database(string database_name);//创建库
	bool Drop_database(string database_name);//删除库
	bool Use(string database_name);//使用库
	bool Create(string, string[], string[], int);//创建表
	bool Drop(string);//删除表
	bool Insert(string, string data[]);//插入数据
	bool Delete(string, string);//删除数据
	bool Update(string, string, string, string);//更新数据
	bool Select_all(string);//查询整表
	bool Select_all_order(string, string);//按序查询整表
	bool Select(string,string);//条件查询
	bool Select_order(string,string,string);//按序条件查询
	bool Open(string);//打开表
	bool Save();//关闭库
	string database_name;//库名
	map<string, table_node> database_map;//搜索表节点
	bool saved;//存储标识
private:
	int table_num;//表树
	vector<string> table_open;//存取表的名字
};


DataBase::DataBase()
{
	saved = 1;
	table_num = 0;
}


bool DataBase::Open(string table_name)//将外存读入内存并组织起来  
{
	string file_name = database_name;
	file_name += "//";
	file_name += table_name;
	file_name += ".txt";
	ifstream in;
	in.open(file_name);
	if (!in)
	{
		in.close();
		return false;
	}
	else
	{
		in.close();
		if (database_map[table_name].if_read)return true;
		else
		{
			table_node p;
			p.current_table = new Table(file_name);
			p.if_read = true;
			database_map[table_name] = p;
			table_open.push_back(table_name);
			table_num++;

		}
	}
	return true;
}



bool DataBase::Save()//记得delete
{
	if (saved == 1)
	{
		cout << "Error: No DataBase is being used." << endl;
		return false;
	}

	string directory = database_name;
	directory += "//";
	ofstream file_copy;
	string copy;
	copy = directory + "copy.txt";

	for (int i = 0; i < table_num; i++)//对操作过的表逐一写入
	{
		string table_save;
		Table * table_now;
		table_save = table_open[i];
		if (database_map.count(table_save) < 1)continue;

		table_now = database_map[table_save].current_table;

		file_copy.open(copy.c_str());
		file_copy << table_now->table_head_number;
		for (int i = 1; i <= table_now->table_head_number; i++)
		{
			file_copy << " " << table_now->table_head[i];
		}
		file_copy << endl;//第一行写入

		file_copy << table_now->table_head_number << " ";
		for (int i = 1; i <= table_now->table_head_number; i++){
			file_copy << table_now->data_type[i];
		}
		file_copy << endl;//第二行

		for (int i = 1; i <= table_now->max_line_num; i++)//输出数据行控制
		{
			if (!table_now->Map[i].is_exist)continue;
			int end = table_now->Map[i].data_list.size();
			for (int j = 0; j < end - 1; j++)
			{
				file_copy << table_now->Map[i].data_list[j] << ' ';
			}
			file_copy << table_now->Map[i].data_list[end - 1];
			file_copy << endl;
		}

		table_save += ".txt";
		table_save = directory + table_save;
		file_copy.close();
		remove(table_save.c_str());
		//perror("remove");
		rename(copy.c_str(), table_save.c_str());
	}
	cout << "Done. Database " << database_name << " has been closed." << endl;;
	database_name = "";
	database_map.clear();
	table_num = 0;
	saved = true;
	return true;
}

bool DataBase::Create_database(string name)
{
	struct _stat fileStat;
	if ((_stat(name.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))//库已经存在
	{
		cout << "Error: The name of the database was used." << endl;;
		return false;
	}
	else {
		_mkdir(name.c_str());
		cout << "Done. Created Database " << name << endl;
		return true;
	}
}

bool DataBase::Drop_database(string name)
{
	struct _stat fileStat;
	if (name == database_name)//库正在被使用
	{
		cout << "Error: This database is being used.Please close it before you drop." << endl;
		return false;
	}

	else if ((_stat(name.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))//成功
	{
		if (_rmdir(name.c_str()) == 0)
		{
			cout << "Done.Database " << name << " has been deleted." << endl;
			return true;
		}
		else//库必须为空删除时
		{
			cout << "Error:Database " << name << " shuold be empty before you delete." << endl;
			return false;
		}
	}

	else {//库不存在
		cout << "Error: The database " << name << " doesn’t exist." << endl;;
		return false;
	}
}

bool DataBase::Use(string name)
{
	struct _stat fileStat;
	if (saved == false)
	{
		cout << "Error:A DataBase is being used." << endl;//有库在用
		return false;
	}
	else
	{
		if (!((_stat(name.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR)))
		{
			cout << "Error: The database doesn't exist." << endl;//库不存在
			return false;
		}

		else
		{
			database_name = name;
			saved = 0;
			cout << "Done. Database " << name << " is opened." << endl;//已经打开
			return true;
		}
	}

}

bool DataBase::Create(string table_name, string filed[], string type[], int field_num)//创建表
{


	string file_name = database_name;
	file_name += "//";
	file_name += table_name;
	file_name += ".txt";

	ifstream in;
	string temp_create = file_name;
	in.open(temp_create.c_str());
	if (in)
	{
		in.close();
		cout << "Error:The name of the table was used. " << endl;
		return false;
	}

	if (!type_judge(type, field_num))
	{
		cout << "Error: Wrong instruction.";
		return false;
	}

	ofstream fout;//第一行
	fout.open(file_name.c_str());
	fout << field_num;

	for (int i = 1; i <= field_num; i++)
	{
		fout << " " << filed[i];
	}
	fout << endl;


	fout << field_num << " ";
	for (int i = 1; i <= field_num; i++)
	{
		if (type[i] == "int")
			fout << "0";
		else if (type[i] == "char")
			fout << "1";
		else if (type[i] == "float")
			fout << "2";
		else if (type[i] == "date")
			fout << "3";
		else fout << "4";
	}
	fout << endl;

	fout.close();
	cout << "Done." << endl;
	return true;
}

bool DataBase::Drop(string table_name)//删除表
{

	string file_name = database_name;
	file_name += "//";
	file_name += table_name;
	file_name += ".txt";

	ifstream in;
	in.open(file_name.c_str());
	if (!in)
	{
		in.close();
		cout << "Error:Table " << table_name << " doesn't exist." << endl;
		return false;
	}

	in.close();
	if (database_map.count(table_name)>0)//若已打开，从内存中delete
		database_map.erase(table_name);

	remove(file_name.c_str());
	cout << "Done.Table " << table_name << " has been deleted!" << endl;
	return true;
}

bool DataBase::Insert(string table_name, string data[])//插入操作
{
	Table * table_now;
	table_now = database_map[table_name].current_table;
	string line_data;
	line_data = data[0];

	if (type_data_judge(data[0], table_now->data_type[1]) == false)
		return false;//若判断到不符合格式的输入，返回false
	

	for (int i = 1; !data[i].empty(); i++)
	{

		if (type_data_judge(data[i], table_now->data_type[i + 1]) == false)
			return false;
		line_data += " ";
		line_data += data[i];

	}
	
	database_map[table_name].current_table->Insert_Line_Data(line_data.c_str());
	return true;
}

bool DataBase::Delete(string table_name, string data)
{
	if (database_map[table_name].current_table->Del_Line(data) == false){
		cout << "Error: No data match." << endl;
		return false;//未找到
	}
	else cout << "Done.Deleted " << database_map[table_name].current_table->operator_times << endl;
	return true;
}

bool DataBase::Update(string table_name, string filed_appoint, string data_appoint, string data)
{


	if (database_map[table_name].current_table->_Updata(data, filed_appoint, data_appoint) == false){
		cout << "Error: No data match." << endl;
		return false;//未找到
	}
	else cout << "Done.Changed " << database_map[table_name].current_table->ans_list.size() << endl;

	return true;
}

bool DataBase::Select_all(string table_name)
{
	Table * table_now;
	table_now = database_map[table_name].current_table;
	output(table_now);

	cout << "Table " << table_name << " output is completed." << endl;
	return true;
}

bool DataBase::Select_all_order(string table_name, string filed_order)
{
	Table * table_now;
	table_now = database_map[table_name].current_table;

	table_now->ans_list.clear();
	table_now->Order(filed_order);

	output_order(table_now);//order 操作

	cout << "Table " << table_name << " output is completed." << endl;

	return true;
}

bool DataBase::Select(string table_name, string data)
{

	cout << table_name << endl << data << endl;
	Table * table_now;
	table_now = database_map[table_name].current_table;

	table_now->Logic(data);//逻辑查询


	if (table_now->ans_list.size() == 0)
	{
		cout << "Error: No data match." << endl;
		return false;
	}

	output_logic(table_now);//输出



	cout << "Table " << table_name << " output is completed." << endl;
	return true;
}


bool DataBase::Select_order(string table_name, string data, string filed_order)
{
	Table * table_now;
	table_now = database_map[table_name].current_table;

	table_now->Logic(data);//逻辑查询
	if (table_now->ans_list.size() == 0)
	{
		cout << "Error: No data match." << endl;
		return false;
	}

	table_now->Order(filed_order);//order操作

	output_logic_order(table_now);

	cout << "Table " << table_name << " output is completed." << endl;


	return true;

}

