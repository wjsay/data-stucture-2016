//=========广义表============ 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define OVERFLOW -1
#define ERROR 0
typedef int Status;
typedef enum{
	//枚举类型默认从0开始，也可自定义，逗号分开 
	ATOM,
	LIST
}ElemTag; //ATOM==0:原子，LIST==1:子表
//为简单起见，原子类型定义为字符 
#define AtomType char  

////---------广义表的头尾存储链表表示----------- 
//typedef struct GLNode{
//	ElemTag tag;//标志域，公共部分，用于区分原子节点和表节点
//	union{
//		AtomType atom;//原子的值域 
//		struct{
//			struct GLNode *hp,*tp;
//		}ptr;//表节点的头结点和尾结点 
//	}data; 
//}*GList,GLNode;//广义表类型 

//---------广义表的拓展线性链表存储表示-------------- 
typedef struct GLNode{
	ElemTag tag;//公共部分 
	union{//原子节点和表节点的联合部分 
		AtomType atom;//原子节点的值域 
		struct GLNode *hp;//表节点的头指针 
	}UNION;
	struct GLNode *tp;//相当于线性链表的next,指向下一个元素节点 
}*GList,GLNode;

//-----------广义表的基本操作------------
	//广义表的拓展线性存储表示 

Status initGList(GList &L);
//S是广义表的书写形式串(由数字，逗号，左右小括号组成) 
Status createGList(GList &L,char S[]);
Status destroyGList(GList &L);
Status copyGList(GList &T,GList L);
int GListLength(GList L);
Status GListDepth(GList L);
Status GListEmpty(GList L);
GList getHead(GList L);
GList getTail(GList L);
Status insertFirst_GL(GList &L,GLNode e);
Status deleteFirst_GL(GList &L,GLNode e);
Status traverse_GL(GList &L,Status (*visit)());

//---------------主函数-----------------------
int main(int argc,char *argv[]){
	//paste your code here, Sir, please
	const char S[]="((),(e),(a,(b,c,d)))";

	GList L;
	initGList(L);
//	createGList(L,S);
	
	return 0;
} 

//对于指针GList初始化 
Status initGList(GList &L){
	L=(GList)malloc(sizeof(GLNode));
	if(!L)exit(OVERFLOW);
	L->tag=LIST;//初始化为表节点 
	L->UNION.hp=NULL;
	L->tp=NULL;
	return OK;
}

Status createGList(GList &L,char S[]){
	
	
	return OK; 
} 



/*输入数据
		//A=();B=(e);C=(a,(b,c,d)); 
		const char S[]="((),(e),(a,(b,c,d)))";
*/ 
