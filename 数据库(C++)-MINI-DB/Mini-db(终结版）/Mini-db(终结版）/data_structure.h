#pragma once
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<map>
#include<string>
#include<cstring>
#include<cmath>
#include<ctime> 
#include<queue> 
#include<set>
#include<fstream>
#include<stack>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////
int cishu = 0;
map<char, int> ch;
map<int, char> nu;


//treap�Ľڵ�

class AVLNode{
private:

public:
	string data;
	int hgt; //�ڵ�ĸ߶�
	int count;
	set <int> num_list;

	AVLNode *son[2]; //0������ӣ�1���Ҷ���
	AVLNode(string data) : data(data), count(1){

		son[0] = son[1] = NULL;
		hgt = 1;
	}

	void show(){
		cout << "*************************************" << endl;
		cout << "�������Ϊ " << data << endl;
		cout << "��㺬�еĵı���б� ";
		int end = num_list.size();
		set<int> ::iterator it;
		for (it = num_list.begin(); it != num_list.end(); it++){
			cout << *it << ' ';
		}
		cout << endl;
	}
	void Get_Hgt();
	int Get_Dir(int tp, string a, string b);

};

class DicNode{
public:
	int count;
	bool is_exist;
	set<int> num_list;
	DicNode *son[62];
	DicNode() {
		count = 0;
		is_exist = false;
		for (int i = 0; i < 62; i++){
			son[i] = NULL;
		}
	}

	void show(){
		cout << "*************************************" << endl;
		cout << "��㺬�еĵı���б� ";
		int end = num_list.size();
		set<int> ::iterator it;
		for (it = num_list.begin(); it != num_list.end(); it++){
			cout << *it << ' ';
		}
		cout << endl;
	}
};

int AVLNode::Get_Dir(int tp, string a, string b){
	if (tp == 0){
		long long int num1 = atoi(a.c_str());
		long long int num2 = atoi(b.c_str());
		int tdir = (num1 > num2);
		return tdir;
	}

	else if (tp == 3 || tp == 4 || tp == 5){
		int tdir = (a > b);
		return tdir;
	}

	else if (tp == 2){
		double dnum1 = atof(a.c_str());
		double dnum2 = atoi(b.c_str());
		int tdir = (dnum1 > dnum2);
		return tdir;
	}
	return 0;
}


void AVLNode::Get_Hgt(){
	//cishu++;
	int ans = 1;
	if (son[0] == NULL){
		if (son[1] != NULL) ans = 1 + (son[1]->hgt);
	}
	else if (son[0] != NULL){
		if (son[1] == NULL) ans = (son[0]->hgt) + 1;
		else ans = max((son[0]->hgt), (son[1]->hgt)) + 1;
	}
	hgt = ans;
}


//AVL Tree
class Tree{
private:
	int hgt;   //���ĸ߶�
	int size;   //���в��ظ��ڵ�����
	void _insert(int tp, AVLNode *& cur, string data, int data_num);
	void _mid_travel(AVLNode *cur);
	//��α���
	void _cengci_travel(AVLNode *cur);
	//����ת���������ң�, ��������������ת����˼�� ��������������������ӵĸ߶�̫��
	//��treap����ת�����෴
	void _singleRoate(AVLNode *& cur, int dir);
	//˫��ת�����ε���ת��
	void _doubleRoate(AVLNode *& cur, int dir);
public:
	set <int> ans_list;
	AVLNode * root;  //���ڵ� 
	DicNode * dic_root;
	Tree() :root(NULL), hgt(0), dic_root(NULL){}
	void mid_travel_dic(DicNode *cur);
	void insert(int tp, const string & data, int data_num);
	void insert(int i, DicNode * cur, string data, int data_num);
	void mid_travel();
	//��α���
	void cengci_travel(){
		_cengci_travel(root);
	};

};

/*************  ˽�з�����ʼ**********************/

void Tree::mid_travel_dic(DicNode *cur){
	if (cur == NULL) return;
	if (cur->is_exist == true){
		cur->show();
	}
	for (int i = 0; i < 62; i++)
		mid_travel_dic(cur->son[i]);
}

void Tree::_insert(int tp, AVLNode *& cur, string data, int data_num){
	//	cishu++;	
	if (NULL == cur){
		cur = new AVLNode(data);
		cur->num_list.insert(data_num);
		return;
	}
	else if (data == cur->data){
		cur->num_list.insert(data_num);
		cur->count++;
		return;
	}

	else{
		int dir = cur->Get_Dir(tp, data, cur->data);
		_insert(tp, cur->son[dir], data, data_num);

		int gap = 0;
		if (cur->son[0] == NULL){
			if (cur->son[1] != NULL) gap = 0 - (cur->son[1]->hgt);
		}
		else if (cur->son[0] != NULL){
			if (cur->son[1] == NULL) gap = cur->son[0]->hgt;
			else gap = (cur->son[0]->hgt) - (cur->son[1]->hgt);
		}


		if (gap >= 2){
			_singleRoate(cur, 0);
		}
		else if (gap <= -2){
			_singleRoate(cur, 1);
		}

		cur->Get_Hgt();
	}
}


void Tree::insert(int i, DicNode * cur, string data, int data_num){
	if (i == data.size()){
		cur->is_exist = true;
		cur->num_list.insert(data_num);
		cur->count += 1;
		return;
	}
	else{
		char temp_char = data[i];
		int x = ch[temp_char];
		if (cur->son[x] == NULL)
			cur->son[x] = new DicNode;
		insert(i + 1, cur->son[x], data, data_num);
	}
}

void Tree::_mid_travel(AVLNode * cur){
	if (NULL != cur){
		//�Ȳ���������
		_mid_travel(cur->son[0]);
		//if(abs(cur->son[0]->height() - cur->son[1]->height()) >= 2)
		{
			if (!(cur->num_list.empty()))
				cur->show();
		}
		_mid_travel(cur->son[1]);
	}
}
//��α�����
//����ڵ�Ϊ�վ����0 ��ռλ
void Tree::_cengci_travel(AVLNode * cur){
	if (NULL == cur)
		return;
	queue<AVLNode*> q;
	q.push(cur);
	AVLNode *top = NULL;
	queue<AVLNode*> tmp;

	while (!q.empty()){
		while (!q.empty()){
			top = q.front();
			q.pop();
			if (NULL == top){
				//��#����ýڵ��ǿգ�#�ĺ������#
				cout << '#' << " ";
				tmp.push(top);
			}
			else{
				cout << top->data << " ";
				tmp.push(top->son[0]);
				tmp.push(top->son[1]);
			}
		}
		bool flag = false;
		while (!tmp.empty()){
			if (NULL != tmp.front())
				flag = true;
			q.push(tmp.front());
			tmp.pop();
		}
		cout << endl;
		if (!flag)
			break;
	}
}

//����ת����ֻ��תһ��
//dir = 0ʱ,������ת������Ϊ������ת
void Tree::_singleRoate(AVLNode *& cur, int dir){
	//cishu++;
	AVLNode *& k2 = cur, *k1 = k2->son[dir]; //k2 ����������
	k2->son[dir] = k1->son[!dir];
	k1->son[!dir] = k2;
	k2 = k1;


	if (k2->son[!dir] != NULL)
		k2->son[!dir]->Get_Hgt();

	if (k2->son[dir] != NULL)
		k2->son[dir]->Get_Hgt();


	if (k2 != NULL)
		k2->Get_Hgt();
}
//˫��ת���������ε���ת
//dir = 0����������� ����Ϊ�������
void Tree::_doubleRoate(AVLNode *& cur, int dir){
	_singleRoate(cur->son[dir], !dir);
	_singleRoate(cur, dir);
}

/*************  ���з������ӿڣ���ʼ**********************/
void Tree::insert(int tp, const string & data, int data_num){
	if (tp == 1){
		insert(0, dic_root, data, data_num);
	}
	else _insert(tp, root, data, data_num);
}

void Tree::mid_travel(){
	_mid_travel(root);
}

//////////////////////////////////////////////////////////////////////////////////


struct node_head{
	int number;
	bool is_exist;//��Ӧ�ýڵ��Ƿ����
	vector <string> data_list;
};


class Table{
public:

	set<int> ans_list;//ÿһ�β�ѯ�����������������ݴ���ans_list��
	set<int> str_list;//��ÿһ��ģ����ѯ�и�������ģ����ѯͬʱ�洢���
	set<int> all;//�洢���ݿ������е����ݱ��
	Tree * ans_tree;//��order by������Ҫ�����Ĵ���
	vector<int> ans_order;//��ɨ�����֮�����ݴ洢��ans_order��
	int operator_times;//ÿһ�ζ����ݿ�����в��������ݸ���

	int times;
	node_head *head, *now;
	map<int, node_head> Map;//�������ݱ�������ݽڵ�Ķ�Ӧ��ϵ
	map<string, int> table_head_num;//�����ͷ��Ӧ�ı�� 
	string table_name;
	string table_head[15];//�����ͷ 
	char temp_data[300]; // �洢�Ӽ������������ 
	int table_head_number;// ��ͷ���� 
	int line_num;//�������ݵ����� 
	int max_line_num;
	ifstream in_data;
	int data_type[15]; //��ʾ��ͷ����������1λ�ַ���0Ϊ������ 
	Tree *StrList[15]; //������ָ��


	Table(string);

	void Save_Order(AVLNode *cur); //�����������������ݱ��˳��
	void _Find_Data(int tp, string finded_head_name, string finded_str);//�����ַ������� 
	set<int> _Find_Str(int step, AVLNode * cur, string finded_str);
	void _Find_Str(int step, int i, DicNode * cur, string finded_str, string now);//���ֵ����в�ѯ�ַ������ݣ���֧��ģ����ѯ��


	bool _Updata(string find_data_logic, string change_head_name2, string change_data);//�������ݿ���Ϣ
	bool Del_Line(string del_data_logic);

	int  GetNumber(int &x, int idx, const char* a);//���ַ�����ָ���ڳ�����
	void Insert_Line_Data(const char *line_data);//ʵ�ֲ���һ������ 
	void CreatList(char table_name[]);//�������ݽ��������ƽ������� 	
	int GetString(string &x, int idx, string a); //��������е��ַ���������	


	set<int> Find_Cond(set<int> ans_set1, set<int> ans_set2, int cond);//�����������ϵ��߼�����concΪ1��2��3�ֱ�Ϊ�롢�򡢷�����

	set<int> Logic(string logic);//�����߼����ʽ�ĺ���
	bool Order(string order);//����Order���жԲ�ѯ�������
};

//logic Ϊ�߼����ʽ
set<int> Table::Logic(string logic){
	int i = 0;
	string str, last_str;
	stack<set<int> > ans_set;
	stack<char> oper;
	set<int> temp_set;
	int l = 0, r = 0;
	int ends = logic.size();
	while (i < ends){
		temp_set.clear();


		i = GetString(str, i, logic);
		if (str.size() == 1 && str != ")" && str != "("){
			cout << "�߼����� �����˷Ƿ������" << endl;
			temp_set.clear();
			return temp_set;
		}
		if (str.size() == 2 && str != "or"){
			cout << "�߼����� �����˷Ƿ������" << endl;
			temp_set.clear();
			return temp_set;
		}
		if (str.size() == 3 && str != "and"&&str != "not"&&str[1] != '='){
			cout << "�߼����� �����˷Ƿ������" << endl;
			temp_set.clear();
			return temp_set;
		}


		if (str != "(" && str != ")" && str != "and" && str != "or" && str != "not"){
			if (last_str != "(" && str != ")" && last_str != "and" && last_str != "or" && last_str != "not"&& last_str.size() != 0){
				cout << "�߼����� ���������м�Ҫ�������" << endl;
				temp_set.clear();
				return temp_set;
			}

			string t1, t2;
			int j;
			for (j = 0; str[j] != '='; j++)
				t1 += str[j];
			int endxx = str.size();
			for (++j; j < endxx; j++)
				t2 += str[j];
			int step = table_head_num[t1];
			int tpp = data_type[step];
			_Find_Data(tpp, t1, t2);
			ans_set.push(ans_list);
		}


		if (str == ")" || i >= ends){
			if (str == ")") r++;
			if (l < r || (i == ends + 1 && l != r)){
				cout << "�߼����� ���Ų�ƥ��" << endl;
				temp_set.clear();
				return temp_set;
			}
			while (1){
				if (oper.empty()) break;
				set<int> set1 = ans_set.top();
				ans_set.pop();


				char s1 = oper.top();
				oper.pop();

				if (s1 == '(') {

					if (!oper.empty()){
						if (oper.top() == '3'){
							oper.pop();
							temp_set = Find_Cond(set1, set1, 3);
							set1 = temp_set;
						}
					}

					ans_set.push(set1);

				}
				else if (s1 == '3'){
					temp_set = Find_Cond(set1, set1, 3);
					ans_set.push(temp_set);
				}
				else if (s1 == '1' || s1 == '2'){
					set<int> set2 = ans_set.top();
					ans_set.pop();
					temp_set = Find_Cond(set1, set2, s1 - '0');
					ans_set.push(temp_set);
				}
			}

		}


		else if (str == "(") {
			if (last_str == ")") {
				cout << "�߼����� ���Ŵ���" << endl;
				temp_set.clear();
				return temp_set;
			}
			oper.push('(');
			l++;
		}
		else if (str == "and") {
			if (last_str == "or" || last_str == "and"){
				cout << "�߼����� �������������" << endl;
				temp_set.clear();
				return temp_set;
			}
			oper.push('1');
		}
		else if (str == "or") {
			if (last_str == "or" || last_str == "and"){
				cout << "�߼����� �������������" << endl;
				temp_set.clear();
				return temp_set;
			}
			oper.push('2');
		}
		else if (str == "not") oper.push('3');
		last_str = str;
	}
	ans_list = ans_set.top();
	operator_times = ans_list.size();
	return ans_list;
}

void Table::Save_Order(AVLNode *cur){
	if (cur == NULL) return;
	Save_Order(cur->son[0]);
	set<int> ::iterator it;
	for (it = cur->num_list.begin(); it != cur->num_list.end(); it++){
		ans_order.push_back(*it);
	}
	Save_Order(cur->son[1]);
}


//�ҵ�����������Ԫ�ز���Ҫ������� 
bool Table::Order(string order){
	if (ans_list.size() == 0) {
		int t = table_head_num[order];
		ans_tree = StrList[t];
	}

	else{
		int step = table_head_num[order];
		ans_tree = new Tree; //����aoder�Խ������ 
		set<int> ::iterator it;
		for (it = ans_list.begin(); it != ans_list.end(); it++){
			string temp_data = Map[*it].data_list[step - 1];
			int ttp = data_type[step];
			if (ttp == 1) ttp = 3;
			ans_tree->insert(ttp, temp_data, *it);
		}
	}
	ans_order.clear();
	Save_Order(ans_tree->root);
	return true;
}


set<int> Table::Find_Cond(set<int> ans_set1, set<int> ans_set2, int cond){
	set<int> temp_set;
	set<int> ::iterator it1, it2;
	if (cond == 1){//������
		if (ans_set1.size() == 0 || ans_set2.size() == 0)
			return ans_set1;
		for (it1 = ans_set1.begin(); it1 != ans_set1.end(); it1++){
			it2 = ans_set2.find(*it1);
			if (it2 != ans_set2.end()) temp_set.insert(*it1);
		}
		return temp_set;
	}
	else if (cond == 2){//������
		temp_set = ans_set2;
		for (it1 = ans_set1.begin(); it1 != ans_set1.end(); it1++)
			temp_set.insert(*it1);
		return temp_set;
	}
	else if (cond == 3){//������
		set<int> ::iterator it2;
		set<int> temp_set = all;
		for (it2 = ans_set2.begin(); it2 != ans_set2.end(); it2++){
			temp_set.erase(*it2);
		}
		return temp_set;//����������
	}
	return temp_set;
}



string Num_Get_String(int num){
	string a, temp;
	int x = 0;
	while (num){
		char tt = (num % 10) + '0';
		a += tt;
		num /= 10;
		++x;
	}
	while (x > 0){
		temp += a[--x];
	}
	int len = temp.size();
	return temp;
}



int Table::GetString(string &x, int idx, string a){
	string t;
	int len = a.size();


	for (int i = idx; i <= len; i++){
		if (a[i] == ' ' || i == len) {
			x = t;
			return i + 1;
		}
		t += a[i];
	}
	return 0;
}

int Table::GetNumber(int &x, int idx, const char* a){
	int t = 0;
	int len = strlen(a);


	for (int i = idx; i <= len; i++){
		if (a[i] == ' ' || i == len){
			for (int j = i - 1; j >= idx; j--){
				t += (int)((a[j] - '0') * pow(10, i - j - 1));
			}
			x = t;
			return i + 1;
		}
	}
	return 0;
}
//����һ������
void Table::Insert_Line_Data(const char* line_data){
	//cishu++;
	times++;
	max_line_num++;
	int step = 0;
	int i = 0;
	node_head *now = new node_head;
	now->number = times;
	now->is_exist = true;
	while (++step <= table_head_number){
		string temp_str;
		i = GetString(temp_str, i, line_data);//��line_data�н�ȡһ���ַ������temp_str�����Դ���
		now->data_list.push_back(temp_str);//����ȡ������temp_str�������ݽڵ�

		if (data_type[step] == 1){//�������������Ϊ�ַ���������ֵ�����
			if (StrList[step]->dic_root == NULL) StrList[step]->dic_root = new DicNode;
			StrList[step]->insert(0, StrList[step]->dic_root, temp_str, times);
		}

		else{//�������AVL����
			StrList[step]->insert(data_type[step], temp_str, times);
		}

	}

	Map[times] = *now;
	all.insert(times);
}

Table::Table(string file_name){//Table�Ĺ��캯��
	for (int i = 0; i <= 14; i++){
		StrList[i] = new Tree();
		StrList[i]->root = NULL;
	}
	int ix;
	for (ix = 0; ix < 52; ix += 2){//��ʼ��map ch��nu
		int ii = ix / 2;
		char ch1, ch2;
		ch1 = ii + 'A';
		ch2 = ii + 'a';
		ch[ch1] = ix;
		ch[ch2] = ix + 1;
		nu[ix] = ch1;
		nu[ix + 1] = ch2;
	}
	for (int k = 0; ix + k < 62; k++){
		char numx = k + '0';
		ch[numx] = k + ix;
		nu[k + ix] = numx;
	}
	int len1 = file_name.size();
	table_name = file_name;

	times = 0;
	max_line_num = 0;

	in_data.open(file_name.c_str()); // ���ļ� 
	in_data.getline(temp_data, 300);//��ȡ�ļ��ĵ�һ����Ϣ


	int i = GetNumber(table_head_number, 0, temp_data);
	int len = strlen(temp_data);
	int idx = 1;
	while (idx <= table_head_number){
		i = GetString(table_head[idx++], i, temp_data);
		table_head_num[table_head[idx - 1]] = idx - 1;
	}

	string temp_data_type;
	in_data.getline(temp_data, 200);//��ȡ�ļ���һ����Ϣ
	i = GetNumber(line_num, 0, temp_data);
	i = GetString(temp_data_type, i, temp_data);
	int end = temp_data_type.size();
	for (int k = 0; k < end; k++){
		data_type[k + 1] = temp_data_type[k] - '0';
	}
	while (in_data.getline(temp_data, 200)){

		Insert_Line_Data(temp_data);//���ļ��е����ݴ����ڴ���

	}
	line_num = max_line_num;
	in_data.close();
}


bool Table::Del_Line(string del_data_logic){//ɾ��һ������
	set<int> find_ans;
	find_ans = Logic(del_data_logic);//�����ʽ���ҵ����ݽڵ���
	if (find_ans.size() == 0) return false;

	set<int> ::iterator it;
	for (it = find_ans.begin(); it != find_ans.end(); it++){//����Ӧ�����ݽڵ�ɾ��
		int t = *it;
		Map[t].is_exist = 0;
		all.erase(Map[t].number);
		line_num--;
	}
	return true;
}



bool Table::_Updata(string find_data_logic, string change_head_name2, string change_data){
	if (table_head_num[change_head_name2] == 0) return false;
	set<int> find_ans;
	find_ans = Logic(find_data_logic);//���ݱ��ʽfind_data_logic�������ݱ��
	if (find_ans.size() == 0) return false;

	int steps = table_head_num[change_head_name2];
	vector<int> temp_list;
	vector<string> last_data;

	set<int> ::iterator it;
	for (it = find_ans.begin(); it != find_ans.end(); it++){
		int temps = *it;
		temp_list.push_back(temps);
		Map[temps].data_list[steps - 1] = change_data;

	}
	int len = temp_list.size();
	for (int i = 0; i < len; i++){//�������ݲ�����������
		StrList[steps]->insert(data_type[steps], change_data, temp_list[i]);

	}
	return true;
}


//���ֵ����в���finded_str
void Table::_Find_Str(int step, int i, DicNode * cur, string finded_str, string now){
	string tnow = now;
	char t;
	if (cur == NULL) return;
	if (i == finded_str.size()){
		if (cur != NULL){
			set<int> ::iterator it;
			set<int> temp_list;
			for (it = cur->num_list.begin(); it != cur->num_list.end(); it++){
				string tt = Map[*it].data_list[step - 1];
				if (Map[*it].is_exist == true && tt == tnow) {//��֤�ֵ����е�����
					temp_list.insert(*it);
					str_list.insert(*it);
				}

			}
			cur->num_list = temp_list;//�����ֵ����еĽ�����б�

		}
		return;
	}

	if (finded_str[i] == '?'){ //֧�ֶԣ���ģ����ѯ��dfs����ʵ�֣�
		for (int j = 0; j < 62; j++){
			if (cur->son[j] == NULL) continue;
			t = nu[j];
			tnow = now + t;
			_Find_Str(step, i + 1, cur->son[j], finded_str, tnow);
		}

		return;

	}
	if (finded_str[i] == '%'){//֧�ֶ�%��ģ����ѯ��dfs����ʵ�֣�


		for (int j = 0; j < 62; j++){
			if (cur->son[j] == NULL) continue;
			t = nu[j];
			tnow = now + t;
			_Find_Str(step, i + 1, cur->son[j], finded_str, tnow);
		}
		for (int j = 0; j < 62; j++){
			if (cur->son[j] == NULL) continue;
			t = nu[j];
			tnow = now + t;
			_Find_Str(step, i, cur->son[j], finded_str, tnow);
		}
		return;

	}

	tnow = now + finded_str[i];
	char temp_char2 = finded_str[i];
	int j = ch[temp_char2];
	if (cur->son[j] != NULL)
		_Find_Str(step, i + 1, cur->son[j], finded_str, tnow);

}

//��AVL���в�ѯfinded_str
set<int> Table::_Find_Str(int step, AVLNode * cur, string finded_str){
	int tp = data_type[step];
	if (NULL == cur){
		set<int> tt;
		return tt;
	}
	string ts = cur->data;
	if (finded_str == ts){//������ҵ���������Ľ��

		vector<int> temp_lists;
		set<int> ::iterator  it;
		for (it = cur->num_list.begin(); it != cur->num_list.end(); it++){
			if (Map[*it].data_list[step - 1] != cur->data || Map[*it].is_exist == 0) temp_lists.push_back(*it);//����������֤����
		}
		int ends = temp_lists.size();
		for (int i = 0; i < ends; i++){
			cur->num_list.erase(temp_lists[i]);//����AVL��
		}
		return cur->num_list;
	}
	else{
		int dir = cur->Get_Dir(tp, finded_str, cur->data);
		return _Find_Str(step, cur->son[dir], finded_str);
	}
}

//����ͬ�������͵���ͬ�Ĳ��Һ�����
void Table::_Find_Data(int tp, string finded_head_name, string finded_str){
	ans_list.clear();
	str_list.clear();
	int x = table_head_num[finded_head_name];
	string now0;
	if (data_type[x] == 1){
		_Find_Str(x, 0, StrList[x]->dic_root, finded_str, now0);
		ans_list = str_list;
	}
	else  {

		ans_list = _Find_Str(x, StrList[x]->root, finded_str);

	}
}

