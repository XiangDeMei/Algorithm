#define Max 100;//结点个数（最大）  
int count[Max];//记录入度  
int record[Max];//记录拓扑排序编号  
int n;//结点个数（实际）  
//count[Max]初始化为0  
bool tuopu_sort()  
{  
    int i,temp,top=-1;  
    for(i=0;i<n;i++)  
        if(count[i]==0){  
            count[i]=top;  
              top=i;  
        }  
    for(i=0;i<n;i++){  
        if(top==-1)  
            return false;  
        else{  
             temp=top;top=count[top];  
             record[i]=temp;  
             grap_down *s=p.gr[temp].po;  
             while(s){  
                 if(--count[s->number]==0){  
                     count[s->number]=top;  
                     top=s->number;  
                 }  
                 s=s->po;  
             }  
        }  
    }  
    return true;  
} 
