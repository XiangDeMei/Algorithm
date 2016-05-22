#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

typedef struct TreeNode
{
	char c;
	struct TreeNode *Lchild;
	struct TreeNode *Rchild;
}TreeNode,*BinTree;

BinTree insert(BinTree &t, char ch)  
{  		
	if(t==NULL){
		BinTree p = new TreeNode;
        p->c = ch;
        p->Lchild = NULL;
        p->Rchild = NULL;
		t = p;
	}
	else if(ch < t->c){
		 t->Lchild = insert(t->Lchild, ch);
	}
	else{
	   	 t->Rchild = insert(t->Rchild, ch);   
	}
	return t;
} 
void Pre(BinTree t)
{
	if(t!=NULL)
	{
		printf("%c",t->c);
		Pre(t->Lchild);
		Pre(t->Rchild);
	}
	return ;
}
int main()
{
	BinTree root;
	string s;
	while(cin>>s){
		root = NULL;
		for(int i = 0; i < s.size(); i++){
		root = insert(root,s[i]);
  		}
		Pre(root);
		printf("\n");
	}
	return 0;
}


