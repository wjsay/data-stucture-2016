//==============图论===========
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

//------图的数组（邻接矩阵）存储表示--------
#define INFINITY INT_MAX//最大值无穷大0X7fffffff;顶义在头文件中 
#define MAX_VERTEX_NUM 20//最大顶点数
#define VRType int// VRType是顶点关系的类型。对无权图，用1或0
//表示是否相邻；对带权图，则为权值类型 
#define InfoType char
#define VertexType char
//#define GraphKind int
typedef enum { UDG, DG, UDN, DN }GraphKind;
//0,UDG;1,DG;2,UDN;3,DN;//看我来个枚举类型 
typedef struct ArcCell {
	VRType adj;
	InfoType *info;//该弧相关信息的指针 
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//还可以这样用……涨知识了 
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum, arcnum;//图的当前顶点数和弧数
	GraphKind kind;//图的种类标志 
}MGraph;

//----------邻接矩阵的基本操作原型-------------
Status CreateGraph(MGraph *G);//尽量先不用引用调用 
int    Locate(MGraph G, char v);
Status CreateUDG(MGraph *G);
Status UDGprint(MGraph G);
char   mygetchar();
//Status CreateDG(MGraph *G);
//Status CreateUDN(MGraph *G);
//Status CreateDN(MGraph *G);

//----------主函数-------------------------------------------------------
int main() {
	//paste your code here
	//freopen("d:\\coding\\data.in", "r", stdin);
	//	printf("%X\n",INT_MAX);
	//	printf("%d\n",sizeof(AdjMatrix));//3200,Dev下 
	MGraph G;
	CreateGraph(&G);
	if (G.kind == 0) UDGprint(G);

	while (1);
	return 0;
}


//-------------邻接矩阵基本操作实现--------------- 
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
	exit(OVERFLOW); //不允许出错 
}
Status CreateUDG(MGraph *G) {
	//采用数组（邻接矩阵）表示法，构造无向图G
	scanf("%d%d", &((*G).vexnum), &((*G).arcnum));
	int IncInfo = 0;
	//scanf("%d",&IncInfo);IncInfo为0则各弧不含其他信息
	int i = 0, j = 0, k = 0;
	for (i = 0; i<(*G).vexnum; ++i) (*G).vexs[i]=mygetchar(); //构造顶点向量
	for (i = 0; i<(*G).vexnum; ++i) {//初始化邻接矩阵 
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
			//保存信息的指针，暂时不用 
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
