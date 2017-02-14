//===============ϡ��������Ԫ��˳��洢��ʾ=========== 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define OK 1
#define ERROR 0
typedef int Status;
//�����Ƿ�ʹ�ú�������ֱ����ֹ���򣬺�������
 
//�������Ԫ�ظ��������ֵΪMAXSIZE 
#define MAXSIZE 12500


//------------ϡ�����Ĵ洢�ṹ----- 
typedef int ElemType;
typedef struct{
	int i,j;//����Ԫ�����±�����±� 
	ElemType e;//ǰ���Զ��������Ԫ�� 
}Triple;//spareϡ�� triple������
typedef struct{
	Triple data[MAXSIZE+1];//data[0]δ��
	int m,n,t;//������������������� 
}TSMatrix; 


//----------------ϡ�����Ļ���������Ҫ˵��-------------- 

//����ϡ����� 
Status createSMatrix(TSMatrix &M);
//����ϡ�����
Status destroySMatrix(TSMatrix &M);
//���ϡ�����M 
void printSMatrix(TSMatrix M);
//����ϡ�����//destination temp
void copySMatrix(TSMatrix &T,TSMatrix M); 
//������� 
Status addSMatrix(TSMatrix &sum,TSMatrix A,TSMatrix B);
//�������
Status subSMatrix(TSMatrix &sub,TSMatrix A,TSMatrix B);
//�������
Status multSMatrix(TSMatrix &R,TSMatrix A,TSMatrix B);
//����ת�� 
Status transposeSMatrix(TSMatrix M,TSMatrix &T);


//---------------������-----------------
int main(int argc,char* argv[]){
	//paste my code here
	freopen("d:\\coding\\data.in","r",stdin); 
	TSMatrix M,T;
	createSMatrix(M);
	transposeSMatrix(M,T);
//	destroySMatrix(M); 
//	copySMatrix(T,M);
//	subSMatrix(T,M,M);
	printSMatrix(M);
//	printSMatrix(T);
	for(int i=0;i<25;++i)printf("=");printf("\n"); 
	printSMatrix(T);
	
	return 0;
} 

Status transposeSMatrix(TSMatrix M,TSMatrix &T){
	//ϡ�������Ԫ���ʾ���Ŀ���ת���㷨 
	//ʱ�临�Ӷ�O(n+t) 
	int num[MAXSIZE+1],cpot[MAXSIZE+1],p,q; 
	//num[]��cpot[]��Ч���ȷֱ�Ϊj,t; 
	T.m=M.m;T.n=M.n;T.t=M.t;
	if(T.t){
		memset(num,0,M.n+1);//��ʼ��ÿһ�з���Ԫ�ظ���Ϊ0
		for(int t=1;t<=M.t;++t){
			++num[M.data[t].j];//��ÿһ�к�����Ԫ�صĸ��� 
		} 
		cpot[1]=1;
		for(int col=2;col<=M.t;++col){
			cpot[col]=num[col-1]+cpot[col-1];
		} 
		for(p=1;p<=M.t;++p){
			//start to transpose, so please pay attention to following codes 
			int col=M.data[p].j;//����M.data[]���к� 
			q=cpot[col];
			T.data[q].i=col;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];//update 
		}
	}
	return OK;
}


//----------�����������㷨ʵ��------------

Status createSMatrix(TSMatrix &M){
	scanf("%d%d%d",&M.m,&M.n,&M.t);
	for(int i=1;i<=M.t;++i){
		scanf("%d%d",&M.data[i].i,&M.data[i].j);
		scanf("%d",&M.data[i].e);//���������Ԫ�أ������Զ���
	} 
	return OK;
} 

void printSMatrix(TSMatrix M){
	for(int i=1;i<=M.t;++i){
		printf("%d\t%d",M.data[i].i,M.data[i].j);
		printf("\t%d\n",M.data[i].e);//��������Ԫ��e�����ͱ�д 
	}
}

Status destroySMatrix(TSMatrix &M){
	//��̬��������Ԫ������ٷ���
	for(int i=1;i<=M.t;++i){
		M.data[i].i=M.data[i].j=0;
		M.data[i].e=0;//����Ԫ��e�Ĵ��� 
	} 
	M.m=M.n=M.t=0;
	return OK;
}

void copySMatrix(TSMatrix &T,TSMatrix M){
	T.m=M.m;
	T.n=M.n;
	T.t=M.t;
	for(int i=1;i<=M.t;++i){
		T.data[i].i=M.data[i].i;
		T.data[i].j=M.data[i].j;
		T.data[i].e=M.data[i].e;//����e�����ݽṹ 
	}
}

//------ϡ����������------
//ϡ�����ļӼ��˿��ܻ�����0��������㷨û��Ҫ0 

