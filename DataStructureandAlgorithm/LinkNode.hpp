#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int val;
	Node* next;
	Node(int _val,Node* _next = NULL) :val(_val),next(_next){}
};

//链表类
class LinkList
{
public:
	int length;
	Node* first;

	/*构造函数：
	1.用数组构造；
	2.复制构造；
	*/
	LinkList(){}
	LinkList(int array[], int num)
	{
		first = NULL;
		for (int i = num - 1; i >= 0;--i)
		{
			Node *temp = new Node(array[i], first);
			first = temp;
		}
		length = num;
	}
	LinkList(LinkList& list)
	{
		Node* cur_ptr=list.first;
		first = new Node(cur_ptr->val);
		cur_ptr = cur_ptr->next;

		Node* tail_ptr=first;

		while (cur_ptr != NULL)
		{
			Node* temp = new Node(cur_ptr->val);
			tail_ptr->next = temp;
			tail_ptr = temp;
			cur_ptr = cur_ptr->next;
		}
		length = list.length;
	}
	/*析构函数*/
	~LinkList()
	{
		Node* cur_ptr = first;
		while (cur_ptr != NULL)
		{
			Node* temp = cur_ptr;
			cur_ptr = cur_ptr->next;
			delete temp;
		}
	}
	/*动态构造*/
	void build()
	{
		printf("Please enter elements of the list:\n");

		int tempVal;

		cin >> tempVal;
		first = new Node(tempVal);
		Node* tail_ptr=first;
		length = 1;
		while (cin >> tempVal && cin.get()!='\n')
		{
			Node* temp = new Node(tempVal);
			tail_ptr->next = temp;
			tail_ptr = temp;
			length++;
		}
	}
	/*插入：在位置n处插入值_val*/
	void insert(int n,int _val)
	{
		if (n > length + 1 || n<1)
		{
			printf("Invaild insert position!\n");
			return;
		}

		length++;
		if (n == 1)
		{
			Node* temp = new Node(_val, first);
			first = temp;
			return;
		}

		int count = 0;
		Node* cur_ptr = first;
		while (++count != n-1)
		{
			cur_ptr=cur_ptr->next;
		}
		Node* temp = new Node(_val, cur_ptr->next);
		cur_ptr->next = temp;

	}
	/*删除：删除位置n处的元素*/
	void delt(int n)
	{
		if (n>length || n<1)
		{
			printf("Invaild insert position!\n");
			return;
		}
		length--;
		if (n == 1)
		{
			Node* temp = first;
			first = first->next;
			delete temp;
			return;
		}

		int count = 0;
		Node* cur_ptr = first;
		while (++count != n - 1)
		{
			cur_ptr = cur_ptr->next;
		}
		Node* temp = cur_ptr->next;
		cur_ptr->next = cur_ptr->next->next;
		delete temp;
	}
	/*交换：交换m、n位置元素*/
	void swap(int m, int n)
	{
		if (m > length || n > length)
		{
			printf("Invaild position!\n");
			return;
		}
		if (m > n)
		{
			int temp=m;
			m = n;
			n = temp;
		}
		Node* cur_ptr=first,*m_ptr;
		int count = 1;
		while (count != m)
		{
			cur_ptr = cur_ptr->next;
			count++;
		}
		int temp = cur_ptr->val;
		m_ptr = cur_ptr;

		while (count != n)
		{
			cur_ptr = cur_ptr->next;
			count++;
		}
		m_ptr->val = cur_ptr->val;
		cur_ptr->val = temp;
	}
	/*排序：对链表排序*/
	void sort()
	{

	}
	/*查找：查找元素val的所有位置*/
	/*反转：反转链表*/
	/*提取尾指针*/
	/*打印*/
	void print() const
	{
		Node* cur_ptr=first;
		while (cur_ptr != NULL)
		{
			printf("%d->", cur_ptr->val);
			cur_ptr = cur_ptr->next;
		}
		printf("NULL\n");
	}
	int print(int n) const
	{

	}

};

/*链表节点运算:
	1.判断链表中是否有环
	2.反向打印
	3.判断两个链表是否相交，相交则求其第一个相交节点
	4.查找第k大的元素
*/