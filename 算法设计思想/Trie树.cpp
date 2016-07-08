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

//对每个结点开一个字母集大小的数组，对应的下标是儿子所表示的字母，内容则是这个儿子对应在大数组上的位置，即标号；
#define  MAX    26
typedef struct TrieNode
{
	int nCount;  // 该节点前缀 出现的次数
	struct TrieNode *next[MAX]; //该节点的后续节点
} TrieNode;
TrieNode Memory[1000000]; //先分配好内存。 malloc 较为费时
int allocp = 0;
//初始化一个节点。nCount计数为1， next都为null
TrieNode * createTrieNode()
{
	TrieNode * tmp = &Memory[allocp++];
	tmp->nCount = 1;
	for (int i = 0; i < MAX; i++)
		tmp->next[i] = NULL;
	return tmp;
}

void insertTrie(TrieNode ** pRoot, char * str)
{
	TrieNode * tmp = *pRoot;
	int i = 0, k;
	//一个一个的插入字符
	while (str[i])
	{
		k = str[i] - 'a'; //当前字符应该插入的位置
		if (tmp->next[k])
		{
			tmp->next[k]->nCount++;
		}
		else
		{
			tmp->next[k] = createTrieNode();
		}

		tmp = tmp->next[k];
		i++; //移到下一个字符
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
	return tmp->nCount; //返回最后的那个字符所在节点的 nCount
}

int main(void)
{
	char s[11];
	TrieNode *Root = createTrieNode();
	while (gets(s) && s[0] != '0') //读入0 结束
	{
		insertTrie(&Root, s);
	}

	while (gets(s)) //查询输入的字符串
	{
		printf("%d\n", searchTrie(Root, s));
	}

	return 0;
}