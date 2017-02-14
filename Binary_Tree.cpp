//=========二叉树(Binary Tree)===========
#define _CRT_SECURE_NO_WARNINGS
#include<stack>
#include<queue>
using namespace std;
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define max(a , b) (a>b?a:b)//带参宏,听说比使用函数更好(inline)
#define TElemType int
#define Status int

//-----二叉树的链式存储---------------- 
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lChild, *rChild;
}BiTNode, *BiTree;

//----------基本操作的函数原型说明----------------- 
Status createBiTree(BiTree *T);
Status printBiTree(TElemType *data);
Status Add(TElemType *data);
Status PreorderTraverse(BiTree T, Status(*visit)(TElemType *data));
Status traversePreorder(BiTree T, Status(*visit)(TElemType *data));
Status InorderTraverse(BiTree T, Status(*visit)(TElemType* data));
Status PostorderTraverse(BiTree T, Status(*visit)(TElemType* data));
Status traversePostorder(BiTree T, Status(*visit)(TElemType* data));
Status traverseInorder(BiTree T, Status(*visit)(TElemType* data));
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType* data));//层次遍历
int    BiTreeDepth(BiTree T);
int    depdhBiTree(BiTree T);
//Status clearBiTree(BiTree *T);//将树T清为空树
//Status destroyBiTree(BiTree *T);//摧毁二叉树T

//-----------------------------------------------------主函数----------------------------------------------------------------
int main() {
	//paste your code here
	//freopen("d:\\coding\\data.in", "r", stdin);
	BiTree T;
	createBiTree(&T);
	//PreorderTraverse(T, printBiTree);//已测试
	//InorderTraverse(T, printBiTree);//已测试
	//PostorderTraverse(T, printBiTree);//已测试
	//traverseInorder(T, printBiTree);//非递归中序遍历二叉树已测试
	//traversePreorder(T, printBiTree);//非递归先根序遍历二叉树，已测试
	//traversePostorder(T, printBiTree);//递推后根序遍历二叉树，已测试
	//LevelOrderTraverse(T, printBiTree);//层次遍历，已测试
	//printf("%d\n", BiTreeDepth(T));//求二叉树的深度，已测试
	//printf("%d\n",depdhBiTree(T));//递归求二叉树的深度，已测试
	InorderTraverse(T, printBiTree);
	printf("\n");
	traverseInorder(T,Add);
	InorderTraverse(T, printBiTree);

	while (1);
	return 0;
}

Status createBiTree(BiTree *T) {
	TElemType data;
	scanf("%d", &data);
	if (data == -1) (*T) = NULL;//每个叶子节点用-1表示，必须输入 
	else {
		if (!((*T) = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		(*T)->data = data;
		createBiTree(&((*T)->lChild));
		createBiTree(&((*T)->rChild));
	}

	return OK;
}
Status printBiTree(TElemType *data) {
	printf("%d\t", *data);
	return OK;
}
Status traversePreorder(BiTree T, Status(*visit)(TElemType *data)) {
	stack<BiTree>S;
	BiTree p = T;
	while (!(p == NULL && S.empty())) {
		if (p !=  NULL) {
			visit(&p->data);
			if (p->rChild != NULL) S.push(p->rChild);
			p = p->lChild;
		}
		else {
			p = S.top();
			S.pop();
		}
	}
	return OK;
}
Status traverseInorder(BiTree T, Status(*visit)(TElemType *data)) {
	stack<BiTree>S;
	BiTree p = T;//初始时指针p指向树根
	while (!(p == NULL && S.empty())) {//递推结束条件
		if (p != NULL) {
			S.push(p);
			p = p->lChild;
		}
		else {
			//此时p是空的，栈是不空的。因为若栈也空，则递推已经结束了，放心使用取值弹出操作
			p = S.top();
			S.pop();
			visit(&p->data);
			p = p->rChild;
		}
	}
	return OK;
}
Status traversePostorder(BiTree T, Status(*visit)(TElemType* data)) {
	stack<BiTree>S;
	BiTree p = T,pre=NULL;
	while (!(p == NULL && S.empty())) {
		if (p != NULL) {
			S.push(p);
			p = p->lChild;//直到左孩子为空，栈顶是最左下的节点
		}
		else {
			p = S.top();
			if (p->rChild != NULL && p->rChild!=pre) {//若果右子树存在且未被访问过
				p = p->rChild;
				S.push(p);
				p = p->lChild;
			}
			else {
				visit(&p->data);
				pre = p;
				S.pop();
				p = NULL;
			}
		}
	}//BINGO，设置了一个前驱指针，来区分右子树是否被访问过
	return OK;
}
Status PreorderTraverse(BiTree T, Status(*visit)(TElemType* data)) {
	//先序遍历
	if (T == NULL) return OK;//若二叉树为空，则空操作
	visit(&T->data);//访问根节点
	PreorderTraverse(T->lChild, visit);//先序遍历左子树
	PreorderTraverse(T->rChild, visit);//先序遍历右子树
	return OK;//返回值
}
Status InorderTraverse(BiTree T, Status(*visit)(TElemType* data)) {
	if (T == NULL)return OK;//二叉树为空，则空操作
	InorderTraverse(T->lChild, visit);//中序遍历左子树
	visit(&T->data);//访问根节点
	InorderTraverse(T->rChild, visit);//中序遍历右子树
	return OK;//返回值
}
Status PostorderTraverse(BiTree T, Status(*visit)(TElemType *data)) {
	//后序遍历
	if (T == NULL) return OK;//若二叉树为空，则空操作
	PostorderTraverse(T->lChild, visit);//中序遍历左子树
	PostorderTraverse(T->rChild, visit);//中序遍历右子树
	visit(&T->data);//访问根节点
	return OK;//返回值
}
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType* data)) {
	//层次遍历二叉树，理论上用宽度优先搜索的思想可以实现此遍历
	queue<BiTree>Q;
	Q.push(T);
	BiTree p = NULL;
	while (!Q.empty()) {
		p = Q.front();
		visit(&p->data);
		Q.pop();
		if (p->lChild != NULL) {
			Q.push(p->lChild);
		}
		if (p->rChild != NULL) {
			Q.push(p->rChild);
		}
	}//一遍过
	return OK;
}
int    BiTreeDepth(BiTree T) {
	//用深度搜索的思想应该能实现，分递归、递推两种
	int length = 0;//初始化树的深度
	BiTree p = T;
	if (p == NULL) return 0;//递归出口，千万不要死循环了
	length = length + 1 + max(BiTreeDepth(p->lChild), BiTreeDepth(p->rChild));
	return length;//递归还是比较容易实现的
}
int    depdhBiTree(BiTree T) {
	if (T == NULL) return 0;
	int length = 1;//根算一层
	BiTree p = T;
	queue<BiTree>Q;
	Q.push(T);
	Q.push(NULL);//NULL表示一层结束
	while (Q.size()>1) {//有一个层结束标志时而在队列中
		p = Q.front();
		Q.pop();
		if (p != NULL) {
			if (p->lChild != NULL) Q.push(p->lChild);
			if (p->rChild != NULL) Q.push(p->rChild);
		}
		else {
			length++;
			Q.push(NULL);
		}
	}
	return length;
}
Status Add(TElemType *data) {
	(*data)++;
	return OK;
}

//宽度优先搜索BFS用队列；而且深度优先搜索也用队列
//若出现一个无法解析的……，说明函数名写错了
//优先级 ->第一级，*和&同级（自右至左）

/*输入数据：
1 2 8 -1 10 -1 -1 9 -1 -1 3 4 -1 -1 5 -1 6 -1 7 -1 -1
*/
