//===============稀疏矩阵的三元组顺序存储表示=========== 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define OK 1
#define ERROR 0
typedef int Status;
//若果非法使用函数，则直接终止程序，毫不留情
 
//假设非零元素个数的最大值为MAXSIZE 
#define MAXSIZE 12500


//------------稀疏矩阵的存储结构----- 
typedef int ElemType;
typedef struct{
	int i,j;//非零元的行下标和列下标 
	ElemType e;//前面自定义的数据元素 
}Triple;//spare稀疏 triple三倍的
typedef struct{
	Triple data[MAXSIZE+1];//data[0]未用
	int m,n,t;//行数，列数，非零个数 
}TSMatrix; 


//----------------稀疏矩阵的基本操作简要说明-------------- 

//创建稀疏矩阵 
Status createSMatrix(TSMatrix &M);
//销毁稀疏矩阵
Status destroySMatrix(TSMatrix &M);
//输出稀疏矩阵M 
void printSMatrix(TSMatrix M);
//复制稀疏矩阵//destination temp
void copySMatrix(TSMatrix &T,TSMatrix M); 
//矩阵相加 
Status addSMatrix(TSMatrix &sum,TSMatrix A,TSMatrix B);
//矩阵相减
Status subSMatrix(TSMatrix &sub,TSMatrix A,TSMatrix B);
//矩阵相乘
Status multSMatrix(TSMatrix &R,TSMatrix A,TSMatrix B);
//矩阵转置 
Status transposeSMatrix(TSMatrix M,TSMatrix &T);


//---------------主函数-----------------
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
	//稀疏矩阵三元组表示法的快速转置算法 
	//时间复杂度O(n+t) 
	int num[MAXSIZE+1],cpot[MAXSIZE+1],p,q; 
	//num[]和cpot[]有效长度分别为j,t; 
	T.m=M.m;T.n=M.n;T.t=M.t;
	if(T.t){
		memset(num,0,M.n+1);//初始化每一列非零元素个数为0
		for(int t=1;t<=M.t;++t){
			++num[M.data[t].j];//求每一列含非零元素的个数 
		} 
		cpot[1]=1;
		for(int col=2;col<=M.t;++col){
			cpot[col]=num[col-1]+cpot[col-1];
		} 
		for(p=1;p<=M.t;++p){
			//start to transpose, so please pay attention to following codes 
			int col=M.data[p].j;//保留M.data[]的列号 
			q=cpot[col];
			T.data[q].i=col;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];//update 
		}
	}
	return OK;
}


//----------基本操作的算法实现------------

Status createSMatrix(TSMatrix &M){
	scanf("%d%d%d",&M.m,&M.n,&M.t);
	for(int i=1;i<=M.t;++i){
		scanf("%d%d",&M.data[i].i,&M.data[i].j);
		scanf("%d",&M.data[i].e);//具体的数据元素，具体自定义
	} 
	return OK;
} 

void printSMatrix(TSMatrix M){
	for(int i=1;i<=M.t;++i){
		printf("%d\t%d",M.data[i].i,M.data[i].j);
		printf("\t%d\n",M.data[i].e);//根据数据元素e的类型编写 
	}
}

Status destroySMatrix(TSMatrix &M){
	//静态数组存放三元组的销毁方法
	for(int i=1;i<=M.t;++i){
		M.data[i].i=M.data[i].j=0;
		M.data[i].e=0;//数组元素e的处理 
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
		T.data[i].e=M.data[i].e;//定义e的数据结构 
	}
}

//------稀疏矩阵的运算------
//稀疏矩阵的加减乘可能会计算出0，这里的算法没有要0 

