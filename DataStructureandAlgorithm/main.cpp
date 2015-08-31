#include <iostream>
#include "LinkNode.hpp"

using namespace std;

int main()
{
	int a[4] = { 1, 4, 2, 3 };

	LinkList List1(a,4);
	LinkList List2(List1);
	List2.insert(3, 4);

	LinkList List3;
	List3.build();
	List3.print();
	List3.sort();
	List3.print();

	return 0;
}