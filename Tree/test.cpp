#include <iostream>
#include "BinTree.h"
using namespace std;

int main()
{
	BinTree<int> test;
	test.insertAsRoot(1);
	cout << test.size();
	return 0;
}
