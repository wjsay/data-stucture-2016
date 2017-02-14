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

//------ͼ���ڽӱ�洢��ʾ--------
#define INFINITY INT_MAX//���ֵ�����0X7fffffff;������ͷ�ļ��� 
#define MAX_VERTEX_NUM 20//��󶥵���
#define InfoType char
#define VertexType int
typedef enum { UDG, DG, UDN, DN }GraphKind;
//0,UDG;1,DG;2,UDN;3,DN;//��������ö������ 
typedef struct ArcNode {
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *info;//�û���ص���Ϣָ��
}ArcNode;
typedef struct VNode {
	VertexType data;//������Ϣ
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALGraph;

//----------�ڽӾ���Ļ�������ԭ��-------------
void   InitilizationAL(ALGraph *AL);
Status CreateALGraph(ALGraph *AL);
Status CreateDG(ALGraph *AL);
Status printGraph(ALGraph AL);
Status InDegree(ALGraph AL,int indegree[]);
Status OutDegree(ALGraph AL, int outdegree[]);
Status DestroyGraph(ALGraph *AL);
void   BFSTraverse(ALGraph AL,Status (*Visit)(int )); 

//----------������-------------------------------------------------------
int main() {
	//paste your code here
	freopen("d:\\coding\\data.in", "r", stdin);
	ALGraph AL;
	InitilizationAL(&AL);//��ʼ�����ڴ���
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


//-------------�ڽӾ����������ʵ��--------------- 
void   InitilizationAL(ALGraph *AL) {
	(*AL).arcnum = 0;
	(*AL).kind = UDG;
	for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
		(*AL).vertices[i].data = i;//��ʼ�㣬ǡ�úͱ��λ�������
									//��ʵ�����ô洢��ȵģ�����
		(*AL).vertices[i].firstarc = NULL;
	}
	(*AL).vexnum = 0;
	(*AL).vertices->data = 0;
}
Status CreateALGraph(ALGraph *AL) {
	scanf("%d", &(*AL).kind);
	switch((*AL).kind) {
		//����������ͼ�ٸ�����
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
		p->adjvex = end;//�û���ָ�Ķ���λ��
		p->nextarc = (*AL).vertices[start].firstarc;
		p->info = NULL;//��Ϣ��
		((*AL).vertices[start]).firstarc = p;//β�巨��������Ӧ�úܰ�ȫ
		//������Ϣ��֮ǰ��д�˸�.nextarc�����·��ʴ���
	}
	return OK;
}
Status printGraph(ALGraph AL) {
	//Ϊ�˷���鿴�����Ȱ��ڽӱ�ת��Ϊ�ڽӾ��������
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
	for (int i = 0; i < AL.vexnum; ++i) {//����i
		for (int j = 0; j < AL.vexnum; ++j) {
			ArcNode *p = AL.vertices[j].firstarc;
			while (p != NULL) {
				if (p->adjvex == i) {
					outdegree[i]++;//��ÿһ��������ȶ�Ҫ���������ڽӱ�
									//������ʹ�ó��ȣ����Խ���ʮ���ڽӱ�
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
			free(pre);//����ͷ��ڴ�
		}
	}
	(*AL).kind = DG;
	(*AL).arcnum = 0;
	(*AL).vexnum = 0;
	return OK;
}
/*
���룺
//��һ�д���ͼ�����ͣ��ڶ�����������n,m,n��ʾ���������m��ʾ�ж�������
//����m���У�ÿ������������ʾ����֮���й�ϵ������ͼ��
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
