//=========������(Binary Tree)===========
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
#define max(a , b) (a>b?a:b)//���κ�,��˵��ʹ�ú�������(inline)
#define TElemType int
#define Status int

//-----����������ʽ�洢---------------- 
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lChild, *rChild;
}BiTNode, *BiTree;

//----------���������ĺ���ԭ��˵��----------------- 
Status createBiTree(BiTree *T);
Status printBiTree(TElemType *data);
Status Add(TElemType *data);
Status PreorderTraverse(BiTree T, Status(*visit)(TElemType *data));
Status traversePreorder(BiTree T, Status(*visit)(TElemType *data));
Status InorderTraverse(BiTree T, Status(*visit)(TElemType* data));
Status PostorderTraverse(BiTree T, Status(*visit)(TElemType* data));
Status traversePostorder(BiTree T, Status(*visit)(TElemType* data));
Status traverseInorder(BiTree T, Status(*visit)(TElemType* data));
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType* data));//��α���
int    BiTreeDepth(BiTree T);
int    depdhBiTree(BiTree T);
//Status clearBiTree(BiTree *T);//����T��Ϊ����
//Status destroyBiTree(BiTree *T);//�ݻٶ�����T

//-----------------------------------------------------������----------------------------------------------------------------
int main() {
	//paste your code here
	//freopen("d:\\coding\\data.in", "r", stdin);
	BiTree T;
	createBiTree(&T);
	//PreorderTraverse(T, printBiTree);//�Ѳ���
	//InorderTraverse(T, printBiTree);//�Ѳ���
	//PostorderTraverse(T, printBiTree);//�Ѳ���
	//traverseInorder(T, printBiTree);//�ǵݹ���������������Ѳ���
	//traversePreorder(T, printBiTree);//�ǵݹ��ȸ���������������Ѳ���
	//traversePostorder(T, printBiTree);//���ƺ����������������Ѳ���
	//LevelOrderTraverse(T, printBiTree);//��α������Ѳ���
	//printf("%d\n", BiTreeDepth(T));//�����������ȣ��Ѳ���
	//printf("%d\n",depdhBiTree(T));//�ݹ������������ȣ��Ѳ���
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
	if (data == -1) (*T) = NULL;//ÿ��Ҷ�ӽڵ���-1��ʾ���������� 
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
			p = p->lChild;//ֱ������Ϊ�գ�ջ���������µĽڵ�
		}
		else {
			p = S.top();
			if (p->rChild != NULL && p->rChild!=pre) {//����������������δ�����ʹ�
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
	}//BINGO��������һ��ǰ��ָ�룬�������������Ƿ񱻷��ʹ�
	return OK;
}
Status PreorderTraverse(BiTree T, Status(*visit)(TElemType* data)) {
	//�������
	if (T == NULL) return OK;//��������Ϊ�գ���ղ���
	visit(&T->data);//���ʸ��ڵ�
	PreorderTraverse(T->lChild, visit);//�������������
	PreorderTraverse(T->rChild, visit);//�������������
	return OK;//����ֵ
}
Status InorderTraverse(BiTree T, Status(*visit)(TElemType* data)) {
	if (T == NULL)return OK;//������Ϊ�գ���ղ���
	InorderTraverse(T->lChild, visit);//�������������
	visit(&T->data);//���ʸ��ڵ�
	InorderTraverse(T->rChild, visit);//�������������
	return OK;//����ֵ
}
Status PostorderTraverse(BiTree T, Status(*visit)(TElemType *data)) {
	//�������
	if (T == NULL) return OK;//��������Ϊ�գ���ղ���
	PostorderTraverse(T->lChild, visit);//�������������
	PostorderTraverse(T->rChild, visit);//�������������
	visit(&T->data);//���ʸ��ڵ�
	return OK;//����ֵ
}
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType* data)) {
	//��α������������������ÿ������������˼�����ʵ�ִ˱���
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
Status Add(TElemType *data) {
	(*data)++;
	return OK;
}

//�����������BFS�ö��У����������������Ҳ�ö���
//������һ���޷������ġ�����˵��������д����
//���ȼ� ->��һ����*��&ͬ������������

/*�������ݣ�
1 2 8 -1 10 -1 -1 9 -1 -1 3 4 -1 -1 5 -1 6 -1 7 -1 -1
*/
