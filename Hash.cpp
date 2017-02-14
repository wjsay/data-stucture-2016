//=======�����㷨��ʵ��============
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MAXN 1000000
#define MOD 1000
#define ElemType int
#define KeyType int
#define Status int
#define EQ(a,b) (a)==(b)
#define LT(a,b) (a)<(b)
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define SUCCESS 1
#define UNSUCCESS 0
#define DULLICATE -1
#define NULLKEY -100
int a[MAXN] = { 1,4,5,8,2,3,9,5,1,2,7,6 };//Ĭ�������
typedef struct BiTNode {
	ElemType data;
	struct BiTNode *lChild, *rChild;
}BiTNode,*BiTree;//���������
int hashsize[] = { 997 };//...
typedef struct {
	ElemType *elem;//����Ԫ�ش洢��ַ����̬��������
	int count;//��ǰ����Ԫ�ظ���
	int sizeindex;//hashsize[sizeindex]Ϊ��ǰ����
}HashTable;//���忪�ŵ�ַ��ϣ��Ĵ洢�ṹ

//----------��������------------------
int sequenceFind(int a[], int s, int t, int key);//��a[s..t]�в��ҹؼ���key
void qsort(int a[], int low, int high);//��Ҫһ�������㷨
int biSearch(int a[], int s, int t, int key);
void generateArray(int a[], int n);
void outputArray(int a[], int n);
Status SearchBST(BiTree T, KeyType key,BiTree f,BiTree &p);
	//������ʧ�ܣ����ز���·�����ϵ����һ���ڵ�
Status InsertBST(BiTree &T, ElemType e);
Status DeleteBST(BiTree &T, KeyType key);
Status Delete(BiTree &p);
//----------��˵�еĹ�ϣ�㷨------------
int Hash(int K);
void collision(int &p, int c);
Status SearchHash(HashTable H, KeyType K, int &p, int &c);
void RecreateHashTable(HashTable H);
//--------------------------------������---------------------------------------------------------
int main() {
	//paste your code here
	int result;
	int len = 30;
	generateArray(a, len);
	int key = a[len / 2];
	outputArray(a, len);
	BiTree T=NULL,p=NULL;
	for (int i = 0; i < len; ++i) InsertBST(T, a[i]);
	result = sequenceFind(a, 0, len - 1, key); printf("%d\n", result);
	qsort(a, 0, len - 1);
	outputArray(a, len);
	result = biSearch(a, 0, len - 1, key);printf("%d\n", result);
	InsertBST(T, key); 
	DeleteBST(T, key);
	if (SearchBST(T, key, NULL, p)) printf("%d\t%d\n", key, p->data);

	while (1);
	return 0;
}
//-------------------------------����ʵ��--------------------------------------------
int sequenceFind(int a[], int s, int t, int key) {
	for (int i = s; i <= t; ++i) {
		if (a[i] == key) return i;
	}
	return -1;
}//�����ҳɹ�������key����λ�ã����򷵻�-1
void qsort(int a[], int low, int high) {
	if (low >= high) return;
	int i = low, j = high, key = a[low];
	while (i<j) {
		while (i<j&&a[j] >= key) --j;//֮ǰ���˼ӵȺţ���ʱ������
		a[i] = a[j];
		while (i<j&&a[i] <= key) ++i;
		a[j] = a[i];
	}
	a[i] = key;
	qsort(a, low, i - 1);
	qsort(a, i + 1, high);
}
int biSearch(int a[], int s, int t, int key) {
	while (s <= t) {
		int mid = (s + t) / 2;
		if (a[mid] == key) return mid;
		else {
			if (key<a[mid]) t = mid - 1;
			else s = mid + 1;
		}
	}
	return -1;
}
void generateArray(int a[], int n) {
	srand(time(NULL));
	for (int i = 0; i < n; ++i) {
		a[i] = rand() % MOD;
	}
}//������a��ǰn��Ԫ�ظ�ֵ
void outputArray(int a[], int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
}//�������a��ǰn��Ԫ��
Status SearchBST(BiTree T, KeyType key,BiTree f,BiTree &p) {
	//�����ҳɹ�������TRUE��pָ������Ԫ�ؽڵ�
	//����pָ�����·���Ϸ��ʵ����һ���ڵ�
	if (!T) {p = f; return FALSE;}//û�ҵ�
	else if (EQ(key, T->data)) { p = T; return TRUE; }//���ҳɹ�
	else if (LT(key, T->data)) return SearchBST(T->lChild, key, T, p);//���������в���
	else return (SearchBST(T->rChild,key,T,p));//���������м�������
}
Status InsertBST(BiTree &T, ElemType e) {
	BiTree p = NULL;
	if (!SearchBST(T, e, NULL, p)) {
		BiTree s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lChild = s->rChild = NULL;
		if (!p) T = s;
		else if (LT(e, p->data))p->lChild = s;
		else p->rChild = s;
		return TRUE;
	}
	else return FALSE;
}
Status DeleteBST(BiTree &T, KeyType key) {
	if (!T) return FALSE;
	else {
		if (EQ(key, T->data)) { return Delete(T); }
		else if (LT(key, T->data)) return DeleteBST(T->lChild, key);
		else return DeleteBST(T->rChild, key);
	}
}
Status Delete(BiTree &p) {
	if (!p->rChild) {//����������ֻ��Ҫ���½�����������
		BiTree q = p;
		p = p->lChild;
		free(q);
	}
	else if(!p->lChild){//����������ֻ��Ҫ���½�����������
		BiTree q = p;
		p = p->rChild;
		free(q);
	}
	else {
		BiTree q = p,s=p->lChild;
		while (s->rChild) {
			q = s; s = s->rChild;//������q��s��ǰ��ѽ
		}//ת��Ȼ�����ҵ���ͷ,(����ȥѰ��p��ǰ��)
		p->data = s->data;//sָ��ɾ���ڵ��ǰ����p����ֵ���ѱ�����
		if (q != p) q->rChild = s->lChild;
		else q->lChild = s->lChild;//p������û���Һ���
		delete s;//C++�еģ�����ɾ��������ַ
	}
	return TRUE;
}
int Hash(int K) {
	return K % 13;
}//��ϣ����
void collision(int &p, int c) {
	p++;
}
Status SearchHash(HashTable H, KeyType K, int &p, int &c) {
	p = Hash(K);
	while (H.elem[p] != NULLKEY && !EQ(K, H.elem[p]))
		collision(p, ++c);
	if (EQ(K, H.elem[p])) return SUCCESS;
	else return UNSUCCESS;
}
void RecreateHashTable(HashTable H) {
	return;
}
Status InsertHash(HashTable &H, ElemType e) {
	int c = 0,p=0;
	if (SearchHash(H, e, p, c)) return DULLICATE;
	else if (c < hashsize[H.sizeindex] / 2) {
		H.elem[p] = e;
		++H.count;
		return OK;
	}
	else {
		RecreateHashTable(H);
		return UNSUCCESS;
	}
}
