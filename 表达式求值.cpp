#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
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
#define MAX 10000
const char *optrs = "+-*/()#";


typedef union SElemType {
	double num;
	char ch;
}SElemType;
typedef struct {
	SElemType *base;
	int top;//��ν��topָ�룬Ҳֻ��һ���α���� 
	int stacksize;//��ǰջ����Ŀռ䣬��Ԫ��Ϊ��Ԫ
}SqStack;//˳��ջ 

		 //-----------ջ���������ĺ���ԭ�ͼ�Ҫ˵��--------------
void initStack(SqStack &S);
void destroyStack(SqStack &S);
void cleatStack(SqStack &S);
bool isEmpty(SqStack S);
int  size(SqStack S);
SElemType top(SqStack S);
SElemType pop(SqStack &S);
void push(SqStack &S, SElemType e);
Status StackTraverse(SqStack &S, Status(*visit)(SElemType e));
//��Ҫ�������������޸�topָ�� 

int precede(SElemType e, char c) {
	int pre_optr[7][7] = {
		1,	1,	-1,	-1,	-1,	1,	1,
		1,	1,	-1,	-1,	-1,	1,	1,
		1,	1,	 1,	 1,	-1,	1,	1,
		1,	1,	 1,	 1,	-1,	1,	1,
		-1,	-1,	-1,	-1,	-1,	0,	-2,
		1,	1,	1,	1,	-2,	1,	1,
		-1,	-1,	-1,	-1,	-1,	-2,	0
	};

	return pre_optr[strchr(optrs, e.ch) - optrs][strchr(optrs, c) - optrs];
}

SElemType calculator(double num1, char opt, double num2) {
	double ret; SElemType e;
	switch (opt) {
	case '+': ret = num1 + num2; break;
	case '-': ret = num1 - num2; break;
	case '*': ret = num1*num2; break;
	case '/': ret = num1 / num2; break;
	}
	e.num = ret;
	return e;
}

SElemType EvaluateExpression() {
	//�������ʽ��ֵ����������㷨����optr��opnd�ֱ�Ϊ�����ջ��������ջ��
	//optrΪ��������ϡ�
	SqStack optr;
	SqStack opnd;
	SElemType e;
	e.ch = '#';
	initStack(optr); push(optr, e);
	initStack(opnd);
	char in[20];
	scanf("%s", in);
	while (*in != '#'&&*in != '=' && *in != '\n' || top(optr).ch != '#') {
		if (!strchr(optrs, *in)) {
			e.num = atof(in);
			push(opnd, e);
			scanf("%s", in);
		}
		else {
			switch (precede(top(optr), *in)) {
			case -1://ջ��Ԫ�ص����ȼ���
				e.ch = *in;
				push(optr, e);
				scanf("%s", in);
				break;
			case 0://�����Ų�������һ���ַ�
				pop(optr);
				scanf("%s", in);
				break;
			case 1://��ջ������������ջ
				push(opnd, calculator(pop(opnd).num, pop(optr).ch, pop(opnd).num));
				break;
			case -2:
			default:
				printf("\n�﷨����\n");
				exit(ERROR);
			}
		}
	}
	e = top(opnd);
	destroyStack(optr);
	destroyStack(opnd);
	return e;
}

//������ 
int main(int argc, char *argv[]) {
	//paste your code here
	freopen("D:\\coding\\data.in","r",stdin);
	SElemType e = EvaluateExpression();
	printf("\n%.2lf\n", e.num);

	return 0;
}


//----------����������ʵ��----------- 

void initStack(SqStack &S) {
	//topָ��ָ����һ���ڵ�
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
		printf("\n�ܾ�top����\n");
		exit(ERROR);
	}

}

SElemType pop(SqStack &S) {
	if (S.top) {
		SElemType e = S.base[S.top - 1];
		S.top--;
		return e;
	}
	else {
		printf("\n�ܾ�pop\n");
		exit(ERROR);
	}

}

void push(SqStack &S, SElemType e) {
	if (S.top >= S.stacksize) {
		//�����ϲ������ 
		S.base = (SElemType *)malloc((S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) {
			printf("\n����ռ�ʧ��\n");
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
	//��������ܶ�ջ�ڵ�ÿһ��Ԫ�ض�����visit,�ƻ���ջ�Ĺ���
	for (int i = 0; i<S.top; i++) {
		if (visit(S.base[i]) == 0) return ERROR;
	}
	return OK;
}
