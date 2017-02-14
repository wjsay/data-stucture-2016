//=========二叉树(Binary Tree)===========
#define _CRT_SECURE_NO_WARNINGS
#include<stack>
#include<queue>
using namespace std;//尽量少用C++
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define max(a , b) (a>b?a:b)//带参宏,听说比使用函数更好(inline)
#define TElemType int
#define Status int
int leaves;//定义一个求叶子用的全局变量

//-----二叉树的链式存储---------------- 
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lChild, *rChild;
}BiTNode, *BiTree;

//----------基本操作的函数原型说明----------------- 
Status createBiTree(BiTree *T);
Status printBiTree(BiTNode *Node);
Status Add(BiTNode *Node);
Status PreorderTraverse(BiTree T, Status(*visit)(BiTNode *Node));
Status traversePreorder(BiTree T, Status(*visit)(BiTNode *Node));
Status InorderTraverse(BiTree T, Status(*visit)(BiTNode *Node));
Status PostorderTraverse(BiTree T, Status(*visit)(BiTNode *Node));
Status traversePostorder(BiTree T, Status(*visit)(BiTNode *Node));
Status traverseInorder(BiTree T, Status(*visit)(BiTNode *Node));
Status LevelOrderTraverse(BiTree T, Status(*visit)(BiTNode *Node));//层次遍历
int    BiTreeDepth(BiTree T);
int    depdhBiTree(BiTree T);
int    LeavesSum(BiTree T);
Status leaves_sum(BiTNode *Node);
Status Visit(BiTNode *Node);
Status similar(BiTree T1, BiTree T2, Status(*visit)(BiTNode *Node));
//求两课树是否相似，可以在遍历是记录下值，再比较两棵树遍历结果是否一样（遍历要包含中序+前或后序两次）
Status ClearBiTree(BiTree *T);//将树T清为空树
Status clearBiTNode(BiTNode *Node);
Status DestroyBiTree(BiTree *T);//摧毁二叉树T
Status ExchangeBiTree(BiTree *T);//交换树的左右孩子，从纸的反面就能看到交换的结果，哈哈哈
Status CompleteBiTree(BiTree T);//判断是否是完全而叉树


