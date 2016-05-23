#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;
typedef int DataType;
int count,sel;
void swap(DataType *x, DataType *y) //交换函数 
{
	DataType t = *x;
	*x = *y;
	*y = t;
}

void BubbleSort(DataType a[],int len) //冒泡排序 
{
	int i,j,flag,temp;
	for(i=0;i<len-1;i++)
	{
		flag=0;
		for(j=0;j<len-1-i;j++)
			if(a[j]>a[j+1])
			{
				swap(&a[j], &a[j+1]);
				flag=1;
			}
		if(flag==0)//如果没有交换则跳出循环 
			break;
	}
}

void MergeSortRec(DataType a[], DataType reg[], int left, int right,int l)
{
	//将当前表分为两部分 
	int len = right - left, mid = (len >> 1) + left;
	int left1 = left, right1 = mid;
	int left2 = mid + 1, right2 = right;
	int k = left;
	if (left >= right)
		return;
	//递归调用每一次使得局部有序 
	MergeSortRec(a, reg, left1, right1,l);
	MergeSortRec(a, reg, left2, right2,l);
	//将两个有序表合并和一个有序表 
	while (left1 <= right1 && left2 <= right2)
		reg[k++] = a[left1] < a[left2] ? a[left1++] : a[left2++];
	while (left1 <= right1)
		reg[k++] = a[left1++];
	while (left2 <= right2)
		reg[k++] = a[left2++];
	//将存在寄存数组中的数存回a数组	
	for (k = left; k <= right; k++) 
		a[k] = reg[k];	
	//输出中间过程 		
}
void MergeSort(DataType a[], int len)//归并排序 
{
	DataType reg[len];
	MergeSortRec(a, reg, 0, len - 1,len);
}

void QuickSortRec(DataType a[], int left, int right, int len) 
{
	if (left >= right)
		return;
	DataType mid = a[right];//将最后一个值设为基准记录 
	int low = left, high = right - 1;
	while (low < high)  
	{
		while (a[low] < mid && low < high)//从左到右找大于mid的记录
			low++;
		while (a[high] >= mid && low < high)//从右到左找小于mid的记录 
			high--;
		swap(&a[low], &a[high]);
	}
	if (a[low] >= a[right])//将基准记录保存到right的位置 
		swap(&a[low], &a[right]);
	else
		low++;			    	
	QuickSortRec(a, left, low - 1,len);//对左子表递归排序
	QuickSortRec(a, low + 1, right,len);//对右子表递归排序
}
void QuickSort(DataType a[], int len) //快速排序 
{
	QuickSortRec(a, 0, len - 1,len);
}

void SelectionSort(DataType a[],int len) //选择排序 
{
	int i,j;
	for(i=0;i<len-1;i++)
		for(j=i+1;j<len;j++)
			if(a[j]<a[i])
				swap(&a[j],&a[j+1]);
}

void StrInsSort(DataType a[],int len)//插入排序 
{
	int i,j;
	DataType temp;
	for(i=1;i<len;i++)
	{
		temp=a[i];//存放将待排序记录
		j=i-1;//从后向前查找插入位置，同时将已排序记录向后移动 
		while(j>=0&&a[j]>temp)
		{
			a[j+1]=a[j];
			j--;//记录后移
		}
		a[j+1]=temp;//待排记录放到合适位置
	}
}

void ShellSort(DataType a[], int len)//希尔排序 
{
	int shall, i, j;
	DataType temp;
	for (shall = len >> 1; shall > 0; shall >>= 1)//产生步长序列，并按步长序列产生子序列 
		for (i = shall; i < len; i++) //在子序列局部使用插入排序 
		{
			temp = a[i];
			for (j = i - shall; j >= 0 && a[j] > temp; j -= shall)
				a[j + shall] = a[j];
			a[j + shall] = temp;
		}
}

