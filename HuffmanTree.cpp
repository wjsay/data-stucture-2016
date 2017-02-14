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

//---------HaffmanTree & HaffmanCode �Ĵ洢��ʾ--------
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;//��̬��������洢HuffmanTree
typedef char * *HuffmanCode;//��̬��������洢HuffmanCode Table
							//----------HuffmanTree�����ĺ�������-----------
void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n);
void Select(HuffmanTree HT, int i, int *s1, int *s2);
HTNode HTNodeAssignment(int w, int parent, int lchild, int rchild);
int getWight(int n, int w[]);

//===================������===============================
int main() {
	//paste your code here
	HuffmanTree HT = NULL;
	HuffmanCode HC = NULL;
	int w[N] = { 5,29,7,8,14,23,3,11 };//w�����Ÿ����ַ���Ȩֵ
	
	getWight(n, w);//printf("%d\n", n);//Ҳ������һǣ�浽�ļ���д��Ҫ����
	
	HuffmanCoding(&HT, &HC, w, n);
	for (int i = 1; i <= n; i++) {
		printf("%s\n", HC[i]);
	}

	return 0;
}

//--------HuffmanTree�����ĺ���ʵ��----------------------
HTNode HTNodeAssignment(int w, int parent, int lchild, int rchild) {
	HTNode tmp;
	tmp.weight = w;
	tmp.parent = parent;
	tmp.lchild = lchild;
	tmp.rchild = rchild;
	return tmp;
}
void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n) {
	//w���n���ַ���Ȩֵ����>0��������HuffmanTree HT,�����n��HuffmanCode HC
	if (n <= 1) return;
	int m = 2 * n - 1;
	*HT = NULL;
	*HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0�ŵ�Ԫδ��
	if (*HT == NULL) exit(OVERFLOW);
	//HuffmanTree p=(*HT);
	int i;// printf("%d\n", n);//VS�������ж�ѽ��nֵ�������ǲ�����ѽ
	for (i = 1; i <= n; ++i, ++w) {
		//*p=HTNodeAssignment(*w,0,0,0);
		(*HT)[i] = HTNodeAssignment(*w, 0, 0, 0);
	}
	for (; i <= m; ++i) {
		(*HT)[i] = HTNodeAssignment(0, 0, 0, 0);
	}
	for (i = n + 1; i <= m; i++) {//����HuffmanTree
								  //��HT[1..i)ѡ��parentΪ0��weigh��С�������ڵ㣬����ŷֱ�Ϊs1,s2(small)
		int s1, s2;
		Select(*HT, i, &s1, &s2);//1.��i������i��������ҿ�
								 //printf("%d:  %d    %d\n",i,s1,s2);//�۲캯��ѡ���Ƿ�������
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	//for(int i=1;i<=m;++i)printf("%d\t%d\t%d\n",i,(*HT)[i].parent,(*HT)[i].weight);//debug
	//---��Ҷ�ӵ�������ÿ���ַ���HuffmanCode
	(*HC) = (HuffmanCode)malloc((n + 1) * sizeof(char));//����n���ַ������ͷָ������
	char *cd;
	cd = (char*)malloc(n * sizeof(char));//��������Ĺ����ռ�
	cd[n - 1] = '\0';//���������������볤��n-1
	for (i = 1; i <= n; ++i) {//����ַ���HuffmanCode
		int start = n - 1;
		for (int c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent) {//��Ҷ�ӵ������������
			if ((*HT)[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));//Ϊ��i���ַ��������ռ�
		printf("%d\t%d\t%s\n", i, n - start, cd + start);
		strcpy((*HC)[i], cd + start);//��cd���Ʊ��루������HC
		//for(int cnt=0;start<=n-1;++start) (*HC)[i][cnt++]=cd[start];
		//����(*HC)[1]���Ʋ�����������������
	}
	//printf("%s\n",(*HC)[1]);
	//free(cd); cd = NULL;//һ�ͷž�Ҫ����
}
void Select(HuffmanTree HT, int i, int *s1, int *s2) {//[0,i)
	int min1 = MAX_WEIGHT, min2 = MAX_WEIGHT;
	BOOLEAN flag = FALSE;
	for (int j = 1; j<i; ++j) {
		if (HT[j].parent == 0 && HT[j].weight<min2) {
			if (HT[j].weight<min1) {
				if (flag == FALSE)flag = TRUE;//�����־���ǲ���ɾȥ��
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
//һ���������뺯���ڲ���û����ָ�룬���ֵ���Ǳ��ˣ��ҿ���������
//����������ȫ�ֵľ�̬����

