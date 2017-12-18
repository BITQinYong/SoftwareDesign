#include"syntax.h"

string history[500];
int qindiao = 0;
bool syntax_analysis(string stringname)
{



	history[qindiao] = stringname;
	qindiao++;

	int i = 0, j = 0, k = 0, m = 0, n = 0, count_create = 0;
	int number_change;
	//int column_count = 0;//column_count记录这张表有多少列

	int i_select = 0, count_select = 0;
	int i_delete = 0, count_delete = 0;
	int i_update = 0, count_update = 0;

	int i_drop = 0, count_drop = 0, j_drop = 0;
	int i_open = 0, count_open = 0, j_open = 0;
	int i_close = 0, count_close = 0, j_close = 0;
	int i_insert = 0, count_insert = 0, j_insert = 0;


	int position[40];


	int position_delete[15];
	int position_select[15];
	int position_update[15];

	int position_drop[15];
	int position_close[15];
	int position_insert[15];


	string create_table[40][2];
	string table_head_name[40];//table_head_name用于存储表头信息（即每一列表头）
	string table_head_quality[20];//table_head_quality用于存储每一列的数据类型int或char

	string delete_data[4];
	string select_data[4];
	string update_data[6];

	string drop_data[10];
	string open_data[10];
	string close_data[10];
	string insert_data_instruction[10];


	int i_create_database = 0, count_create_database = 0;
	int position_create_database[10];
	string create_database;           //创建库

	int i_drop_database = 0, count_drop_database = 0;
	int position_drop_database[10];
	string drop_database;          //删除库

	int i_use_database = 0, count_use_database = 0;
	int position_use_database[10];
	string use_database;          //使用库

	int position_order_by[15];
	int i_order = 0, j_order = 0, count_order = 0;
	string order_by[4];

	int position_order_all[15];
	int i_order_all = 0, j_order_all = 0, count_order_all = 0;
	string order_all[2];

	int pos_delete[50];
	int i_again_delete = 0, count_again_delete = 0;
	string again_delete[3];         //delete版本的逻辑表达式；

	int pos_update[50];
	int i_again_update = 0, count_again_update = 0;
	string again_update[5];

	int pos_select[50];
	int i_again_select = 0, count_again_select = 0;
	string again_select[3];

	int pos_delete_by[50];
	int i_again_delete_by = 0, count_again_delete_by = 0;
	string again_delete_by[3];         //delete.....order by版本的逻辑表达式；

	int pos_update_by[50];
	int i_again_update_by = 0, count_again_update_by = 0;
	string again_update_by[5];

	int pos_select_by[50];
	int i_again_select_by = 0, count_again_select_by = 0;
	string again_select_by[3];

	int pos_select_by_column[50];
	int i_again_select_by_column = 0, j_again_select_by_column = 0, count_again_select_by_column = 0;
	string again_select_by_column[20];


	//创建表操作
	if (regex_search(stringname, results, r_creat_table))
	{
		for (auto c : stringname)
		{
			count_create++;
			if ((c == ' ') || (c == ';') || (c == ','))
			{
				position[i] = count_create;
				i++;
			}
		}//遍历整个字符串
		for (j = 1; j < i - 2; j += 2)
		{
			k = j + 1;
			create_table[j][0] = stringname.substr(position[j], position[k] - position[j] - 1);
			create_table[j][1] = stringname.substr(position[k], position[k + 1] - position[k] - 1);
		}
		for (j = 1; j < i - 2; j++)
		{
			if (j % 2 != 0)
			{
				//以下三行是你想要的表头信息，以及列数；
				table_head_name[m] = create_table[j][0];
				table_head_quality[m] = create_table[j][1];
				//	column_count++;   //column_count比表的列数大一，想要表示表的列数，需减一
				m++;    //m与column的功能一样
				number_change = std::atoi(table_head_quality[0].c_str());//number_change是输入的表的列的数量；
				//cout << create_table[j][0] << "  " <<create_table[j][1] << endl;
			}
		}
		m = m - 1;
		if (BeOne.saved == 1)
		{
			cout << "Error:No DataBase is being used." << endl;
		}
		else
		{
			if (m == number_change)
			{
				BeOne.Create(table_head_name[0], table_head_name, table_head_quality, number_change);
			}
			else
			{
				cout << "Error: The amount of the column is wrong." << endl;;
			}
		}
	}


	else if (regex_search(stringname, results, r_create_database))//创建库
	{
		for (auto c : stringname)
		{
			count_create_database++;
			if ((c == ' ') || (c == ';') || (c == ','))
			{
				position_create_database[i_create_database] = count_create_database;
				i_create_database++;
			}
		}
		create_database = stringname.substr(position_create_database[1], position_create_database[2] - position_create_database[1] - 1);
		BeOne.Create_database(create_database);
	}


	else if (regex_search(stringname, results, r_drop_database))//删除库
	{
		for (auto c : stringname)
		{
			count_drop_database++;
			if ((c == ' ') || (c == ';') || (c == ','))
			{
				position_drop_database[i_drop_database] = count_drop_database;
				i_drop_database++;
			}
		}
		drop_database = stringname.substr(position_drop_database[1], position_drop_database[2] - position_drop_database[1] - 1);
		BeOne.Drop_database(drop_database);
	}

	else if (regex_search(stringname, results, r_use_database))//使用库
	{
		for (auto c : stringname)
		{
			count_use_database++;
			if ((c == ' ') || (c == ';') || (c == ','))
			{
				position_use_database[i_use_database] = count_use_database;
				i_use_database++;
			}
		}
		use_database = stringname.substr(position_use_database[0], position_use_database[1] - position_use_database[0] - 1);

		BeOne.Use(use_database);
	}

	else if (regex_search(stringname, results, r_close_database))//关闭库
	{
		BeOne.Save();
	}


	else if (regex_search(stringname, results, r_drop_table))//删除表
	{

		for (auto c : stringname)
		{
			count_drop++;
			if ((c == ' ') || (c == ';') || (c == ','))
			{
				position_drop[i_drop] = count_drop;
				i_drop++;
			}
		}
		for (j_drop = 0; j_drop < i_drop - 2; j_drop++)
		{
			drop_data[j_drop] = stringname.substr(position_drop[j_drop + 1], position_drop[j_drop + 2] - position_drop[j_drop + 1] - 1);
		}

		if (BeOne.saved == 1)
		{
			cout << "Error:No DataBase is being used." << endl;
		}
		else{

			for (int i = 0; i <= j_drop - 1; i++)
			{

				BeOne.Drop(drop_data[i]);
			}
		}
	}

	else if (regex_search(stringname, results, r_input_data))	//插入数据操作
	{
		for (auto c : stringname)
		{
			count_insert++;
			if ((c == ' ') || (c == ';') || (c == ','))
			{
				position_insert[i_insert] = count_insert;
				i_insert++;
			}
		}
		for (j_insert = 0; j_insert < i_insert - 2; j_insert++)
		{
			insert_data_instruction[j_insert] = stringname.substr(position_insert[j_insert + 1], position_insert[j_insert + 2] - position_insert[j_insert + 1] - 1);
			//cout << insert_data_instruction[j_insert] << endl;
		}

		if (BeOne.saved == 1)
		{
			cout << "Error:No DataBase is being used." << endl;
		}
		else{
			if (!BeOne.Open(insert_data_instruction[0]))//判断表是否存在
			{
				cout << "Error: The Table doesn't exist." << endl;
			}
			else{

				string temp_insert;
				string table_field[15];
				temp_insert = BeOne.database_name;
				temp_insert += "//";
				temp_insert += insert_data_instruction[0];
				temp_insert += ".txt";
				int field_num;
				cout << "Please input:" << endl;
				ifstream fin;
				fin.open(temp_insert.c_str());
				fin >> field_num;
				for (int i = 1; i <= field_num; i++)
				{
					fin >> table_field[i];
					cout << table_field[i] << endl;
				}
				fin.close();//读出字段数



				string insert_data;
				while (getline(cin, insert_data))
				{
					if (regex_search(insert_data, results, r_input_data_format))//确保数据输入格式的正确性
					{

						if (insert_data != "exit;")   //完全有必要给输入的数据格式写一个匹配
						{
							int i_data = 1, count_data = 0, j_data = 0; //插入数据操作
							int position_data[15];
							string data[20];  //data数组用于存储每次输入的哪行数据，以空格作为分隔

							int helloqin = 0;
							int countqin = 0;
							for (auto c : insert_data)
							{
								count_data++;
								if ((c == ' ') || (c == ';') || (c == ','))
								{
									position_data[i_data] = count_data;
									i_data++;
								}
							}
							//cout << i_data << endl;
							position_data[0] = 0;
							for (j_data = 0; j_data < i_data - 1; j_data++)
							{
								//下面这一行是你想要的数据
								data[j_data] = insert_data.substr(position_data[j_data], position_data[j_data + 1] - position_data[j_data] - 1);//into后面可跟多个

							}

							for (int helloqin = 0; helloqin < field_num; helloqin++)
							{
								if (data[helloqin] != "")
									countqin++;
							}
							if (countqin == field_num)
							{
								BeOne.Insert(insert_data_instruction[0], data);
							}
							else
							{
								cout << "Error:Wrong data." << endl;
							}

						}
						else
						{
							cout << "Done. Input end." << endl;
							break;
						}
					}
					else if (regex_search(insert_data, results, r_insert_data_part))
					{
						//cout << "qinyong!!" << endl;
						if (insert_data != "exit;")   //完全有必要给输入的数据格式写一个匹配
						{

							int position_insert_not_all[60];
							int i_insert_not_all = 0, j_insert_not_all = 0, count_insert_not_all = 0;
							int right_brackets = 0, hello = 0;

							int wo = 0, shi = 0, qin = 0, yong = 0, aa = 0, bb = 0, cc = 0;
							int table_head_length = 12, part_data_length = 0;//假设长度是0

							string insert_is_part_data[30];

							//string head_table[30];//先测传过来的数组长度；在做处理
							string insert_head[30];

							string insert_is_data[30];

							for (aa = 0; aa < table_head_length; aa++)
							{
								if (table_field[aa] != "")
								{
									bb++;

								}

								//cout << insert_is_part_data[aa] << endl;
							}
							//cout << bb << endl;
							for (auto c : insert_data)
							{
								count_insert_not_all++;
								if ((c == ' ') || (c == ';') || (c == ',') || (c == '(') || (c == ')'))
								{
									position_insert_not_all[i_insert_not_all] = count_insert_not_all;
									i_insert_not_all++;
								}
								if (c == ')')
								{
									right_brackets = count_insert_not_all;
								}
							}
							for (j_insert_not_all = 0; j_insert_not_all < count_insert_not_all; j_insert_not_all++)
							{
								if (right_brackets == position_insert_not_all[j_insert_not_all])
								{
									hello = j_insert_not_all + 1;
									//break;先准备跳出吧。
								}
							}
							//cout << hello << endl;
							for (wo = 0; wo < hello - 2; wo++)
							{
								insert_head[wo] = insert_data.substr(position_insert_not_all[wo + 1], position_insert_not_all[wo + 2] - position_insert_not_all[wo + 1] - 1);
								//cout << insert_head[wo] << endl;
							}
							hello = hello - 1;
							for (shi = 0; shi < i_insert_not_all - hello; shi++)
							{
								insert_is_data[shi] = insert_data.substr(position_insert_not_all[hello + shi], position_insert_not_all[shi + hello + 1] - position_insert_not_all[shi + hello] - 1);
								//cout << insert_is_data[shi] << endl;
							}
							shi = shi - 1;
							//cout << wo << endl;
							//cout << shi << endl;
							//part_data_length = sizeof(insert_head) / sizeof(insert_head[0]);
							//cout << part_data_length << endl;
							if (wo == shi)
							{
								for (int mm = 0; mm < bb; mm++)
								{
									insert_is_part_data[mm] = "-1";
								}
								for (qin = 0; qin < shi; qin++)
								{
									for (yong = 1; yong < bb + 1; yong++)
									{
										if (insert_head[qin] == table_field[yong])
										{
											insert_is_part_data[yong - 1] = insert_is_data[qin];//insert_is_part_data就是想要的；
										}
										//else
										//{
										//insert_is_part_data[yong] = "-1";
										//}
									}
								}

								BeOne.Insert(insert_data_instruction[0], insert_is_part_data);
							}
							else
							{
								cout << "Error:input_format_error;" << endl;
							}
						}

						else
						{
							cout << "Ok:input_data_end" << endl;
							break;
						}
					}
					else
					{
						cout << "Error: Wrong instruction." << endl;
						continue;
					}
				}
			}
		}
	}

	//第一条：Delete from 表名 where 任意字符串；
	else if (regex_search(stringname, results, r_again_delete))
	{
		cout << "1111111111111" << endl;
		for (auto c : stringname)
		{
			count_again_delete++;
			if ((c == ' ') || (c == ';') || (c == ',') || (c == '<') || (c == '>') || (c == '(') || (c == ')') || (c == '='))
			{
				pos_delete[i_again_delete] = count_again_delete;
				i_again_delete++;
			}
		}//遍历整个字符串
		again_delete[0] = stringname.substr(pos_delete[1], pos_delete[2] - pos_delete[1] - 1);//表名
		again_delete[1] = stringname.substr(pos_delete[3], pos_delete[i_again_delete - 1] - pos_delete[3] - 1);

		cout << again_delete[0] << endl << again_delete[1] << endl;
		if (BeOne.saved == 1)
		{
			cout << "Error:No DataBase is being used." << endl;
		}
		else{
			if (!BeOne.Open(insert_data_instruction[0]))//判断表是否存在
			{
				cout << "Error: The Table doesn't exist." << endl;
			}
			else{
				BeOne.Delete(again_delete[0], again_delete[1]);
			}
		}
	}


	//	第三条：Update from 表名 字段名 = 更新值 where 任意字符串；
	else if (regex_search(stringname, results, r_again_select))
	{
		cout << "66666666666" << endl;
		for (auto c : stringname)
		{
			count_again_select++;
			if ((c == ' ') || (c == ';') || (c == ',') || (c == '<') || (c == '>') || (c == '(') || (c == ')') || (c == '='))
			{
				pos_select[i_again_select] = count_again_select;
				i_again_select++;
			}
		}//遍历整个字符串
		again_select[0] = stringname.substr(pos_select[1], pos_select[2] - pos_select[1] - 1);//表名
		again_select[1] = stringname.substr(pos_select[3], pos_select[i_again_select - 1] - pos_select[3] - 1);
		cout << again_select[0] << endl << again_select[1] << endl;
	}


	//select在没有where时的操作
	else if (regex_search(stringname, results, r_select_data_all))
	{
		for (auto c : stringname)
		{
			count_close++;
			if ((c == ' ') || (c == ';') || (c == ','))
			{
				position_close[i_close] = count_close;
				i_close++;
			}
		}
		for (j_close = 0; j_close < i_close - 2; j_close++)
		{
			close_data[j_close] = stringname.substr(position_close[j_close + 1], position_close[j_close + 2] - position_close[j_close + 1] - 1);
		}

		for (int i = 0; i < i_close - 2; i++)
		{


			if (BeOne.saved == 1)
			{
				cout << "Error:No DataBase is being used." << endl;
				break;
			}
			else{
				if (!BeOne.Open(close_data[i]))
				{
					cout << "Error: The Table " << close_data[i] << " doesn't exist." << endl;
				}
				else{
					BeOne.Select_all(close_data[i]);
				}
			}
		}
	}

	else if (regex_search(stringname, results, r_order_all))//select_all_order
	{
		for (auto c : stringname)
		{
			count_order_all++;
			if ((c == ' ') || (c == ';') || (c == '"'))
			{
				position_order_all[i_order_all] = count_order_all;
				i_order_all++;
			}
		}
		order_all[0] = stringname.substr(position_order_all[1], position_order_all[2] - position_order_all[1] - 1);//截取了表名
		order_all[1] = stringname.substr(position_order_all[4], position_order_all[5] - position_order_all[4] - 1);//截取了列的名字
		if (BeOne.saved == 1)
		{
			cout << "Error:No DataBase is being used." << endl;
		}
		else{
			if (!BeOne.Open(order_all[0]))
			{
				cout << "Error: The Table " << order_all[0] << " doesn't exist." << endl;
			}
			else{
				BeOne.Select_all_order(order_all[0], order_all[1]);
			}
		}
	}
	//	第六条：Select from 表名 where 任意字符串；
	else if (regex_search(stringname, results, r_again_select_by))
	{
		cout << "5555555555555" << endl;
		for (auto c : stringname)
		{
			count_again_select_by++;
			if ((c == ' ') || (c == ';') || (c == ',') || (c == '<') || (c == '>') || (c == '(') || (c == ')') || (c == '='))
			{
				pos_select_by[i_again_select_by] = count_again_select_by;
				i_again_select_by++;
			}
		}//遍历整个字符串
		again_select_by[0] = stringname.substr(pos_select_by[1], pos_select_by[2] - pos_select_by[1] - 1);//表名
		again_select_by[1] = stringname.substr(pos_select_by[3], pos_select_by[i_again_select_by - 4] - pos_select_by[3] - 1);
		again_select_by[2] = stringname.substr(pos_select_by[i_again_select_by - 2], pos_select_by[i_again_select_by - 1] - pos_select_by[i_again_select_by - 2] - 1);
		cout << again_select_by[0] << endl << again_select_by[1] << endl << again_select_by[2] << endl;
	}

	//	第五条：Select from<表名>where 任意字符串 order by 字段名；
	else if (regex_search(stringname, results, r_again_update_by))
	{
		cout << "4444444444 " << endl;
		for (auto c : stringname)
		{
			count_again_update_by++;
			if ((c == ' ') || (c == ';') || (c == ',') || (c == '<') || (c == '>') || (c == '(') || (c == ')') || (c == '='))
			{
				pos_update_by[i_again_update_by] = count_again_update_by;
				i_again_update_by++;
			}
		}//遍历整个字符串
		again_update_by[0] = stringname.substr(pos_update_by[1], pos_update_by[2] - pos_update_by[1] - 1);//表名
		again_update_by[1] = stringname.substr(pos_update_by[2], pos_update_by[3] - pos_update_by[2] - 1);
		again_update_by[2] = stringname.substr(pos_update_by[3], pos_update_by[4] - pos_update_by[3] - 1);
		again_update_by[3] = stringname.substr(pos_update_by[5], pos_update_by[i_again_update_by - 4] - pos_update_by[5] - 1);
		again_update_by[4] = stringname.substr(pos_update_by[i_again_update_by - 2], pos_update_by[i_again_update_by - 1] - pos_update_by[i_again_update_by - 2] - 1);
		cout << again_update_by[0] << endl << again_update_by[1] << endl << again_update_by[2] << endl << again_update_by[3] << endl << again_update_by[4] << endl;
	}

	//	第七条：Select 字段1名 字段2名....字段n名 from 表名；
	else if (regex_search(stringname, results, r_column_select))
	{
		cout << "777777777777777" << endl;
		for (auto c : stringname)
		{
			count_again_select_by_column++;
			if ((c == ' ') || (c == ';') || (c == ',') || (c == '<') || (c == '>') || (c == '(') || (c == ')') || (c == '='))
			{
				pos_select_by_column[i_again_select_by_column] = count_again_select_by_column;
				i_again_select_by_column++;
			}
		}//遍历整个字符串
		for (j_again_select_by_column = 0; j_again_select_by_column < i_again_select_by_column - 2; j_again_select_by_column++)
		{
			again_select_by_column[j_again_select_by_column] = stringname.substr(pos_select_by_column[j_again_select_by_column], pos_select_by_column[j_again_select_by_column + 1] - pos_select_by_column[j_again_select_by_column] - 1);
			cout << again_select_by_column[j_again_select_by_column] << endl;
		}
		//ain_select_by[0] = stringname.substr(pos_select_by[1], pos_select_by[2] - pos_select_by[1] - 1);//表名
		//gain_select_by[1] = stringname.substr(pos_select_by[3], pos_select_by[i_again_select_by - 4] - pos_select_by[3] - 1);
		//again_select_by[2] = stringname.substr(pos_select_by[i_again_select_by - 2], pos_select_by[i_again_select_by - 1] - pos_select_by[i_again_select_by - 2] - 1);
		//cout << again_select_by[0] << endl << again_select_by[1] << endl << again_select_by[2] << endl;
	}

	else
	{
		cout << "Error: Wrong instruction." << endl;
	}
	return true;
}