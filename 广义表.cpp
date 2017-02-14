//=========�����============ 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define OVERFLOW -1
#define ERROR 0
typedef int Status;
typedef enum{
	//ö������Ĭ�ϴ�0��ʼ��Ҳ���Զ��壬���ŷֿ� 
	ATOM,
	LIST
}ElemTag; //ATOM==0:ԭ�ӣ�LIST==1:�ӱ�
//Ϊ�������ԭ�����Ͷ���Ϊ�ַ� 
#define AtomType char  

////---------������ͷβ�洢�����ʾ----------- 
//typedef struct GLNode{
//	ElemTag tag;//��־�򣬹������֣���������ԭ�ӽڵ�ͱ�ڵ�
//	union{
//		AtomType atom;//ԭ�ӵ�ֵ�� 
//		struct{
//			struct GLNode *hp,*tp;
//		}ptr;//��ڵ��ͷ����β��� 
//	}data; 
//}*GList,GLNode;//��������� 

//---------��������չ��������洢��ʾ-------------- 
typedef struct GLNode{
	ElemTag tag;//�������� 
	union{//ԭ�ӽڵ�ͱ�ڵ�����ϲ��� 
		AtomType atom;//ԭ�ӽڵ��ֵ�� 
		struct GLNode *hp;//��ڵ��ͷָ�� 
	}UNION;
	struct GLNode *tp;//�൱�����������next,ָ����һ��Ԫ�ؽڵ� 
}*GList,GLNode;

//-----------�����Ļ�������------------
	//��������չ���Դ洢��ʾ 

Status initGList(GList &L);
//S�ǹ�������д��ʽ��(�����֣����ţ�����С�������) 
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

//---------------������-----------------------
int main(int argc,char *argv[]){
	//paste your code here, Sir, please
	const char S[]="((),(e),(a,(b,c,d)))";

	GList L;
	initGList(L);
//	createGList(L,S);
	
	return 0;
} 

//����ָ��GList��ʼ�� 
Status initGList(GList &L){
	L=(GList)malloc(sizeof(GLNode));
	if(!L)exit(OVERFLOW);
	L->tag=LIST;//��ʼ��Ϊ��ڵ� 
	L->UNION.hp=NULL;
	L->tp=NULL;
	return OK;
}

Status createGList(GList &L,char S[]){
	
	
	return OK; 
} 



/*��������
		//A=();B=(e);C=(a,(b,c,d)); 
		const char S[]="((),(e),(a,(b,c,d)))";
*/ 
