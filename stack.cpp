#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define Status int
#define bool int 

typedef union SElemType {
	double num;
	char ch;
}SElemType;
typedef struct {
	SElemType *base;
	int top;//所谓的top指针，也只是一个游标吧了 
	int stacksize;//当前栈分配的空间，以元素为单元
}SqStack;

//-----------栈基本操作的函数原型简要说明--------------
void initStack(SqStack &S);
void destroyStack(SqStack &S);
void cleatStack(SqStack &S);
bool isEmpty(SqStack S);
int  size(SqStack S);
SElemType top(SqStack S);
void pop(SqStack &S);
void push(SqStack &S, SElemType e);
Status StackTraverse(SqStack &S, Status(*visit)(SElemType e));
//不要在其他程序中修改top指针 

//主函数 
int main(int argc, char *argv[]) {
	//paste your code here
	SqStack S;
	SElemType elem,tmp;
	initStack(S);

	return 0;
}


//----------基本操作的实现----------- 

void initStack(SqStack &S) {
	//top指针指向下一个节点
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	S.top = 0;
	if (!S.base) exit(OVERFLOW);
	S.stacksize = STACK_INIT_SIZE;
}

void cleatStack(SqStack &S) {
	free(S.base);
	initStack(S);
}

void destroyStack(SqStack &S) {
	free(S.base);
	S.base = NULL;
	S.top = 0;
	S.stacksize = 0;
}

bool isEmpty(SqStack S) {
	if (S.top) return FALSE;
	return TRUE;
}

int    size(SqStack S) {
	return S.top;
}

SElemType top(SqStack S) {
	if (S.top)  return S.base[S.top - 1];
	else {
		printf("\n拒绝top访问\n");
		exit(ERROR);
	}

}

void pop(SqStack &S) {
	if (S.top)S.top--;
	else {
		printf("\n拒绝pop\n");
		exit(ERROR);
	}

}

void push(SqStack &S, SElemType e) {
	if (S.top >= S.stacksize) {
		//理论上不会大于 
		S.base = (SElemType *)malloc((S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) {
			printf("\n申请空间失败\n");
			exit(OVERFLOW);
		}
		S.stacksize += STACKINCREMENT;
	}
	S.base[S.top++] = e;
}

Status function(SElemType e) {
	//paste your code here
	return OK;
}

Status StackTraverse(SqStack &S, Status(*visit)(SElemType e)) {
	//这个函数能对栈内的每一个元素都调用visit,破坏了栈的规则
	for (int i = 0; i<S.top; i++) {
		if (visit(S.base[i]) == 0) return ERROR;
	}
	return OK;
}
