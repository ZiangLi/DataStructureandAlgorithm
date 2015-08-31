#include <iostream>
#include "LinkNode.hpp"

using namespace std;

int main()
{
	int a[3] = { 1, 2, 3 };

	LinkList List1(a,3);
	LinkList List2(List1);
	List2.insert(3, 4);
	List2.swap(1, 3);
	List2.print();

	return 0;
}