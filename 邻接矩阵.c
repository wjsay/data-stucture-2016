//==============ͼ��===========
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define TRUE 1
#define FALSE 0

//------ͼ�����飨�ڽӾ��󣩴洢��ʾ--------
#define INFINITY INT_MAX//���ֵ�����0X7fffffff;������ͷ�ļ��� 
#define MAX_VERTEX_NUM 20//��󶥵���
#define VRType int// VRType�Ƕ����ϵ�����͡�����Ȩͼ����1��0
//��ʾ�Ƿ����ڣ��Դ�Ȩͼ����ΪȨֵ���� 
#define InfoType char
#define VertexType char
//#define GraphKind int
typedef enum { UDG, DG, UDN, DN }GraphKind;
//0,UDG;1,DG;2,UDN;3,DN;//��������ö������ 
typedef struct ArcCell {
	VRType adj;
	InfoType *info;//�û������Ϣ��ָ�� 
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�����������á�����֪ʶ�� 
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];//��������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;//ͼ�������־ 
}MGraph;

//----------�ڽӾ���Ļ�������ԭ��-------------
Status CreateGraph(MGraph *G);//�����Ȳ������õ��� 
int    Locate(MGraph G, char v);
Status CreateUDG(MGraph *G);
Status UDGprint(MGraph G);
char   mygetchar();
//Status CreateDG(MGraph *G);
//Status CreateUDN(MGraph *G);
//Status CreateDN(MGraph *G);

//----------������-------------------------------------------------------
int main() {
	//paste your code here
	//freopen("d:\\coding\\data.in", "r", stdin);
	//	printf("%X\n",INT_MAX);
	//	printf("%d\n",sizeof(AdjMatrix));//3200,Dev�� 
	MGraph G;
	CreateGraph(&G);
	if (G.kind == 0) UDGprint(G);

	while (1);
	return 0;
}


//-------------�ڽӾ����������ʵ��--------------- 
Status CreateGraph(MGraph *G) {
	scanf("%d", &((*G).kind));
	//	printf("%d\n",(*G).kind);//have a try //OK, no problem
	switch ((*G).kind) {
	case UDG: return CreateUDG(G);
		//		case DG: return CreateDG(G);
		//		case UDN: return CreateUDN(G);
		//		case DN: return CreateDN(G);
	default: return ERROR;
	}
}
int    Locate(MGraph G, char v) {
	int i = 0;
	for (; i<G.vexnum; ++i) {
		if (G.vexs[i] == v)
			return i;
	}
	exit(OVERFLOW); //��������� 
}
Status CreateUDG(MGraph *G) {
	//�������飨�ڽӾ��󣩱�ʾ������������ͼG
	scanf("%d%d", &((*G).vexnum), &((*G).arcnum));
	int IncInfo = 0;
	//scanf("%d",&IncInfo);IncInfoΪ0���������������Ϣ
	int i = 0, j = 0, k = 0;
	for (i = 0; i<(*G).vexnum; ++i) (*G).vexs[i]=mygetchar(); //���춥������
	for (i = 0; i<(*G).vexnum; ++i) {//��ʼ���ڽӾ��� 
		for (j = 0; j<(*G).vexnum; ++j) {
			(*G).arcs[i][j].adj = INFINITY;
			(*G).arcs[i][j].info = NULL;
		}
	}
	char v1, v2;
	int w;
	for (k = 0; k<(*G).arcnum; ++k) {
		v1 = mygetchar();
		v2 = mygetchar();
		scanf("%d", &w);
		i = Locate(*G, v1);
		j = Locate(*G, v2);
		(*G).arcs[i][j].adj = w;
		if (IncInfo != 0) {
			(*G).arcs[i][j].info = NULL;
			//������Ϣ��ָ�룬��ʱ���� 
		}
	}

	return OK;
}
Status UDGprint(MGraph G) {
	int i = 0, j = 0;
	for (; i<G.vexnum; ++i) {
		for (j = 0; j<G.vexnum; ++j) {
			printf("( %c , %c ) = %-12d", G.vexs[i], G.vexs[j], G.arcs[i][j].adj);
		}
		printf("\n");
	}

	return OK;
}
char   mygetchar() {
	char ch;
	do {
		ch = getchar();
	} while (ch == ' ' || ch == '\n' || ch == '\t');
	return ch;
}

/*
0
4 12
abcd
aa 1 ab 1 ac 1 ad 1
ba 1 bb 1 bc 1 bd 1
ca 1 cb 1
da 1 db 1

*/
