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

//------图的邻接表存储表示--------
#define INFINITY INT_MAX//最大值无穷大0X7fffffff;顶义在头文件中 
#define MAX_VERTEX_NUM 20//最大顶点数
#define InfoType char
#define VertexType int
typedef enum { UDG, DG, UDN, DN }GraphKind;
//0,UDG;1,DG;2,UDN;3,DN;//看我来个枚举类型 
typedef struct ArcNode {
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *info;//该弧相关的信息指针
}ArcNode;
typedef struct VNode {
	VertexType data;//顶点信息
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALGraph;

//----------邻接矩阵的基本操作原型-------------
void   InitilizationAL(ALGraph *AL);
Status CreateALGraph(ALGraph *AL);
Status CreateDG(ALGraph *AL);
Status printGraph(ALGraph AL);
Status InDegree(ALGraph AL,int indegree[]);
Status OutDegree(ALGraph AL, int outdegree[]);
Status DestroyGraph(ALGraph *AL);
void   BFSTraverse(ALGraph AL,Status (*Visit)(int )); 

//----------主函数-------------------------------------------------------
int main() {
	//paste your code here
	freopen("d:\\coding\\data.in", "r", stdin);
	ALGraph AL;
	InitilizationAL(&AL);//初始化先于创建
	//printf("%d\n", sizeof(AdjList));//320=(12+4)*MAX_VERTEX_NUM
	CreateALGraph(&AL);
	int indegree[MAX_VERTEX_NUM] = { 0 }, outdegree[MAX_VERTEX_NUM] = { 0 };
	printGraph(AL);
	InDegree(AL, indegree);
	OutDegree(AL, outdegree);
	printf("\n");
	for (int i = 0; i < AL.vexnum; ++i) {
		printf("%d\t%d\n", indegree[i],outdegree[i]);
	}
	DestroyGraph(&AL);

	while (1);
	return 0;
}


//-------------邻接矩阵基本操作实现--------------- 
void   InitilizationAL(ALGraph *AL) {
	(*AL).arcnum = 0;
	(*AL).kind = UDG;
	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		(*AL).vertices[i].data = i;//起始点，恰好和表的位置相等了
									//其实可以用存储入度的，算了
		(*AL).vertices[i].firstarc = NULL;
	}
	(*AL).vexnum = 0;
	(*AL).vertices->data = 0;
}
Status CreateALGraph(ALGraph *AL) {
	scanf("%d", &(*AL).kind);
	switch((*AL).kind) {
		//我先用有向图举个例子
		case DG: return CreateDG(AL);
		//case UDG: return CreateDG(AL);
		default: (*AL).vertices->firstarc = NULL; return ERROR;
	}
}
Status CreateDG(ALGraph *AL) {
	scanf("%d%d", &(*AL).vexnum, &(*AL).arcnum);
	ArcNode *p = NULL;
	for (int i = 0; i < (*AL).arcnum; ++i) {
		int start, end;
		scanf("%d%d", &start, &end);
		if(!(p =(ArcNode *)malloc(sizeof(ArcNode)))) exit(OVERFLOW);
		p->adjvex = end;//该弧所指的顶点位置
		p->nextarc = (*AL).vertices[start].firstarc;
		p->info = NULL;//信息域
		((*AL).vertices[start]).firstarc = p;//尾插法建立链表，应该很安全
		//调试信息，之前多写了个.nextarc，导致访问错误
	}
	return OK;
}
Status printGraph(ALGraph AL) {
	//为了方便查看，我先把邻接表转化为邻接矩阵，再输出
	int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	memset(matrix, 0, sizeof(matrix));
	for (int i = 0; i < AL.vexnum; ++i) {
		ArcNode *p=AL.vertices[i].firstarc;
		while (p!=NULL) {
			matrix[i][p->adjvex] = 1;
			p = p->nextarc;
		}
	}
	for (int i = 0; i < AL.vexnum; ++i) {
		for (int j = 0; j < AL.vexnum; ++j) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
	return OK;
}
Status InDegree(ALGraph AL, int indegree[]) {
	for (int i = 0; i < AL.vexnum; ++i) {
		ArcNode *p = AL.vertices[i].firstarc;
		indegree[i] = 0;
		while (p != NULL) {
			indegree[i]++;
			p = p->nextarc;
		}
	}
	return OK;
}
Status OutDegree(ALGraph AL, int outdegree[]) {
	for (int i = 0; i < AL.vexnum; ++i) {//出度i
		for (int j = 0; j < AL.vexnum; ++j) {
			ArcNode *p = AL.vertices[j].firstarc;
			while (p != NULL) {
				if (p->adjvex == i) {
					outdegree[i]++;//求每一个顶点出度都要遍历整个邻接表。
									//若经常使用出度，可以建立十字邻接表
				}
				p = p->nextarc;
			}
		}
	}
	return OK;
}
Status DestroyGraph(ALGraph *AL) {
	for (int i = 0; i < (*AL).vexnum; i++) {
		ArcNode *pre=NULL, *p = (*AL).vertices[i].firstarc;
		while (p != NULL) {
			pre = p;
			p = p->nextarc;
			free(pre);//逐个释放内存
		}
	}
	(*AL).kind = DG;
	(*AL).arcnum = 0;
	(*AL).vexnum = 0;
	return OK;
}
/*
输入：
//第一行代表图的类型，第二行有两个数n,m,n表示顶点个数，m表示有多少条弧
//下面m行中，每行两个数，表示两点之间有关系（有向图）
1
9 9
1 2
1 3
2 4
2 5
4 8
5 8
3 6
3 7
6 7

*/
