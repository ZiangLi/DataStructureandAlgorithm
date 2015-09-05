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
	3.移动构造
	*/
	LinkList(){}
	LinkList(int array[], int num)
	{
		printf("Call construction!\n");
		first = NULL;
		for (int i = num - 1; i >= 0;--i)
		{
			Node *temp = new Node(array[i], first);
			first = temp;
		}
		length = num;
	}
	LinkList(const LinkList& list)
	{
		printf("Call copy construction!\n");
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
	//移动构造函数
	LinkList(LinkList&& list)
	{
		printf("Call move construction!\n");
		first = list.first;
		list.first = NULL;
	}
	/*析构函数*/
	~LinkList()
	{
		printf("Call Destruction!\n");
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
		while (cin.get()!='\n')
		{
			cin >> tempVal;
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
	//插入排序
	void sort()
	{
		if (length == 1) return;
		//pre_cur:记录遍历位置的前指针
		//pre_insert：记录插入位置的前指针
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
	//快速排序
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
	/*查找：查找元素val的所有位置*/

	/*反转：反转链表*/
	void Reverse()
	{
		Node* pCurrent = first;
		Node* pReverseHead = NULL;
		while (pCurrent != NULL)
		{
			Node* pTemp = pCurrent;
			pCurrent = pCurrent->next;
			pTemp->next = pReverseHead;
			pReverseHead = pTemp;
		}
		first = pReverseHead;
	}

	Node* ReverseList(Node* pHead)
	{
		if (pHead == NULL || pHead->next == NULL)
			return pHead;
		Node* pReverseHead = ReverseList(pHead->next);
		pHead->next->next = pHead;
		pHead->next = NULL;
		return pReverseHead;
	}
	void Reverse_recursive()
	{
		first = ReverseList(first);
	}
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
	void print(int n) const
	{
		if (length < n)
		{
			throw n;
		}
		int count = 1;
		Node* pCurrent = first;
		while (count < n)
		{
			pCurrent = pCurrent->next;
			count++;
		}
		printf("%d\n", pCurrent->val);
	}
	//合并两个链表(重载加号)
	LinkList operator+(LinkList& List1) const
	{
		LinkList TempList(*this);
		Node* pCurrent = TempList.first;
		while (pCurrent->next != NULL)
			pCurrent = pCurrent->next;

		Node* pCurrent1 = List1.first;
		while (pCurrent1 != NULL)
		{
			Node* temp = new Node(pCurrent1->val);
			pCurrent->next = temp;
			pCurrent = temp;
			pCurrent1 = pCurrent1->next;
		}
		TempList.length = TempList.length + List1.length;
		return TempList;
	}

	//排序地合并两个链表_递归
	void SortMergeList(LinkList& List)
	{
		this->sort();
		List.sort();
		first = Merge_recursive(first, List.first);
		length += length;
		List.first = NULL;
		List.length = 0;
	}
	Node* Merge_recursive(Node* phead1, Node* phead2)
	{
		if (phead1 == NULL && phead2 == NULL)
			return NULL;
		else if (phead1 == NULL)
			return phead2;
		else if (phead2 == NULL)
			return phead1;

		Node* pheadNew = NULL;
		if (phead1->val < phead2->val)
		{
			pheadNew = phead1;
			pheadNew->next = Merge_recursive(phead1->next, phead2);
		}
		else
		{
			pheadNew = phead2;
			pheadNew->next = Merge_recursive(phead1, phead2->next);
		}

		return pheadNew;
	}

};

//}
/*链表节点运算:
	1.判断链表中是否有环
	2.反向打印
	3.判断两个链表是否相交，相交则求其第一个相交节点
	4.查找第k大的元素
*/

//合并有序链表_迭代
Node* Merge(Node* pHead1, Node* pHead2)
{
	if (pHead1 == NULL && pHead2 == NULL)
		return NULL;
	else if (pHead1 == NULL)
		return pHead2;
	else if (pHead2 == NULL)
		return pHead1;

	Node* pHeadNew = NULL;
	Node* pCurrent1 = pHead1;
	Node* pCurrent2 = pHead2;
	if (pHead1->val < pHead2->val)
	{
		pHeadNew = pHead1;
		pCurrent1 = pCurrent1->next;
	}
	else
	{
		pHeadNew = pHead2;
		pCurrent2 = pCurrent2->next;
	}

	Node* pCurrent = pHeadNew;
	while (pCurrent1 != NULL && pCurrent2 != NULL)
	{
		if (pCurrent1->val < pCurrent2->val)
		{
			pCurrent->next = pCurrent1;
			pCurrent1 = pCurrent1->next;
		}
		else
		{
			pCurrent->next = pCurrent2;
			pCurrent2 = pCurrent2->next;
		}
		pCurrent = pCurrent->next;
		pCurrent->next = NULL;
	}
	if (pCurrent1 == NULL)
	{
		pCurrent->next = pCurrent2;
	}
	else
	{
		pCurrent->next = pCurrent1;
	}
	return pHeadNew;
}