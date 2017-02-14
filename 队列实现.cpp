#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<strinh.h>

#define OK 1
#define ERROR 0
#definde TRUE 1
#define FALSE 0
#define OVERFLOW 

typedef int Status;

typedef double QElemTpye;

typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
    QueuePtr front;//队头指针
    QueuePtr rear;//队尾指针
}LinkQueue;

//------------基本操作函数原型说明-----------
Status initQueue(LinkQueue &Q);
    //构造一个队列
Status destoryQueue(LinkQueue &Q);
Status clearQueue(LinkQUeue &Q);
Status isEmpty(LinkQueue Q);
Status QueueLength(LinkQueue Q);
Status getHead(LinkQueue Q);
Status enterQueue(LinkQueue &Q,QElemType e);
Status deleteQueue(LinkQueue &Q,QElemType &e);
Status traveseQueue(LinkQueue Q,visit());

//------------主函数--------------------------
int main(){
    //paste your code here
    return 0;
}

//------------基本操作的代码实现---------------

Status initQueue(LinkQueue &Q){
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(Queue));
    if(!Q.front) exit(OVERFLOW);
    Q.front->next=NULL;
    return OK;
}

Status destoryQueue(LinkQueue &Q){
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front=Q.rear;
    }//里面有个NULL
    return OK；
}

Status clearQueue(LinkQueue &Q){
    destoryQueue(Q);
    intiQUeue(Q);
    return 0;
}

Staus enterQueue(LinkQueue &Q,QElemType e){
    Q.rear->data=e;
    if(!(Q.rear->next=(QueuePtr)malloc(sizeof(QNode))))
        return OVERFLOW;
    Q.rear=Q.rear->next;
    Q.rear->next=NULL;
    return OK;
}