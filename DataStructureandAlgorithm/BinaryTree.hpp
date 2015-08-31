#include <iostream>

using namespace std;

struct BTNode
{
	int val;
	BTNode* lchild;
	BTNode* rchild;
	BTNode(int _val, BTNode* _lchild = NULL, BTNode* _rchild = NULL) :val(_val), lchild(_lchild), rchild(_rchild){}
};

class BinayTree
{
	BTNode* root;
	//构造、重建、镜像
	//插入、删除、查找
	//前向、后向、中序、分层遍历
	//K层节点数、层数
	//是否平衡
};

//两个二叉树结构是否相同
//二分查找
//堆排序