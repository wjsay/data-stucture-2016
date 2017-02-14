//广义表——头尾链表存储表示法实现 
#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX 10000//字符串最大长度 
typedef int Status;

//-----广义表的头尾链表存储表示----- 
typedef enum { ATOM = 0, LIST }ElemTag;//ATOM=0:原子；LIST=1:子表 
typedef char AtomType;
typedef struct GLNode {
	ElemTag tag;			//公共部分，用于原子节点和表节点
	union {
		AtomType atom;		//atom是原子的值域
		struct { struct GLNode *hp, *tp; }ptr;
		//ptr是表节点的指针域，ptr.hp和ptr.tp分别指向表头和表尾 
	}Union;
}**GList_p, *GList, GLNode;

//---广义表的函数声明-------------
Status sever(char str[], char hstr[]);
Status CreateGList(GList &L, char S[]);
Status SubString(char sub[], char S[], int start, int len);
int GListDepth(GList L);
Status CopyGList(GList *T, GList L);

//-----------------主函数------------------------------------------------------------------------------ 
int main(int argc, char argv[]) {
	//paste your code here
	char S[] = "((),(e),(b,c,d))", sub[MAX];
	GList L;//注意啦，L是一个尚未初始化的指针变量
	CreateGList(L, S);
	printf("%d\n", GListDepth(L));
	//getchar();
	return 0;
}

//---广义表的函数定义----------- 
Status SubString(char sub[], char S[], int start, int len) {//start>=1; 
															//也可能求自己的子串 				//求子串，可用于字符串脱去两端括号							
	if (start + len - 1>strlen(S) && start<1) return ERROR; int i = 0;
	//若编译器报错，把for循环中的i添加上，感觉dev有时犯糊涂 
	for (; i<len; ++i) sub[i] = S[start - 1 + i]; sub[i] = '\0';
	return OK;
}
Status sever(char str[], char hstr[]) {
	//将非空串str分成两部分：hsub为第一个','之前的子串，str为之后的只串
	int n = strlen(str), i = 0, k = 0;//i记尚未匹配的左括号的个数，
	for (; i<n && (str[i] != ',' || k != 0); ++i) {//搜索最外层的第一个逗号
		if (str[i] == '(') ++k;
		else if (str[i] == ')') --k; //其他情况就是原子元素 
	}//正常跳出循环时str[i]==',';k==0; 
	if (i<n) {//正常，i就','号的下标 
		SubString(hstr, str, 1, i);  SubString(str, str, i + 2, n - i - 1);
		//1 2 3 4 , 6 7 8
	}
	else { strcpy(hstr, str);   str[0] = '\0'; }
	return OK;
} //sever分离，分开 
Status CreateGList(GList &pL, char S[]) {
	//注意纯C语言的指针不易理解,若是高级语言就用引用调用 
	//好比调用的函数修改被调函数的整型n一样，f(&n),void f(int *p){*p=10;}才能修改n 
	static char emp[] = "()";//静态局部变量，emp空表
	GList p, q;
	if (strcmp(S, emp) == 0) { pL = NULL; return OK; }//创建空表 
	if (!(pL = (GList)malloc(sizeof(GLNode)))) exit(OVERFLOW);
	if (strlen(S) == 1) { (pL)->tag = ATOM; (pL)->Union.atom = *S; }
	//单目运算符结合方向自右向左，故*pL要括起来 
	else {
		(pL)->tag = LIST;
		p = pL;//*能降低指针等级，但是…… 
		char sub[MAX], hsub[MAX];
		SubString(sub, S, 2, strlen(S) - 2);//脱括号 
		do {//重复创建n个子表 
			sever(sub, hsub);//从sub中分离出表头串hsub 
			CreateGList(((p)->Union.ptr.hp), hsub);
			q = p;
			if (strlen(sub)) {//如果表尾不空
				if (!(p = (GList)malloc(sizeof(GLNode)))) exit(OVERFLOW);
				(p)->tag = LIST; (q)->Union.ptr.tp = p;
			}
		} while (strlen(sub));
		(q)->Union.ptr.tp = NULL;//一个字符写错了，调试半天
	}
	return OK;
}
int GListDepth(GList L) {
	//求广义表的深度
	if (!L) return 0;
	if (L->tag = ATOM) return 1;
	int max = 0; GList pp = L;
	for (; pp; pp = pp->Union.ptr.tp) {
		int dep = GListDepth(pp->Union.ptr.tp);
		if (dep > max)max = dep;
	}
	return max + 1;
}
Status CopyGList(GList *T, GList L) {
	//由广义表L复制得到广义表T
	if (!L) T = NULL;
	else {
		if (!(*T = (GList)malloc(sizeof(GLNode))))exit(OVERFLOW);
		(*T)->tag = L->tag;
		if (L->tag == ATOM) (*T)->Union.atom = L->Union.atom;//复制单个原子
		else {
			CopyGList(&((*T)->Union.ptr.hp), L->Union.ptr.hp);
			//复制广义表L->ptr.hp的一个副本T->ptr.hp（类C）
			CopyGList(&((*T)->Union.ptr.tp), L->Union.ptr.tp);
		}
	}
	return OK;
}

