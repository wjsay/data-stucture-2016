#include<cstdio>
#include<iostream>
#include<stack>
#include<cmath>
#include<cstring>
using namespace std;
const int maxn=1000000;

//可以定义一个字符变量，保存c前的一个字符，这样就可以解决负数的问题
//但是在函数内部有输入，会严重降低函数的复用性，所以我要一次性都完 
//注意中文括号和英文括号不同；*(++c)就相当于c=getchar(); 
//压入时，记录一个有效字符，便于判断-是否是负号 
int Precede(char opt1,char opt2){
	//判断运算符栈的栈顶元素opt1和读入的运算符opt2之间的优先级函数
	//可以用两层switch实现，也可以打表 
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
		default:	return 0;//正常情况是不会有缺省的 
	}
} 

double EvaluateExpression(char *c){
	if(*c=='\n'||*c=='\0'||*c==-1) return 0;//数据来源空 
	stack<double> OPND;
	stack<char> OPTR;
	OPTR.push('='); char pre='\0';
	while(!strchr("\n#=",*c) &&*c!=-1||OPTR.top()!='='){
		if('0'<=*c&&*c<='9'||(*c=='-'&&(pre<'0'||pre>'9'))){//不是运算符就就是数字，就得进运算数栈 
			double num=0,flag=1,small=0;
			if(*c=='-') {flag=-1;*(++c);}//招待减号 
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
			}else	OPND.push((num+small)*flag);//运算数进栈 
			pre=*(c-1);
		}else
			switch(Precede(OPTR.top(),*c)){
				case -1:	OPTR.push(*c);*(++c);pre=*(c-1);break;//运算符进栈 
				case 0: OPTR.pop();*(++c);break;//脱括号
				case 1: {
					if(OPTR.empty()) return 0;
					char opt=OPTR.top();OPTR.pop();
					if(OPND.empty()) return 0;
					double b=OPND.top();OPND.pop();
					if(OPND.empty()) return 0;
					double a=OPND.top();OPND.pop();
					OPND.push(Operate(a,opt,b)); //注意a,b顺序 
					break;
				}
				default: if(!strchr("#=\n\0\377",*c)) *(++c);//执行缺省说明，说明输入有问题，继续读入//也可以case -2：
				//default: return ERROR;//若是项目计算器，这用这句代替上句，其他…… 
			}
	} 
	return OPND.top(); 
}
void getExpression(char *p){
	while((*p=getchar())&&*p!='\n'&&*p!='='&&*p!='#'&&*p!=-1)p++;
	//*(++p)='#';*(++p)='\0'; //这一行可以不要（只是给字符串一个结尾，不写也没事 
}
int main(int argc,char *argv[]){
	//freopen("d:\\coding\\data.in","r",stdin); 
	while(1){
		char str[maxn];
		//strcpy(str,"2 * ( -703 + 300% )");//getExpression()可以代替此句 
		//strcat(str,"=");
		getExpression(str);
		printf("%.2lf\n",EvaluateExpression(str));
	} 
	return 0;
}
