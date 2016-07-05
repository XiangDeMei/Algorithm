

int lowbit(int x) //计算lowbit
{
    return x & (-x);
}
//一维
void modify(int i,int val)//将第i个元素更改为val
{  
    while(i<=MAXN)  
    {      
        a[i]+=add;    
        i+=lowbit(i); 
    }
}
int get_sum(int i)//求前i项和
{  
    int ret=0; 
    while(i!=0)  
    {       
        ret+=a[i];   
        i-=lowbit(i);   
    }  
    return ret;
}

//二维
void modify(int x,int y,int data)
{
    for(int i=x;i<MAXN;i+=lowbit(i))
        for(int j=y;j<MAXN;j+=lowbit(j))
            a[i][j]+=data;
}
int get_sum(int x,int y)
{
    int res=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            res+=a[i][j];
    return res;
}