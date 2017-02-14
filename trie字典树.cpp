#include<cstdio> 
#include<cstring>
using namespace std;
struct trie{
	trie *chi[26];
	int num;
	trie(){
		num=0;
		for(int i=0;i<26;++i)
			chi[i]=NULL;
	}//¹¹Ôìº¯Êý 
}*root;
void insertTrie(char s[]){
	trie *p=root;
	p->num++;
	for(int i=0;s[i];++i){
		int j=s[i]-'a';
		if(p->chi[j]==NULL)
			p->chi[j]=new trie();
		p=p->chi[j];
		p->num++;
	}
}
int searchTrie(char s[]){
	trie *p=root;
	for(int i=0;p&&s[i];++i){
		int j=s[i]-'a';
		p=p->chi[j];
	}
	if(!p) return 0;
	else return p->num;
}
int main(){
	freopen("d:\\coding\\data.in","r",stdin);
	char s[12];
	int n,m;
	while(~scanf("%d",&n)){
		root=new trie;
		while(n--){
			scanf("%s",s);
			insertTrie(s);
		}
		scanf("%d",&m);
		while(m--){
			scanf("%s",s);
			printf("%d\n",searchTrie(s));
		}
	}
	return 0;
}
