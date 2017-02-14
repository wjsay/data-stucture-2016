//=========������(Binary Tree)===========
#define _CRT_SECURE_NO_WARNINGS
#include<stack>
#include<queue>
using namespace std;//��������C++
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define max(a , b) (a>b?a:b)//���κ�,��˵��ʹ�ú�������(inline)
#define TElemType int
#define Status int
int leaves;//����һ����Ҷ���õ�ȫ�ֱ���

//-----����������ʽ�洢---------------- 
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lChild, *rChild;
}BiTNode, *BiTree;

//----------���������ĺ���ԭ��˵��----------------- 
Status createBiTree(BiTree *T);
Status printBiTree(BiTNode *Node);
Status Add(BiTNode *Node);
Status PreorderTraverse(BiTree T, Status(*visit)(BiTNode *Node));
Status traversePreorder(BiTree T, Status(*visit)(BiTNode *Node));
Status InorderTraverse(BiTree T, Status(*visit)(BiTNode *Node));
Status PostorderTraverse(BiTree T, Status(*visit)(BiTNode *Node));
Status traversePostorder(BiTree T, Status(*visit)(BiTNode *Node));
Status traverseInorder(BiTree T, Status(*visit)(BiTNode *Node));
Status LevelOrderTraverse(BiTree T, Status(*visit)(BiTNode *Node));//��α���
int    BiTreeDepth(BiTree T);
int    depdhBiTree(BiTree T);
int    LeavesSum(BiTree T);
Status leaves_sum(BiTNode *Node);
Status Visit(BiTNode *Node);
Status similar(BiTree T1, BiTree T2, Status(*visit)(BiTNode *Node));
//���������Ƿ����ƣ������ڱ����Ǽ�¼��ֵ���ٱȽ���������������Ƿ�һ��������Ҫ��������+ǰ��������Σ�
Status ClearBiTree(BiTree *T);//����T��Ϊ����
Status clearBiTNode(BiTNode *Node);
Status DestroyBiTree(BiTree *T);//�ݻٶ�����T
Status ExchangeBiTree(BiTree *T);//�����������Һ��ӣ���ֽ�ķ�����ܿ��������Ľ����������
Status CompleteBiTree(BiTree T);//�ж��Ƿ�����ȫ������


//-----------------------------------------------------������----------------------------------------------------------------
int main() {
	//paste your code here
	//freopen("d:\\coding\\data.in", "r", stdin);
	BiTree T,T2;
	createBiTree(&T);
	createBiTree(&T2);
	//PreorderTraverse(T, printBiTree);//�Ѳ���
	//InorderTraverse(T, printBiTree);//�Ѳ���
	//PostorderTraverse(T, printBiTree);//�Ѳ���
	//traverseInorder(T, printBiTree);//�ǵݹ���������������Ѳ���
	//traversePreorder(T, printBiTree);//�ǵݹ��ȸ���������������Ѳ���
	//traversePostorder(T, printBiTree);//���ƺ����������������Ѳ���
	//LevelOrderTraverse(T, printBiTree);//��α������Ѳ���
	//printf("%d\n", BiTreeDepth(T));//�����������ȣ��Ѳ���
	//printf("%d\n",depdhBiTree(T));//�ݹ������������ȣ��Ѳ���
	//if (similar(T, T2, Visit)==OK) printf("YES\n");
	//else printf("NO\n");
	LevelOrderTraverse(T, printBiTree);printf("\n");
	//ClearBiTree(&T);//������������Ľڵ�ȫֵΪ���ˣ������ڴݻ���
	//DestroyBiTree(&T);//���������Ѳ���
	//printf("1\n");
	//ExchangeBiTree(&T);//�����������ĵݹ��㷨���Ѳ���
	//LevelOrderTraverse(T, printBiTree);
	//traverseInorder(T2, Add);//���������޸�һ��
	//InorderTraverse(T2, printBiTree);printf("\n");
	//similar(T, T2, Visit) == OK ? puts("YES") : puts("NO");
	//printf("Leaves = %d\n", LeavesSum(T));//��Ҷ����Ŀ���Ѳ���
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
	if (data == -1) (*T) = NULL;//ÿ��Ҷ�ӽڵ���-1��ʾ���������� 
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
	BiTree p = T;//��ʼʱָ��pָ������
	while (!(p == NULL && S.empty())) {//���ƽ�������
		if (p != NULL) {
			S.push(p);
			p = p->lChild;
		}
		else {
			//��ʱp�ǿյģ�ջ�ǲ��յġ���Ϊ��ջҲ�գ�������Ѿ������ˣ�����ʹ��ȡֵ��������
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
			//�Ͳ�������
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
			p = p->lChild;//ֱ������Ϊ�գ�ջ���������µĽڵ�
		}
		else {
			p = S.top();
			if (p->rChild != NULL && p->rChild != pre) {//����������������δ�����ʹ�
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
	}//BINGO��������һ��ǰ��ָ�룬�������������Ƿ񱻷��ʹ�
	return OK;
}
Status PreorderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	//�������
	if (T == NULL) return OK;//��������Ϊ�գ���ղ���
	visit(T);//���ʸ��ڵ�
	PreorderTraverse(T->lChild, visit);//�������������
	PreorderTraverse(T->rChild, visit);//�������������
	return OK;//����ֵ
}
Status InorderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	if (T == NULL)return OK;//������Ϊ�գ���ղ���
	InorderTraverse(T->lChild, visit);//�������������
	visit(T);//���ʸ��ڵ�//ʵ��֤����visit�������޸�T
	InorderTraverse(T->rChild, visit);//�������������
	return OK;//����ֵ
}
Status PostorderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	//�������
	if (T == NULL) return OK;//��������Ϊ�գ���ղ���
	PostorderTraverse(T->lChild, visit);//�������������
	PostorderTraverse(T->rChild, visit);//�������������
	visit(T);//���ʸ��ڵ�
	return OK;//����ֵ
}
Status LevelOrderTraverse(BiTree T, Status(*visit)(BiTNode *Node)) {
	//��α������������������ÿ������������˼�����ʵ�ִ˱���
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
	}//һ���
	return OK;
}
int    BiTreeDepth(BiTree T) {
	//�����������˼��Ӧ����ʵ�֣��ֵݹ顢��������
	int length = 0;//��ʼ���������
	BiTree p = T;
	if (p == NULL) return 0;//�ݹ���ڣ�ǧ��Ҫ��ѭ����
	length = length + 1 + max(BiTreeDepth(p->lChild), BiTreeDepth(p->rChild));
	return length;//�ݹ黹�ǱȽ�����ʵ�ֵ�
}
int    depdhBiTree(BiTree T) {
	if (T == NULL) return 0;
	int length = 1;//����һ��
	BiTree p = T;
	queue<BiTree>Q;
	Q.push(T);
	Q.push(NULL);//NULL��ʾһ�����
	while (Q.size()>1) {//��һ���������־ʱ���ڶ�����
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
	return OK;//�յķ��ʺ��������غ���
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
	return OK;//̫���ˣ���ûд����
}

//�����������BFS�ö��У����������������Ҳ�ö���
//������һ���޷������ġ�����˵��������д����
//���ȼ� ->��һ����*��&ͬ������������

/*�������ݣ�
1 2 8 -1 10 -1 -1 9 -1 -1 3 4 -1 -1 5 -1 6 -1 7 -1 -1
1 2 8 -1 -1 -1 -1
*/
/*���Ĵ���������е�������-1��ʾ��
1
2 3
8 9 4 5
-1 10 -1 -1 -1 6
 -1 -1         -1 7
			     -1 -1
*/
