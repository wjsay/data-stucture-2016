//˳������ʽʵ�֣� ����ͷ��㣬���������ȣ� 

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
}Node,*LNode;//����С28Bytes 
//�ṹ������ı����ռ���ܻᶪ��malloc����Ĳ��� 

Status IntiList(LNode Head);
Status creatLNode(LNode Head);
Status clearLink(LNode Head); 
Status DestoryList(LNode Head); 
//Status

int main(){
	LNode Head;//ֻ��������һ��ָ�� 
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
//	//ע���ˣ�����pָ�����һ���ڵ�
//	p->next=tmp;
//	Head->num++;//�ڵ㳤�ȼ�һ 
//	return 0; 
//}

Status clearLink(LNode Head){
	LNode tmp,p=Head->next;//��ǰָ��p
	while(p->next){
		tmp=p;
		p=p->next;
		free(tmp);
	}
	free(p);
	return OK;
}
