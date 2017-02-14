//=======查找算法的实现============
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
int a[MAXN] = { 1,4,5,8,2,3,9,5,1,2,7,6 };//默认情况下
typedef struct BiTNode {
	ElemType data;
	struct BiTNode *lChild, *rChild;
}BiTNode,*BiTree;//定义二叉树
int hashsize[] = { 997 };//...
typedef struct {
	ElemType *elem;//数据元素存储基址，动态分配数组
	int count;//当前数据元素个数
	int sizeindex;//hashsize[sizeindex]为当前容量
}HashTable;//定义开放地址哈希表的存储结构

//----------函数声明------------------
int sequenceFind(int a[], int s, int t, int key);//在a[s..t]中查找关键字key
void qsort(int a[], int low, int high);//需要一个排序算法
int biSearch(int a[], int s, int t, int key);
void generateArray(int a[], int n);
void outputArray(int a[], int n);
Status SearchBST(BiTree T, KeyType key,BiTree f,BiTree &p);
	//若查找失败，返回查找路经过上的最后一个节点
Status InsertBST(BiTree &T, ElemType e);
Status DeleteBST(BiTree &T, KeyType key);
Status Delete(BiTree &p);
//----------传说中的哈希算法------------
int Hash(int K);
void collision(int &p, int c);
Status SearchHash(HashTable H, KeyType K, int &p, int &c);
void RecreateHashTable(HashTable H);
//--------------------------------主函数---------------------------------------------------------
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
//-------------------------------函数实现--------------------------------------------
int sequenceFind(int a[], int s, int t, int key) {
	for (int i = s; i <= t; ++i) {
		if (a[i] == key) return i;
	}
	return -1;
}//若查找成功，返回key所在位置；否则返回-1
void qsort(int a[], int low, int high) {
	if (low >= high) return;
	int i = low, j = high, key = a[low];
	while (i<j) {
		while (i<j&&a[j] >= key) --j;//之前忘了加等号，有时就死了
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
}//给数组a的前n个元素赋值
void outputArray(int a[], int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
}//输出数组a的前n个元素
Status SearchBST(BiTree T, KeyType key,BiTree f,BiTree &p) {
	//若查找成功，返回TRUE，p指向数据元素节点
	//否则，p指向查找路径上访问的最后一个节点
	if (!T) {p = f; return FALSE;}//没找到
	else if (EQ(key, T->data)) { p = T; return TRUE; }//查找成功
	else if (LT(key, T->data)) return SearchBST(T->lChild, key, T, p);//在左子树中查找
	else return (SearchBST(T->rChild,key,T,p));//在右子树中继续查找
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
	if (!p->rChild) {//右子树空则只需要重新接它的左子树
		BiTree q = p;
		p = p->lChild;
		free(q);
	}
	else if(!p->lChild){//左子树空则只需要重新接它的右子树
		BiTree q = p;
		p = p->rChild;
		free(q);
	}
	else {
		BiTree q = p,s=p->lChild;
		while (s->rChild) {
			q = s; s = s->rChild;//看样子q是s的前驱呀
		}//转左，然后向右到尽头,(就是去寻找p的前驱)
		p->data = s->data;//s指向被删除节点的前驱，p的数值域已被覆盖
		if (q != p) q->rChild = s->lChild;
		else q->lChild = s->lChild;//p的左孩子没有右孩子
		delete s;//C++中的，用于删除变量地址
	}
	return TRUE;
}
int Hash(int K) {
	return K % 13;
}//哈希函数
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
