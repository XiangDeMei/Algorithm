/*
	TrieÊ÷±äÐÎ 
	http://acm.hdu.edu.cn/showproblem.php?pid=2846
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

#define  MAX    26
#define  MAXN   1000000
typedef struct TrieNode
{
	int nCount;  
	int id;
	struct TrieNode *next[MAX]; 
} TrieNode;
TrieNode Memory[MAXN]; 
int allocp = 0;
TrieNode * createTrieNode()
{
	TrieNode * tmp = &Memory[allocp++];
	tmp->nCount = 1;
	tmp->id = -1;
	for (int i = 0; i < MAX; i++)
		tmp->next[i] = NULL;
	return tmp;
}

void insertTrie(TrieNode ** pRoot, char * str, int num)
{
	TrieNode * tmp = *pRoot;
	int i = 0, k;
	while (str[i])
	{
		k = str[i] - 'a'; 
		if (tmp->next[k])
		{
			if(tmp->next[k]->id!=num){
				tmp->next[k]->nCount++;
				tmp->next[k]->id = num;
			}
		}
		else
		{
			tmp->next[k] = createTrieNode();
			tmp->next[k]->id = num;
		}
		tmp = tmp->next[k];
		i++;
	}
}

int searchTrie(TrieNode * root, char * str)
{
	if (root == NULL)
		return 0;
	TrieNode * tmp = root;
	int i = 0, k;
	while (str[i])
	{
		k = str[i] - 'a';
		if (tmp->next[k])
		{
			tmp = tmp->next[k];
		}
		else
			return 0;
		i++;
	}
	return tmp->nCount;
}

int main(void)
{
	char s[21];
	int i,n,m,l;
	TrieNode *Root = createTrieNode();
	scanf("%d",&n);
	while (n--)
	{
		
		scanf("%s",s);
		l=strlen(s);
		for(i=0;i<l;i++)
		{
			insertTrie(&Root, s+i,n+1);
		}
	}
	scanf("%d",&m);
	while (m--)
	{
		scanf("%s",s);
		printf("%d\n", searchTrie(Root, s));
	}

	return 0;
}
