#include<iostream>
#include<cstdio>
using namespace std;
int n,a[8],con;
void disp()
{
	for (int i = 0; i < 8; i++)
		printf("%d", a[i]+1);
	printf("\n");
}
void search(int k){
	if(k==8) {
		con++;
		if(con==n){
			disp();
		}
	}
	else{
		for(int i=0;i<8;i++){
			int flag = 1;
			a[k]=i;
			for(int j=0;j<k;j++)
			if(a[k]==a[j]||k-a[k]==j-a[j]||k+a[k]==j+a[j]){
				flag=0;
				break;
			}
			if(flag) search(k+1);
		}
	}
} 
int main(){
	scanf("%d",&n);
	con=0;
	search(0);
	return 0;
}



