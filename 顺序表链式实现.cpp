//顺序表的链式实现（ 带有头结点，保存链表长度） 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE
#define FALSE 0

typedef int Status;

typedef struct LinkNode{
        int num;
        char str[20];
        struct LinkNode* next;
}Node,*LNode;//结点大小28Bytes 
//结构体申请的变量空间可能会丢，malloc申请的不会 

Status IntiList(LNode Head);
Status creatLNode(LNode Head);
Status clearLink(LNode Head); 
Status DestoryList(LNode Head); 
//Status

int main(){
	LNode Head;//只是声明了一个指针 
	IntiList(Head);
//	for(int i=0;i<5;i++){
//		creatLNode(Head);
//	}
	printf("%d\n",Head->num);
	
	return 0;
}

Status IntiList(LNode Head){
	Head=(LNode)malloc(sizeof(Node));
	if(!Head) exit(OVERFLOW);
	Head->num=0;
	Head->str[0]='\0';
	Head->next=NULL;
	return OK;
}

//Status creatLNode(LNode Head){
//	LNode tmp=(LNode)malloc(sizeof(Node));
//	if(!tmp) exit(OVERFLOW);
//	tmp->next=NULL;
//	LNode p=Head;
//	while(p->next){
//		p=p->next;
//	}
//	//注意了，现在p指向最后一个节点
//	p->next=tmp;
//	Head->num++;//节点长度加一 
//	return 0; 
//}

Status clearLink(LNode Head){
	LNode tmp,p=Head->next;//当前指针p
	while(p->next){
		tmp=p;
		p=p->next;
		free(tmp);
	}
	free(p);
	return OK;
}
