//=============�����ʵ��=====================
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

//----------�����˳��洢��ʾ---------------- 
#include<stdarg.h>//��׼ͷ�ļ�,�ṩva_arg,va_start,va_end,va_list 
					//���ڴ�ȡ�䳤������
//va_list�൱��char *;va_end(ap);�൱��ap=0;NULL��
//����va_arg(ap,variable)������������va_start(ap,variable)����ap=��ַ 
#define MAX_ARRAY_DIM 8//�����������󳤶�
typedef int ElemType;//��������Ĭ��Ϊint 
typedef struct{
	ElemType *base;//����Ԫ�ػ�ַ����InitArray���� 
	int dim;//�����ά�� 
	int *bounds;//����ά���ַ����InitArray����
	int *constans;//����Ӱ����������ַ����InitArray���� 
}Array;

//-----------���������ĺ���ԭ��˵��----------------------
Status initArray(Array &A,int dim,...);
	//��ά��dim�����ĸ�ά���ȺϷ���������Ӧ������A��������OK
Status destroyArray(Array &A);
	//��������A
Status locate(Array A,va_list ap,int &off);
	//��apָʾ���±�Ϸ����������Ԫ����A����Ե�ַoff 
Status value(Array A,ElemType &e,...);
	//A��nά���飬eΪԪ�ر����������n���±�ֵ��
	//���±겻Խ�磬��e��ֵ��Ϊ��ָ����A��Ԫ�أ�������OK
Status assign(Array &A,ElemType &e,...);
	//A��nά���飬eΪԪ�ر����������n���±�ֵ��
	//���±겻Խ�磬��e��ֵ������ָ����A��Ԫ�أ�������OK

/*--------������--------------------------------------------------------------------------------------*/
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

//-----------�����������㷨����----------------- 
Status initArray(Array &A,int dim,...){
	//��ά��dim�͸�ά���ȺϷ���������Ӧ������A,������OK
	if(dim<1||dim>MAX_ARRAY_DIM){
		return ERROR; 
	} 
	A.dim=dim;
	A.bounds=(int *)malloc(dim*sizeof(int));
	if(!A.bounds) exit(OVERFLOW);
	//����ά�ȺϷ��������A.bounds,���A��Ԫ������elemtotal
	int elemtotal=1;
	va_list ap;//apΪva_list���ͣ��Ǵ�ű䳤�����ı���Ϣ�����飬array point 
	va_start(ap,dim);
	for(int i=0;i<dim;++i){
		A.bounds[i]=va_arg(ap,int);//��������va_arg()Ӧ���Ǵ��εĺ궨��;
		if(A.bounds[i]<0) return UNDERFLOW; 
		elemtotal*=A.bounds[i];//bounds������ά���ַ��bounds[i]�ǵ�iά�Ŀ�ȣ����� 
	} 
	va_end(ap);
	A.base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
	if(!A.base) exit(OVERFLOW);
	//��Ӱ�����ĳ���ci,������A.constants[i-1],i=1..dim
	//LOC (j1,j2,��,jn ) = LOC(0,0,��,0) + (b2*b3*��*bn * j1+ b3*b4*��*bn * j2+ ����+ bn*jn-1 + jn ) * L 
	//ÿ������ռL���洢��Ԫ
	//c[n]=L,c[i-1]=b[i]*c[i],1<i&&i<=n����ͷ����޷�ճ��   
	A.constans=(int *)malloc(dim*sizeof(int));
	if(!A.constans) return OVERFLOW;
	A.constans[dim-1]=1;//L����1��ָ���������Ԫ�صĴ�СΪ��λ
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
	//��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A����Եĵ�ַoff
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
	//A��nά���飬eΪԪ�ر����������n���±�ֵ
	//���±겻Խ�磬��e��ֵ������ָ����A��Ԫ�أ�������OK
	va_list ap;//char *ap; 
	va_start(ap,e);
	Status result;
	int off;
	if((result=locate(A,ap,off))<0) return result;
	e=*(A.base+off);
	return OK;
}

Status assign(Array &A,ElemType &e,...){
	//A��nά���飬eΪԪ�ر����������n���±�ֵ��
	//���±겻Խ�磬��e��ֵ������ָ����A��Ԫ�أ�������OK
	char *ap;//�����к궨�壬����й� 
	va_start(ap,e);
	int result,off; 
	if((result=locate(A,ap,off))<0){
		return result;
	} 
	*(A.base+off)=e;
	return OK;
}
