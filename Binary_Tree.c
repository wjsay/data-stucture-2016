//=========������(Binary Tree)===========
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define TElemType int
#define Status int

//-----����������ʽ�洢---------------- 
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lChild,*rChild;
}BiTNode,*BiTree;

//----------���������ĺ���ԭ��˵��----------------- 
Status createBiTree(BiTree *T); 
Status inOrderTraverse(BiTree T,Status(*function_p)(TElemType data)){
	BiTree p=T;
	while(p!=NULL||)
}
 
int main(){
	//paste your code here
	BiTree T;
	createBiTree(&T);
	return 0;
} 

Status createBiTree(BiTree *T){
	TElemType data;
	scanf("%d",&data);
	if(data==-1) (*T)=NULL;//ÿ��Ҷ�ӽڵ���-1��ʾ���������� 
	else{
		if(!((*T)=(BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		(*T)->data=data;
		createBiTree(&((*T)->lChild));
		createBiTree(&((*T)->rChild));
	}
	
	return OK;
} 


