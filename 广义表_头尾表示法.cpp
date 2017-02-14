//�������ͷβ����洢��ʾ��ʵ�� 
#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX 10000//�ַ�����󳤶� 
typedef int Status;

//-----������ͷβ����洢��ʾ----- 
typedef enum { ATOM = 0, LIST }ElemTag;//ATOM=0:ԭ�ӣ�LIST=1:�ӱ� 
typedef char AtomType;
typedef struct GLNode {
	ElemTag tag;			//�������֣�����ԭ�ӽڵ�ͱ�ڵ�
	union {
		AtomType atom;		//atom��ԭ�ӵ�ֵ��
		struct { struct GLNode *hp, *tp; }ptr;
		//ptr�Ǳ�ڵ��ָ����ptr.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β 
	}Union;
}**GList_p, *GList, GLNode;

//---�����ĺ�������-------------
Status sever(char str[], char hstr[]);
Status CreateGList(GList &L, char S[]);
Status SubString(char sub[], char S[], int start, int len);
int GListDepth(GList L);
Status CopyGList(GList *T, GList L);

//-----------------������------------------------------------------------------------------------------ 
int main(int argc, char argv[]) {
	//paste your code here
	char S[] = "((),(e),(b,c,d))", sub[MAX];
	GList L;//ע������L��һ����δ��ʼ����ָ�����
	CreateGList(L, S);
	printf("%d\n", GListDepth(L));
	//getchar();
	return 0;
}

//---�����ĺ�������----------- 
Status SubString(char sub[], char S[], int start, int len) {//start>=1; 
															//Ҳ�������Լ����Ӵ� 				//���Ӵ����������ַ�����ȥ��������							
	if (start + len - 1>strlen(S) && start<1) return ERROR; int i = 0;
	//��������������forѭ���е�i����ϣ��о�dev��ʱ����Ϳ 
	for (; i<len; ++i) sub[i] = S[start - 1 + i]; sub[i] = '\0';
	return OK;
}
Status sever(char str[], char hstr[]) {
	//���ǿմ�str�ֳ������֣�hsubΪ��һ��','֮ǰ���Ӵ���strΪ֮���ֻ��
	int n = strlen(str), i = 0, k = 0;//i����δƥ��������ŵĸ�����
	for (; i<n && (str[i] != ',' || k != 0); ++i) {//���������ĵ�һ������
		if (str[i] == '(') ++k;
		else if (str[i] == ')') --k; //�����������ԭ��Ԫ�� 
	}//��������ѭ��ʱstr[i]==',';k==0; 
	if (i<n) {//������i��','�ŵ��±� 
		SubString(hstr, str, 1, i);  SubString(str, str, i + 2, n - i - 1);
		//1 2 3 4 , 6 7 8
	}
	else { strcpy(hstr, str);   str[0] = '\0'; }
	return OK;
} //sever���룬�ֿ� 
Status CreateGList(GList &pL, char S[]) {
	//ע�ⴿC���Ե�ָ�벻�����,���Ǹ߼����Ծ������õ��� 
	//�ñȵ��õĺ����޸ı�������������nһ����f(&n),void f(int *p){*p=10;}�����޸�n 
	static char emp[] = "()";//��̬�ֲ�������emp�ձ�
	GList p, q;
	if (strcmp(S, emp) == 0) { pL = NULL; return OK; }//�����ձ� 
	if (!(pL = (GList)malloc(sizeof(GLNode)))) exit(OVERFLOW);
	if (strlen(S) == 1) { (pL)->tag = ATOM; (pL)->Union.atom = *S; }
	//��Ŀ�������Ϸ����������󣬹�*pLҪ������ 
	else {
		(pL)->tag = LIST;
		p = pL;//*�ܽ���ָ��ȼ������ǡ��� 
		char sub[MAX], hsub[MAX];
		SubString(sub, S, 2, strlen(S) - 2);//������ 
		do {//�ظ�����n���ӱ� 
			sever(sub, hsub);//��sub�з������ͷ��hsub 
			CreateGList(((p)->Union.ptr.hp), hsub);
			q = p;
			if (strlen(sub)) {//�����β����
				if (!(p = (GList)malloc(sizeof(GLNode)))) exit(OVERFLOW);
				(p)->tag = LIST; (q)->Union.ptr.tp = p;
			}
		} while (strlen(sub));
		(q)->Union.ptr.tp = NULL;//һ���ַ�д���ˣ����԰���
	}
	return OK;
}
int GListDepth(GList L) {
	//����������
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
	//�ɹ����L���Ƶõ������T
	if (!L) T = NULL;
	else {
		if (!(*T = (GList)malloc(sizeof(GLNode))))exit(OVERFLOW);
		(*T)->tag = L->tag;
		if (L->tag == ATOM) (*T)->Union.atom = L->Union.atom;//���Ƶ���ԭ��
		else {
			CopyGList(&((*T)->Union.ptr.hp), L->Union.ptr.hp);
			//���ƹ����L->ptr.hp��һ������T->ptr.hp����C��
			CopyGList(&((*T)->Union.ptr.tp), L->Union.ptr.tp);
		}
	}
	return OK;
}

