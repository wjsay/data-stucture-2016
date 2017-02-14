//==========HaffmanTree & HaffmanCode===============
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Status int
#define OK 1
#define ERROR 0
#define BOOLEAN int
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define MAXSIZE 200
#define MAX_WEIGHT 0X7f7f7f7f
#define N 26
static int n = N;

//---------HaffmanTree & HaffmanCode 的存储表示--------
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;//动态分配数组存储HuffmanTree
typedef char * *HuffmanCode;//动态分配数组存储HuffmanCode Table
							//----------HuffmanTree操作的函数声明-----------
void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n);
void Select(HuffmanTree HT, int i, int *s1, int *s2);
HTNode HTNodeAssignment(int w, int parent, int lchild, int rchild);
int getWight(int n, int w[]);

//===================主函数===============================
int main() {
	//paste your code here
	HuffmanTree HT = NULL;
	HuffmanCode HC = NULL;
	int w[N] = { 5,29,7,8,14,23,3,11 };//w数组存放各个字符的权值
	
	getWight(n, w);//printf("%d\n", n);//也可能是一牵涉到文件读写就要出错
	
	HuffmanCoding(&HT, &HC, w, n);
	for (int i = 1; i <= n; i++) {
		printf("%s\n", HC[i]);
	}

	return 0;
}

//--------HuffmanTree操作的函数实现----------------------
HTNode HTNodeAssignment(int w, int parent, int lchild, int rchild) {
	HTNode tmp;
	tmp.weight = w;
	tmp.parent = parent;
	tmp.lchild = lchild;
	tmp.rchild = rchild;
	return tmp;
}
void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n) {
	//w存放n个字符的权值（均>0），构造HuffmanTree HT,并求出n个HuffmanCode HC
	if (n <= 1) return;
	int m = 2 * n - 1;
	*HT = NULL;
	*HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0号单元未用
	if (*HT == NULL) exit(OVERFLOW);
	//HuffmanTree p=(*HT);
	int i;// printf("%d\n", n);//VS编译器有毒呀，n值理论上是不会变的呀
	for (i = 1; i <= n; ++i, ++w) {
		//*p=HTNodeAssignment(*w,0,0,0);
		(*HT)[i] = HTNodeAssignment(*w, 0, 0, 0);
	}
	for (; i <= m; ++i) {
		(*HT)[i] = HTNodeAssignment(0, 0, 0, 0);
	}
	for (i = n + 1; i <= m; i++) {//建立HuffmanTree
								  //在HT[1..i)选择parent为0且weigh最小的两个节点，其序号分别为s1,s2(small)
		int s1, s2;
		Select(*HT, i, &s1, &s2);//1.。i不包括i，即左闭右开
								 //printf("%d:  %d    %d\n",i,s1,s2);//观察函数选择是否有问题
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	//for(int i=1;i<=m;++i)printf("%d\t%d\t%d\n",i,(*HT)[i].parent,(*HT)[i].weight);//debug
	//---从叶子到根逆求每个字符的HuffmanCode
	(*HC) = (HuffmanCode)malloc((n + 1) * sizeof(char));//分配n个字符编码的头指针向量
	char *cd;
	cd = (char*)malloc(n * sizeof(char));//求分配编码的工作空间
	cd[n - 1] = '\0';//编码结束符，最长编码长度n-1
	for (i = 1; i <= n; ++i) {//逐个字符求HuffmanCode
		int start = n - 1;
		for (int c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent) {//从叶子到根逆向求编码
			if ((*HT)[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));//为第i个字符编码分配空间
		printf("%d\t%d\t%s\n", i, n - start, cd + start);
		strcpy((*HC)[i], cd + start);//从cd复制编码（串）到HC
		//for(int cnt=0;start<=n-1;++start) (*HC)[i][cnt++]=cd[start];
		//除了(*HC)[1]复制不正常，其他都正常
	}
	//printf("%s\n",(*HC)[1]);
	//free(cd); cd = NULL;//一释放就要出事
}
void Select(HuffmanTree HT, int i, int *s1, int *s2) {//[0,i)
	int min1 = MAX_WEIGHT, min2 = MAX_WEIGHT;
	BOOLEAN flag = FALSE;
	for (int j = 1; j<i; ++j) {
		if (HT[j].parent == 0 && HT[j].weight<min2) {
			if (HT[j].weight<min1) {
				if (flag == FALSE)flag = TRUE;//这个标志还是不能删去的
				else { min2 = min1; *s2 = *s1; }
				min1 = HT[j].weight;
				*s1 = j;
			}
			else {
				min2 = HT[j].weight;
				*s2 = j;
			}
		}
	}
}//s1<s2
int getWight(int n, int w[]) {
	int record = 0;
	memset(w, 0, sizeof(w));
	char ch = '\0', *filepath = "sourcedata.txt";
	FILE *fp;
	if (!(fp = fopen(filepath, "rt"))) exit(ERROR);
	memset(w, 0, sizeof(w));
	while ((ch = getc(fp)) && ch != -1) {
		++w[ch - 'a'];
		++record;
	}
	fclose(fp);
	return record;
}
//一个变量进入函数内部后，没有用指针，结果值还是变了，我可以骂人吗
//后来定义了全局的静态变量

