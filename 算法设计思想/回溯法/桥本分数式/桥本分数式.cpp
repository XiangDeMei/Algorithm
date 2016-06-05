#include<stdio.h>
#include<cstdlib>
using namespace std;
int main()
{

    int flag,i,k,a[10],n=9;
    long m1, m2, m3;
    i = 1;
    a[1] = 1;
    s = 0;
    while (1)
    {
        flag=1;
        for(k=i-1;k>=1;k--)
    		if(a[i]==a[k])
            	{
               	 	flag=0;
           		}
        if(flag&&i==n&&a[1]<a[4])
        {
            m1 = a[2] * 10 + a[3];
            m2 = a[5] * 10 + a[6];
            m3 = a[8] * 10 + a[9];
            if(a[1]*m2 * m3 + a[4]*m1 * m3 == a[7]*m1 * m2)
            {
               	printf("%d/%d+%d/%d=%d/%d\n",a[1],m1,a[4],m2,a[7],m3);
            }
        }
        if(i<n&& flag)
        {
            i++;  
            a[i]=1;
            continue;
        }
        while(a[i]==n&&i>1) i--;
        if(a[i] ==n&&i==1) break;
        else a[i]++; 
    }
    return 0;
}