Status addSMatrix(TSMatrix &sum,TSMatrix A,TSMatrix B){
	if(A.m!=B.m||A.n!=B.n) return ERROR;//不是同一类型的矩阵直接退出 
	int i=1,j=1,k=0;//i,j,k分别是A，B,sum的下标 
	while(i<=A.t||j<B.t){//下面代码有直接复制粘贴的，可以简化 
		if(A.data[i].i==B.data[j].i){//同一行
			if(A.data[i].j==A.data[j].j){
				if(A.data[i].e+B.data[j].e==0) {++i;++j;continue;}
				sum.data[++k].i=A.data[i].i;
				sum.data[k].j=A.data[i].j;
				sum.data[k].e=A.data[i].e+B.data[j].e;//数据元素e
				++i;++j; 
			}else if(A.data[i].j<A.data[j].j){//小于 
				sum.data[++k].i=A.data[i].i;
				sum.data[k].j=A.data[i].j;
				sum.data[k].e=A.data[i].e;//数据元素e
				++i;
			}else{//大于 
				sum.data[++k].i=B.data[i].i;
				sum.data[k].j=B.data[i].j;
				sum.data[k].e=B.data[i].e;//数据元素e
				++j; 
			}
		} else if(A.data[i].i<B.data[j].i){//小于 
			sum.data[++k].i=A.data[i].i;
				sum.data[k].j=A.data[i].j;
				sum.data[k].e=A.data[i].e;//数据元素e
				++i;
		} else{
			sum.data[++k].i=B.data[i].i;
				sum.data[k].j=B.data[i].j;
				sum.data[k].e=B.data[i].e;//数据元素e
				++j; 
		} 
	}
	sum.m=A.m;
	sum.n=A.n;
	sum.t=k;
	return OK;
}

Status subSMatrix(TSMatrix &sub,TSMatrix A,TSMatrix B){
	if(A.m!=B.m||A.n!=B.n) return ERROR;//不是同一类型的矩阵直接退出 
	int i=1,j=1,k=0;//i,j,k分别是A，B,sub的下标 
	while(i<=A.t||j<B.t){//下面代码有直接复制粘贴的，可以简化 
		if(A.data[i].i==B.data[j].i){//同一行
			if(A.data[i].j==A.data[j].j){
				if(A.data[i].e-B.data[j].e==0) {++i;++j;continue;}
				sub.data[++k].i=A.data[i].i;
				sub.data[k].j=A.data[i].j;
				sub.data[k].e=A.data[i].e-B.data[j].e;//数据元素e
				++i;++j; 
			}else if(A.data[i].j<A.data[j].j){//小于 
				sub.data[++k].i=A.data[i].i;
				sub.data[k].j=A.data[i].j;
				sub.data[k].e=A.data[i].e;//数据元素e
				++i;
			}else{//大于 
				sub.data[++k].i=B.data[i].i;
				sub.data[k].j=B.data[i].j;
				sub.data[k].e=-B.data[j].e;//数据元素e
				++j; 
			}
		} else if(A.data[i].i<B.data[j].i){//小于 
			sub.data[++k].i=A.data[i].i;
				sub.data[k].j=A.data[i].j;
				sub.data[k].e=A.data[i].e;//数据元素e
				++i;
		} else{
			sub.data[++k].i=B.data[i].i;
				sub.data[k].j=B.data[i].j;
				sub.data[k].e=-B.data[j].e;//数据元素e
				++j; 
		} 
	}
	sub.m=A.m;
	sub.n=A.n;
	sub.t=k;
	return OK;	
}

Status multSMatrix(TSMatrix &R,TSMatrix A,TSMatrix B){
	//一般矩阵相乘的时间复杂度为i*j*j*k
//	if(A.n!=B.m) return ERROR;//不是同一类型的矩阵直接退出 
//	R.m=A.m;
//	R.n=B.n;
//	int numA[MAXSIZE+1],numB[MAXSIZE+1],cpotA[MAXSIZE+1],cpotB[MAXSIZE+1];
//	//这里的num[]和cpot[]和转置中的还是有区别的,但是它们都是存个数的，这一点就够了 
//	memset(numA,0,A.m+1);//初始化 
//	memset(numB,0,B.n+1); 
//	for(int i=1;i<=A.t;++i) numA[A.data[i].i]++; //第i行非零元素个数 
//	for(int i=0;i<=B.t;++i) numB[B.data[i].j]++; //第j列非零元素个数 
//	coptA[1]=cpotB[1]=1;
//	for(int i=2;i<=A.t;++i) cpotA[i]=cpotA[i-1]+numA[i-1];
//	for(int i=2;i<=B.t;++i) cpotB[i]=cpotB[i-1]+numB[i-1];
//	int k=0;//k 
//	for(int i=1;i<=A.t;++i){
//		if(numA[A.data[i].i]!=0&&numB[A.data[i].j]!=0){
//			for(int j=i;j<=numA[A.data[i].i];++j){
//				
//			}
//		}  //未完待续 
//	}
	
	return OK;
}



/*--------输入文本data.in----------- 
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
