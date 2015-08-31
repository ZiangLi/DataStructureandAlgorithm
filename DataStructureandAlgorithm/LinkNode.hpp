#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int val;
	Node* next;
	Node(int _val,Node* _next = NULL) :val(_val),next(_next){}
};

//������
class LinkList
{
public:
	int length;
	Node* first;

	/*���캯����
	1.�����鹹�죻
	2.���ƹ��죻
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
	/*��������*/
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
	/*��̬����*/
	void build()
	{
		printf("Please enter elements of the list:\n");

		int tempVal;

		cin >> tempVal;
		first = new Node(tempVal);
		Node* tail_ptr=first;
		length = 1;
		while (cin.get()!='\n')
		{
			cin >> tempVal;
			Node* temp = new Node(tempVal);
			tail_ptr->next = temp;
			tail_ptr = temp;
			length++;
		}
	}
	/*���룺��λ��n������ֵ_val*/
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
	/*ɾ����ɾ��λ��n����Ԫ��*/
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
	/*����������m��nλ��Ԫ��*/
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
	/*���򣺶���������*/
	//��������
	void sort()
	{
		if (length == 1) return;
		//pre_cur:��¼����λ�õ�ǰָ��
		//pre_insert����¼����λ�õ�ǰָ��
		Node* cur_ptr = first;
		Node* pre_cur = cur_ptr;
		cur_ptr = cur_ptr->next;

		while (cur_ptr != NULL)
		{
			int insert_val = cur_ptr->val;
			
			if (insert_val <= first->val)
			{
				pre_cur->next = cur_ptr->next;
				cur_ptr->next = first;
				first = cur_ptr;
				pre_cur = pre_cur->next;
				cur_ptr = pre_cur->next;
				continue;
			}

			Node* insert_ptr = first;
			Node* pre_insert = insert_ptr;

			while (insert_ptr != cur_ptr && insert_ptr->val <= insert_val)
			{
				pre_insert = insert_ptr;
				insert_ptr = insert_ptr->next;
			}
			if (insert_ptr != cur_ptr)
			{
				pre_cur->next = cur_ptr->next;

				cur_ptr->next = insert_ptr;
				pre_insert->next = cur_ptr;
				cur_ptr = pre_cur->next;
			}
			else
			{
				pre_cur = pre_cur->next;
				cur_ptr = pre_cur->next;
			}
		}
	}
	void QuickSort(Node* &first, Node* &tail)
	{
		if (first == NULL) return;
		Node* first1, *first2, *tail1, *tail2,*pre1,*pre2;
		first1 = first2 = tail1 = tail2 = pre1 = pre2 = NULL;

		Node* pCurrent = first;
		int key = first->val;
		pCurrent = pCurrent->next;
		first->next = NULL;

		while (pCurrent != NULL)
		{
			if (pCurrent->val < key)
			{
				if (!first1)
				{
					first1 = pCurrent;
					pre1 = first1;
				}
				else
				{
					pre1->next = pCurrent;
					pre1 = pCurrent;
				}
				pCurrent = pCurrent->next;
				pre1->next = NULL;
			}
			else
			{
				if (!first2)
				{
					first2 = pCurrent;
					pre2 = first2;
				}
				else
				{
					pre2->next = pCurrent;
					pre2 = pCurrent;
				}
				pCurrent = pCurrent->next;
				pre2->next = NULL;
			}
		}
		tail1 = pre1,tail2=pre2;

		QuickSort(first1, tail1);
		QuickSort(first2, tail2);

		if (tail1 && first2)
		{
			tail1->next = first;
			first->next = first2;
			first = first1;
			tail = tail2;
		}
		else if (!tail1)
		{
			first->next = first2;
			tail = tail2;
		}
		else if (!first2)
		{
			tail1->next = first;
			tail = first;
			first = first1;
		}
	}

	void qsort()
	{
		Node* tail = NULL;
		QuickSort(first, tail);
	}
	/*���ң�����Ԫ��val������λ��*/
	/*��ת����ת����*/
	/*��ȡβָ��*/
	/*��ӡ*/
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

//}
/*����ڵ�����:
	1.�ж��������Ƿ��л�
	2.�����ӡ
	3.�ж����������Ƿ��ཻ���ཻ�������һ���ཻ�ڵ�
	4.���ҵ�k���Ԫ��
*/