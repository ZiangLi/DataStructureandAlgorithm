#include <iostream>
#include <string>
#include "LinkNode.hpp"

using namespace std;

int main()
{
	int a[4] = { 8,4, 6 };
	int b[9] = { 9, 3,3,1,3,5,3,1,4 };

	try
	{

		LinkList List1(a, 3);
		LinkList List2(b, 9);
		LinkList List3(a, 3);
		LinkList List4=List1+List2+List3;
		LinkList List5 = move(List4);
		List4.print();
		int a = 0;
	}
	catch (...)
	{
		cout<<"Invaild input!"<<endl;
		exit(1);
	}
	return 0;
}