Status addSMatrix(TSMatrix &sum,TSMatrix A,TSMatrix B){
	if(A.m!=B.m||A.n!=B.n) return ERROR;//����ͬһ���͵ľ���ֱ���˳� 
	int i=1,j=1,k=0;//i,j,k�ֱ���A��B,sum���±� 
	while(i<=A.t||j<B.t){//���������ֱ�Ӹ���ճ���ģ����Լ� 
		if(A.data[i].i==B.data[j].i){//ͬһ��
			if(A.data[i].j==A.data[j].j){
				if(A.data[i].e+B.data[j].e==0) {++i;++j;continue;}
				sum.data[++k].i=A.data[i].i;
				sum.data[k].j=A.data[i].j;
				sum.data[k].e=A.data[i].e+B.data[j].e;//����Ԫ��e
				++i;++j; 
			}else if(A.data[i].j<A.data[j].j){//С�� 
				sum.data[++k].i=A.data[i].i;
				sum.data[k].j=A.data[i].j;
				sum.data[k].e=A.data[i].e;//����Ԫ��e
				++i;
			}else{//���� 
				sum.data[++k].i=B.data[i].i;
				sum.data[k].j=B.data[i].j;
				sum.data[k].e=B.data[i].e;//����Ԫ��e
				++j; 
			}
		} else if(A.data[i].i<B.data[j].i){//С�� 
			sum.data[++k].i=A.data[i].i;
				sum.data[k].j=A.data[i].j;
				sum.data[k].e=A.data[i].e;//����Ԫ��e
				++i;
		} else{
			sum.data[++k].i=B.data[i].i;
				sum.data[k].j=B.data[i].j;
				sum.data[k].e=B.data[i].e;//����Ԫ��e
				++j; 
		} 
	}
	sum.m=A.m;
	sum.n=A.n;
	sum.t=k;
	return OK;
}

Status subSMatrix(TSMatrix &sub,TSMatrix A,TSMatrix B){
	if(A.m!=B.m||A.n!=B.n) return ERROR;//����ͬһ���͵ľ���ֱ���˳� 
	int i=1,j=1,k=0;//i,j,k�ֱ���A��B,sub���±� 
	while(i<=A.t||j<B.t){//���������ֱ�Ӹ���ճ���ģ����Լ� 
		if(A.data[i].i==B.data[j].i){//ͬһ��
			if(A.data[i].j==A.data[j].j){
				if(A.data[i].e-B.data[j].e==0) {++i;++j;continue;}
				sub.data[++k].i=A.data[i].i;
				sub.data[k].j=A.data[i].j;
				sub.data[k].e=A.data[i].e-B.data[j].e;//����Ԫ��e
				++i;++j; 
			}else if(A.data[i].j<A.data[j].j){//С�� 
				sub.data[++k].i=A.data[i].i;
				sub.data[k].j=A.data[i].j;
				sub.data[k].e=A.data[i].e;//����Ԫ��e
				++i;
			}else{//���� 
				sub.data[++k].i=B.data[i].i;
				sub.data[k].j=B.data[i].j;
				sub.data[k].e=-B.data[j].e;//����Ԫ��e
				++j; 
			}
		} else if(A.data[i].i<B.data[j].i){//С�� 
			sub.data[++k].i=A.data[i].i;
				sub.data[k].j=A.data[i].j;
				sub.data[k].e=A.data[i].e;//����Ԫ��e
				++i;
		} else{
			sub.data[++k].i=B.data[i].i;
				sub.data[k].j=B.data[i].j;
				sub.data[k].e=-B.data[j].e;//����Ԫ��e
				++j; 
		} 
	}
	sub.m=A.m;
	sub.n=A.n;
	sub.t=k;
	return OK;	
}

Status multSMatrix(TSMatrix &R,TSMatrix A,TSMatrix B){
	//һ�������˵�ʱ�临�Ӷ�Ϊi*j*j*k
//	if(A.n!=B.m) return ERROR;//����ͬһ���͵ľ���ֱ���˳� 
//	R.m=A.m;
//	R.n=B.n;
//	int numA[MAXSIZE+1],numB[MAXSIZE+1],cpotA[MAXSIZE+1],cpotB[MAXSIZE+1];
//	//�����num[]��cpot[]��ת���еĻ����������,�������Ƕ��Ǵ�����ģ���һ��͹��� 
//	memset(numA,0,A.m+1);//��ʼ�� 
//	memset(numB,0,B.n+1); 
//	for(int i=1;i<=A.t;++i) numA[A.data[i].i]++; //��i�з���Ԫ�ظ��� 
//	for(int i=0;i<=B.t;++i) numB[B.data[i].j]++; //��j�з���Ԫ�ظ��� 
//	coptA[1]=cpotB[1]=1;
//	for(int i=2;i<=A.t;++i) cpotA[i]=cpotA[i-1]+numA[i-1];
//	for(int i=2;i<=B.t;++i) cpotB[i]=cpotB[i-1]+numB[i-1];
//	int k=0;//k 
//	for(int i=1;i<=A.t;++i){
//		if(numA[A.data[i].i]!=0&&numB[A.data[i].j]!=0){
//			for(int j=i;j<=numA[A.data[i].i];++j){
//				
//			}
//		}  //δ����� 
//	}
	
	return OK;
}



/*--------�����ı�data.in----------- 
6 6 8
1 2 12
1 3 9
3 1 -3
3 6 14
4 3 24
5 2 18
6 1 15
6 4 -7
-----------------------------------*/ 
