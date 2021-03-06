#pragma once
#include<iostream>
#include<fstream>
using namespace std;
typedef struct point
{
	unsigned int x;
	unsigned int y;
}point;
typedef struct chess
{
	unsigned int x; unsigned int y; unsigned int z;//(0为空，1为白，2为黑)
}chess;
typedef class chess_node
{
public:
	chess_node* prev;//指向上一个结点的指针
	chess_node* next;//指向下一个结点的指针
	chess chess1;
}chess_node;

class chess_man
{
private:
	chess_node* head, * now, * last;
	string file;
	int length;
public:
	chess_man();							//构造函数开始新游戏的时候用的
	chess_man(string file1, int i);					//这是重载构造函数，载入进度或者复盘的时候用的
	void change_file(string file2);			//这个实在是不知道用来干什么用的
//注意，这里函数名字是creat_chess,creat后面没有e。
	void creat_chess(chess chess2);		   //这里是新建一个结点，下一步棋用的
	void delete_chess();					//这是删除一个结点，悔棋的时候用的
	void save(int x);//（1（读档）, 2（复盘））;//这是保存进度，注意为了读档和为了复盘这是两种不同的保存，要用不同的文件后缀
	void jumpup();							//这是跳到上一步
	void jumpdown();						//这是跳到下一步，复盘的时候用的
	chess get_chess();						//这是得到当前那一步的那个棋子的指针


};
chess_man::chess_man()						//这个构造函数应该要读文件才对
{
	head = new chess_node;
	last = new chess_node;
	head->next = last;
	head->prev = nullptr;
	last->next = nullptr;
	last->prev = head;
	//iofile = nullptr;						//这个哪里错了？
	length = 0;
	file = { 0 };
	now = head->next;						//一开始now指针是指向head得下一个的空间
}
//这个复制构造函数是载入进度或者复盘的时候用的，所以要读文件
chess_man::chess_man(string file1, int i)			//为什么这里要有一个参数？
{
	if (i == 1)
	{
		head = new chess_node;
		last = new chess_node;
		head->next = last;
		head->prev = nullptr;
		last->next = nullptr;
		last->prev = head;
		file = file1;
		fstream iofile;
		iofile.open("date1\\" + file + ".ld", ios::in);//注意这里date文件夹的位置可能放错了

		iofile >> length;
		int i = 0;//用来控制从文件里面读取数据
		for (i = 0; i < length; i++)//之所以不是 <= 是因为i是从0开始的
		{
			chess_node* temp1 = new chess_node;
			chess_node* temp2 = new chess_node;
			/*其实可以直接写temp2=last->prev;
			*/
			temp2 = head->next;				//这里可能会有错，因为没有写temp2->prev=head;
			while (temp2 != last)
			{
				temp2 = temp2->next;
			}
			temp2 = temp2->prev;
			temp2->next = temp1;
			temp1->prev = temp2;
			temp1->next = last;
			last->prev = temp1;
			iofile >> temp1->chess1.x >> temp1->chess1.y >> temp1->chess1.z;//这里可能会有错，因为有太多"->"了
			//这里可能会错，因为endl，在往文件输入数据的时候，是有换行符的，然而在读取数据的时候却没有，可能会错
		}
		now = head->next;//要注意这里是构造函数，要把所有的数据都初始化//now一开始是指向head的下一个，即第一个储存数据的空间
		iofile.close();
	}
	if (i == 2)
	{
		head = new chess_node;
		last = new chess_node;
		head->next = last;
		head->prev = nullptr;
		last->next = nullptr;
		last->prev = head;
		file = file1;
		fstream iofile;
		iofile.open("date2\\" + file + ".rp", ios::in);//注意这里date文件夹的位置可能放错了

		iofile >> length;
		int i = 0;//用来控制从文件里面读取数据
		for (i = 0; i < length; i++)//之所以不是 <= 是因为i是从0开始的
		{
			chess_node* temp1 = new chess_node;
			chess_node* temp2 = new chess_node;
			/*其实可以直接写temp2=last->prev;
			*/
			temp2 = head->next;				//这里可能会有错，因为没有写temp2->prev=head;
			while (temp2 != last)
			{
				temp2 = temp2->next;
			}
			temp2 = temp2->prev;
			temp2->next = temp1;
			temp1->prev = temp2;
			temp1->next = last;
			last->prev = temp1;
			iofile >> temp1->chess1.x >> temp1->chess1.y >> temp1->chess1.z;//这里可能会有错，因为有太多"->"了
			//这里可能会错，因为endl，在往文件输入数据的时候，是有换行符的，然而在读取数据的时候却没有，可能会错
		}
		now = head->next;//要注意这里是构造函数，要把所有的数据都初始化//now一开始是指向head的下一个，即第一个储存数据的空间
		iofile.close();
	}
}
void chess_man::change_file(string file2)
{
	file = file2;							//这个可能不会满足需求，需要重做

}
//注意，这里函数名字是creat_chess,creat后面没有e。
void chess_man::creat_chess(chess chess2)
{
	chess_node* temp = last;			//这里的temp是干什么用的？//不知道
	last->chess1 = chess2;
	last->next = new chess_node;
	chess_node* p; p = last;
	last = last->next;
	last->prev = p;
	last->next = nullptr;
	length++;
	now = last->prev;//这里是让now指向倒数第二个，即最后一个储存数据的空间
	//这里可能会出错，因为只写了now=last->prev;
}
void chess_man::delete_chess()//这里删除的是倒数第二个结点
{
	if (length == 0)
	{
		//cout << "链表为空";
		return;
	}
	else {
		//这里也可以直接用last，不用从头指针开始捋
		chess_node* temp1, * temp2;
		temp1 = last->prev;
		temp2 = temp1->prev;
		temp2->next = last;
		last->prev = temp2;
		delete temp1;
		now = temp2;
		length--;
		return;
	}
}
void chess_man::save(int x)
{
	if (x == 1)
	{
		int i = 1;		//用来控制while循环的
		chess_node* temp; temp = head->next;
		string  filename;
		cin >> filename;
		fstream iofile;
		iofile.open("date1\\" + filename + ".ld", ios::out);
		iofile << length << endl;								//这里是把头空间的length储存到文件里面
		if (length > 0)
		{
			while (i <= length)
			{

				iofile << temp->chess1.x << endl << temp->chess1.y << endl << temp->chess1.z << endl;//注意temp->chess1->x是错误的，电脑会显示"表达式必须包含指针类型"
				i++;
				temp = temp->next;
			}
		}
		iofile.close();
		fstream file("allname1.txt", ios::out | ios::app);//注意，这里很容易犯错误，一定要在文件尾添加数据，而不是直接写数据，因为直接写数据会把原先的数据给删了
		file << filename + ".ld" << endl;//这里可能会报错//注意一定要有换行符
		file.close();
	}
	if (x == 2)
	{
		int i = 1;		//用来控制while循环的
		chess_node* temp; temp = head->next;
		string  filename;
		cin >> filename;
		fstream iofile;
		iofile.open("date2\\" + filename + ".rp", ios::out);
		iofile << length << endl;								//这里是把头空间的length储存到文件里面
		if (length > 0)
		{
			while (i <= length)
			{
				iofile << temp->chess1.x << endl << temp->chess1.y << endl << temp->chess1.z << endl;//注意temp->chess1->x是错误的，电脑会显示"表达式必须包含指针类型"
				i++;
				temp = temp->next;
			}
		}
		iofile.close();
		iofile.close();
		fstream file("allname2.txt", ios::out | ios::app);
		file << filename + ".rp" << endl;//注意一定要有换行符
		file.close();
	}
}
void chess_man::jumpup()//这个应该是改变指针now的值，使之指向上一个
{
	now = now->prev;
}
void chess_man::jumpdown()
{
	now = now->next;
}
chess chess_man::get_chess()
{
	chess temp;
	temp.x = now->chess1.x;
	temp.y = now->chess1.y;
	temp.z = now->chess1.z;
	return temp;
}
