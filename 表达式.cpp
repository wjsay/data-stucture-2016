#include<cstdio>
#include<iostream>
#include<stack>
#include<cmath>
#include<cstring>
using namespace std;
const int maxn=1000000;

//���Զ���һ���ַ�����������cǰ��һ���ַ��������Ϳ��Խ������������
//�����ں����ڲ������룬�����ؽ��ͺ����ĸ����ԣ�������Ҫһ���Զ��� 
//ע���������ź�Ӣ�����Ų�ͬ��*(++c)���൱��c=getchar(); 
//ѹ��ʱ����¼һ����Ч�ַ��������ж�-�Ƿ��Ǹ��� 
int Precede(char opt1,char opt2){
	//�ж������ջ��ջ��Ԫ��opt1�Ͷ���������opt2֮������ȼ�����
	//����������switchʵ�֣�Ҳ���Դ�� 
	if(!strchr("+-*/()#=\n\377\0",opt2)) return -2;
	switch(opt1){
		case '+':
		case '-':	switch(opt2){
						case '+':
						case '-':
						case ')':
						case '#':	return 1;
						
						case '*':
						case '/':
						case '(':	return -1;
					} 			
		case '*':
		case '/':	return(opt2=='('?-1:1);			
			
		case '(':	if(opt2==')')return 0;
					return(opt2=='#'?-2:-1);
		case ')':	return(opt2=='('?-2:1);
		
		case '=':	if(opt2=='#')return 0;
					return(opt2=='('?-2:-1);
	} 
} 

double Operate(double a,char opt,double b){
	switch(opt){
		case '+':	return a+b;
		case '-':	return a-b;
		case '*':	return a*b;
		case '/':	return a/b;
		default:	return 0;//��������ǲ�����ȱʡ�� 
	}
} 

double EvaluateExpression(char *c){
	if(*c=='\n'||*c=='\0'||*c==-1) return 0;//������Դ�� 
	stack<double> OPND;
	stack<char> OPTR;
	OPTR.push('='); char pre='\0';
	while(!strchr("\n#=",*c) &&*c!=-1||OPTR.top()!='='){
		if('0'<=*c&&*c<='9'||(*c=='-'&&(pre<'0'||pre>'9'))){//����������;������֣��͵ý�������ջ 
			double num=0,flag=1,small=0;
			if(*c=='-') {flag=-1;*(++c);}//�д����� 
			while('0'<=*c&&*c<='9'){
				num=num*10+*c-'0';
				*(++c);
			}
			if(*c=='.'){
				small=0;int i=1;
				while('0'<=*(++c)&&*c<='9'){
					small=small+pow(0.1,(i++))*(*c-'0');
				}
			}
			if(*c=='%'){
				OPND.push((num+small)*flag/100.0);
				*(++c);
			}else	OPND.push((num+small)*flag);//��������ջ 
			pre=*(c-1);
		}else
			switch(Precede(OPTR.top(),*c)){
				case -1:	OPTR.push(*c);*(++c);pre=*(c-1);break;//�������ջ 
				case 0: OPTR.pop();*(++c);break;//������
				case 1: {
					if(OPTR.empty()) return 0;
					char opt=OPTR.top();OPTR.pop();
					if(OPND.empty()) return 0;
					double b=OPND.top();OPND.pop();
					if(OPND.empty()) return 0;
					double a=OPND.top();OPND.pop();
					OPND.push(Operate(a,opt,b)); //ע��a,b˳�� 
					break;
				}
				default: if(!strchr("#=\n\0\377",*c)) *(++c);//ִ��ȱʡ˵����˵�����������⣬��������//Ҳ����case -2��
				//default: return ERROR;//������Ŀ�������������������Ͼ䣬�������� 
			}
	} 
	return OPND.top(); 
}
void getExpression(char *p){
	while((*p=getchar())&&*p!='\n'&&*p!='='&&*p!='#'&&*p!=-1)p++;
	//*(++p)='#';*(++p)='\0'; //��һ�п��Բ�Ҫ��ֻ�Ǹ��ַ���һ����β����дҲû�� 
}
int main(int argc,char *argv[]){
	//freopen("d:\\coding\\data.in","r",stdin); 
	while(1){
		char str[maxn];
		//strcpy(str,"2 * ( -703 + 300% )");//getExpression()���Դ���˾� 
		//strcat(str,"=");
		getExpression(str);
		printf("%.2lf\n",EvaluateExpression(str));
	} 
	return 0;
}
