//=============数组的实现=====================
#define _CRT_SECURE_NO_WANGINGS 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Status int
#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0 
#define OVERFLOW 2
#define UNDERFLOW -2

//----------数组的顺序存储表示---------------- 
#include<stdarg.h>//标准头文件,提供va_arg,va_start,va_end,va_list 
					//用于存取变长参数表
//va_list相当于char *;va_end(ap);相当于ap=0;NULL，
//还有va_arg(ap,variable)分析，自增，va_start(ap,variable)就是ap=地址 
#define MAX_ARRAY_DIM 8//假设数组的最大长度
typedef int ElemType;//数据类型默认为int 
typedef struct{
	ElemType *base;//数组元素基址，由InitArray分配 
	int dim;//数组的维界 
	int *bounds;//数组维界基址，由InitArray分配
	int *constans;//数组影像函数常量基址，由InitArray分配 
}Array;

//-----------基本操作的函数原型说明----------------------
Status initArray(Array &A,int dim,...);
	//若维数dim和随后的各维长度合法，则构造相应的数组A，并返回OK
Status destroyArray(Array &A);
	//销毁数组A
Status locate(Array A,va_list ap,int &off);
	//若ap指示的下标合法，则求出该元素在A中相对地址off 
Status value(Array A,ElemType &e,...);
	//A是n维数组，e为元素变量，随后是n个下标值。
	//若下标不越界，则将e的值赋为所指定的A的元素，并返回OK
Status assign(Array &A,ElemType &e,...);
	//A是n维数组，e为元素变量，随后是n个下标值。
	//若下标不越界，则将e的值赋给所指定的A的元素，并返回OK

/*--------主函数--------------------------------------------------------------------------------------*/
int main(int argc, char *argv[]){
	//paste your code here
	Array A;
	initArray(A,3,10,10,10);
	printf("%d\n",A.dim);
	for(int i=0;i<A.dim;++i){
		printf("%d\n",A.constans[i]);
	}
	destroyArray(A);
	printf("%d\n",A.dim);
	return 0;
} 

//-----------基本操作的算法描述----------------- 
Status initArray(Array &A,int dim,...){
	//若维度dim和各维长度合法，则构造相应的数组A,并返回OK
	if(dim<1||dim>MAX_ARRAY_DIM){
		return ERROR; 
	} 
	A.dim=dim;
	A.bounds=(int *)malloc(dim*sizeof(int));
	if(!A.bounds) exit(OVERFLOW);
	//若各维度合法，则存入A.bounds,求出A的元素总数elemtotal
	int elemtotal=1;
	va_list ap;//ap为va_list类型，是存放变长参数的表信息的数组，array point 
	va_start(ap,dim);
	for(int i=0;i<dim;++i){
		A.bounds[i]=va_arg(ap,int);//检查参数，va_arg()应该是带参的宏定义;
		if(A.bounds[i]<0) return UNDERFLOW; 
		elemtotal*=A.bounds[i];//bounds是数组维界基址，bounds[i]是第i维的宽度，界限 
	} 
	va_end(ap);
	A.base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
	if(!A.base) exit(OVERFLOW);
	//求影像函数的常数ci,并存入A.constants[i-1],i=1..dim
	//LOC (j1,j2,…,jn ) = LOC(0,0,…,0) + (b2*b3*…*bn * j1+ b3*b4*…*bn * j2+ ……+ bn*jn-1 + jn ) * L 
	//每个数据占L个存储单元
	//c[n]=L,c[i-1]=b[i]*c[i],1<i&&i<=n，求和符号无法粘贴   
	A.constans=(int *)malloc(dim*sizeof(int));
	if(!A.constans) return OVERFLOW;
	A.constans[dim-1]=1;//L等于1，指针的增减以元素的大小为单位
	for(int i=dim-2;i>=0;--i){
		A.constans[i]=A.bounds[i]*A.constans[i+1];
	} 
	return OK;
}

Status destroyArray(Array &A){
	if(!A.base) return ERROR;
	free(A.base);A.base=NULL;
	if(!A.bounds) return ERROR;
	free(A.bounds);A.bounds=NULL;
	if(!A.constans) return ERROR;
	free(A.constans);A.constans=0;
	A.dim=0; 
	return OK; 
}

Status locate(Array A,char *ap,int &off){
	//若ap指示的各下标值合法，则求出改元素在A中相对的地址off
	off=0;
	int ind; 
	for(int i=0;i<A.dim;++i){
		ind=va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i]) return OVERFLOW;
		off+=A.constans[i]*ind;
	}
	return OK;
}

Status value(Array A,ElemType &e,...){
	//A是n维数组，e为元素变量，随后是n个下标值
	//若下标不越界，则将e的值赋给所指定的A的元素，并返回OK
	va_list ap;//char *ap; 
	va_start(ap,e);
	Status result;
	int off;
	if((result=locate(A,ap,off))<0) return result;
	e=*(A.base+off);
	return OK;
}

Status assign(Array &A,ElemType &e,...){
	//A是n维数组，e为元素变量，随后是n个下标值。
	//若下标不越界，则将e的值赋给所指定的A的元素，并返回OK
	char *ap;//好像有宏定义，框架有关 
	va_start(ap,e);
	int result,off; 
	if((result=locate(A,ap,off))<0){
		return result;
	} 
	*(A.base+off)=e;
	return OK;
}