//-----------------------------------------------------主函数----------------------------------------------------------------
int main() {
	//paste your code here
	//freopen("d:\\coding\\data.in", "r", stdin);
	BiTree T,T2;
	createBiTree(&T);
	createBiTree(&T2);
	//PreorderTraverse(T, printBiTree);//已测试
	//InorderTraverse(T, printBiTree);//已测试
	//PostorderTraverse(T, printBiTree);//已测试
	//traverseInorder(T, printBiTree);//非递归中序遍历二叉树已测试
	//traversePreorder(T, printBiTree);//非递归先根序遍历二叉树，已测试
	//traversePostorder(T, printBiTree);//递推后根序遍历二叉树，已测试
	//LevelOrderTraverse(T, printBiTree);//层次遍历，已测试
	//printf("%d\n", BiTreeDepth(T));//求二叉树的深度，已测试
	//printf("%d\n",depdhBiTree(T));//递归求二叉树的深度，已测试
	//if (similar(T, T2, Visit)==OK) printf("YES\n");
	//else printf("NO\n");
	LevelOrderTraverse(T, printBiTree);printf("\n");
	//ClearBiTree(&T);//清空树，把树的节点全值为零了，区别于摧毁树
	//DestroyBiTree(&T);//销毁树，已测试
	//printf("1\n");
	//ExchangeBiTree(&T);//交换左右数的递归算法，已测试
	//LevelOrderTraverse(T, printBiTree);
	//traverseInorder(T2, Add);//对整棵树修改一下
	//InorderTraverse(T2, printBiTree);printf("\n");
	//similar(T, T2, Visit) == OK ? puts("YES") : puts("NO");
	//printf("Leaves = %d\n", LeavesSum(T));//求叶子数目，已测试
	if (CompleteBiTree(T) == OK) printf("OK\n");
	else printf("NO\n");
	if (CompleteBiTree(T2))printf("YES\n");
	else printf("NO\n");
 
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
Status printBiTree(BiTNode *Node) {
	printf("%d\t", (*Node).data);
	return OK;
}
Status traversePreorder(BiTree T, Status(*visit)(BiTNode *Node)) {
	stack<BiTree>S;
	BiTree p = T;
	while (!(p == NULL && S.empty())) {
		if (p != NULL) {
			visit(&(*p));
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
Status traverseInorder(BiTree T, Status(*visit)(BiTNode *Node)) {
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
			visit(&(*p));
			p = p->rChild;
		}
	}
	return OK;
}
Status similar(BiTree T1, BiTree T2, Status(*visit)(BiTNode *Node)) {
	stack<BiTree>S1, S2;
	BiTree p1 = T1, p2 = T2;
	while (!(p1 == NULL && S1.empty()) || !(p2 == NULL && S2.empty())) {
		if (p1 != NULL && p2 != NULL) {
			S1.push(p1); p1 = p1->lChild;
			S2.push(p2); p2 = p2->lChild;
		}
		else if(p1==NULL && p2==NULL){
			p1 = S1.top(); S1.pop();
			p2 = S2.top(); S2.pop();
			//就不访问了
			p1 = p1->rChild;
			p2 = p2->rChild;
		}
		else {
			break;
		}
	}
	if (S1.empty() && S2.empty() && p1==NULL && p2==NULL) {
		return OK;
	}
	else {
		return ERROR;
	}
}
Status traversePostorder(BiTree T, Status(*visit)(BiTNode *Node)) {
	stack<BiTree>S;
	BiTree p = T, pre = NULL;
	while (!(p == NULL && S.empty())) {
		if (p != NULL) {
			S.push(p);
			p = p->lChild;//直到左孩子为空，栈顶是最左下的节点
		}
		else {
			p = S.top();
			if (p->rChild != NULL && p->rChild != pre) {//若果右子树存在且未被访问过
				p = p->rChild;
				S.push(p);
				p = p->lChild;
			}
			else {
				visit(&(*p));
				pre = p;
				S.pop();
				p = NULL;
			}
		}
	}//BINGO，设置了一个前驱指针，来区分右子树是否被访问过
	return OK;
}
Status PreorderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	//先序遍历
	if (T == NULL) return OK;//若二叉树为空，则空操作
	visit(T);//访问根节点
	PreorderTraverse(T->lChild, visit);//先序遍历左子树
	PreorderTraverse(T->rChild, visit);//先序遍历右子树
	return OK;//返回值
}
Status InorderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	if (T == NULL)return OK;//二叉树为空，则空操作
	InorderTraverse(T->lChild, visit);//中序遍历左子树
	visit(T);//访问根节点//实践证明，visit函数能修改T
	InorderTraverse(T->rChild, visit);//中序遍历右子树
	return OK;//返回值
}
Status PostorderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	//后序遍历
	if (T == NULL) return OK;//若二叉树为空，则空操作
	PostorderTraverse(T->lChild, visit);//中序遍历左子树
	PostorderTraverse(T->rChild, visit);//中序遍历右子树
	visit(T);//访问根节点
	return OK;//返回值
}
Status LevelOrderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	//层次遍历二叉树，理论上用宽度优先搜索的思想可以实现此遍历
	queue<BiTree>Q;
	Q.push(T);
	BiTree p = NULL;
	while (!Q.empty()) {
		p = Q.front();
		visit(&(*p));
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
Status Add(BiTNode *Node) {
	(*Node).data += 2;
	return OK;
}
Status leaves_sum(BiTNode *Node) {
	if ((*Node).lChild == NULL && (*Node).rChild == NULL) {
		++leaves;
	}
	return OK;
}
int    LeavesSum(BiTree T) {
	leaves = 0;
	InorderTraverse(T, leaves_sum);
	return leaves;
}
Status Visit(BiTNode *Node) {
	return OK;//空的访问函数，返回恒真
}
Status clearBiTNode(BiTNode *Node) {
	(*Node).data = 0;
	return OK;
}
Status ClearBiTree(BiTree *T) {
	LevelOrderTraverse(*T, clearBiTNode);
	return OK;
}
Status DestroyBiTree(BiTree *T) {
	if ((*T) != NULL) {
		if ((*T)->lChild != NULL) {
			DestroyBiTree(&((*T)->lChild));
		}
		if ((*T)->rChild != NULL) {
			DestroyBiTree(&(*T)->rChild);
		}
		free((*T));
		(*T) = NULL;
	}
	return OK;
}
Status ExchangeBiTree(BiTree *T) {
	BiTree p;
	if (*T == NULL) return OK;
	if ((*T)->lChild != NULL) ExchangeBiTree(&((*T)->lChild));
	if ((*T)->rChild != NULL) ExchangeBiTree(&((*T)->rChild));
	p = (*T)->lChild;
	(*T)->lChild = (*T)->rChild;
	(*T)->rChild = p;
	return OK;
}
Status CompleteBiTree(BiTree T){
	return OK;//太晚了，还没写出来
}

//宽度优先搜索BFS用队列；而且深度优先搜索也用队列
//若出现一个无法解析的……，说明函数名写错了
//优先级 ->第一级，*和&同级（自右至左）

/*输入数据：
1 2 8 -1 10 -1 -1 9 -1 -1 3 4 -1 -1 5 -1 6 -1 7 -1 -1
1 2 8 -1 -1 -1 -1
*/
/*树的大致情况，有点抽象哈，-1表示空
1
2 3
8 9 4 5
-1 10 -1 -1 -1 6
 -1 -1         -1 7
			     -1 -1
*/