void menu()
{
	cout<<"       排序算法比较"<<endl;
	cout<<endl;
	cout<<" 请选择1或2"<<endl;
	cout<<" 1、小数据（10个，显示排序过程）"<<endl; 
	cout<<" 2、大数据（100K个，显示排序用时）"<<endl;  
}
int main()
{
	clock_t start,end;
	DataType a[100000];
	int i;
	menu(); 
	scanf("%d",&sel);
	if(sel==1)
	{
		count=0;
		cout<<"插入排序："<<endl;
		int b[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"最优情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		cout<<b[i]<<" ";
		cout<<endl; 
		cout<<"过程："<<endl;
		StrInsSort(b,10);  
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"插入排序："<<endl;
		int c[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"最差情况原始数据："<<endl;
		for(i=0;i<10;i++)
		cout<<c[i]<<" ";
		cout<<endl; 
		cout<<"过程："<<endl;
		StrInsSort(c,10); 
		cout<<"排序次数："<<count<<endl; 
		
		
		count=0;
		cout<<"希尔排序："<<endl;
		int b0[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"最优情况原始数据："<<endl;
		for(i=0;i<10;i++)
		cout<<b0[i]<<" ";
		cout<<endl; 
		cout<<"过程："<<endl;
		ShellSort(b0,10);
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"希尔排序："<<endl;
		int c0[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"最差情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		cout<<c0[i]<<" ";
		cout<<endl;
		cout<<"过程："<<endl;
		ShellSort(c0,10);
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"冒泡排序："<<endl;
		int b1[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"最优情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		cout<<b1[i]<<" ";
		cout<<endl;
		cout<<"过程："<<endl;
		BubbleSort(b1,10); 
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"冒泡排序："<<endl;
		int c1[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"最差情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		cout<<c1[i]<<" ";
		cout<<endl;
		cout<<"过程："<<endl;
		BubbleSort(c1,10); 
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"快速排序："<<endl;
		int b2[10];
		cout<<"最优情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		{
			b2[i]=rand();
			cout<<b2[i]<<" ";
		}
		cout<<endl;
		cout<<"过程："<<endl;
		QuickSort(b2,10); 
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"快速排序："<<endl;
		int c2[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"最差情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		cout<<c2[i]<<" ";
		cout<<endl;
		cout<<"过程："<<endl;
		QuickSort(c2,10); 
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"选择排序："<<endl;
		int b3[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"最优情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		cout<<b3[i]<<" ";
		cout<<endl;
		cout<<"过程："<<endl;
		SelectionSort(b3,10); 
		cout<<"排序次数："<<count<<endl; 
		
		count=0;
		cout<<"选择排序："<<endl;
		int c3[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"最差情况原始数据："<<endl; 
		for(i=0;i<10;i++)
		cout<<c3[i]<<" ";
		cout<<endl;
		cout<<"过程："<<endl;
		SelectionSort(c3,10); 
		cout<<"排序次数："<<count<<endl; 
		 
		count=0;
		cout<<"归并排序："<<endl;
		cout<<"原始数据："<<endl; 
		for(i=0;i<10;i++)
		{
			a[i]=rand();
			cout<<a[i]<<" ";
		}
		cout<<endl;
		cout<<"过程："<<endl;
		MergeSort(a,10); 
		cout<<"排序次数："<<count<<endl; 	
	}
	else
	{
	for(i=0;i<100000;i++)
		a[i]=rand();
	start=clock();
	StrInsSort(a,100000);
	end=clock();
	printf("StrInsSort’s run time is %lf s\n",double(end-start)/CLOCKS_PER_SEC);
	
	for(i=0;i<100000;i++)
		a[i]=rand();
	start=clock();
	ShellSort(a,100000);
	end=clock();
	printf("ShellSorts's run time is %lf s\n",double(end-start)/CLOCKS_PER_SEC);
	 
	for(i=0;i<100000;i++)
		a[i]=rand();
	start=clock();
	BubbleSort(a,100000);
	end=clock();
	printf("BubbleSort's run time is %lf s\n",double(end-start)/CLOCKS_PER_SEC);
	
	for(i=0;i<100000;i++)
		a[i]=rand();
	start=clock();
	QuickSort(a,100000);
	end=clock();
	printf("QuickSort's run time is %lf s\n",double(end-start)/CLOCKS_PER_SEC);
	
	for(i=0;i<100000;i++)
		a[i]=rand();
	start=clock();
	SelectionSort(a,100000); 
	end=clock();
	printf("SelectionSort's run time is %lf s\n",double(end-start)/CLOCKS_PER_SEC);
	
	for(i=0;i<100000;i++)
		a[i]=rand();
	start=clock();
	MergeSort(a,100000); 
	end=clock();
	printf("MergeSort's run time is %lf s\n",double(end-start)/CLOCKS_PER_SEC);
    }
	return 0;
} 
