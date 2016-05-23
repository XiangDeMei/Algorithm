#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;
typedef int DataType;
int count,sel;
void swap(DataType *x, DataType *y) //�������� 
{
	DataType t = *x;
	*x = *y;
	*y = t;
}

void BubbleSort(DataType a[],int len) //ð������ 
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
		if(flag==0)//���û�н���������ѭ�� 
			break;
	}
}

void MergeSortRec(DataType a[], DataType reg[], int left, int right,int l)
{
	//����ǰ���Ϊ������ 
	int len = right - left, mid = (len >> 1) + left;
	int left1 = left, right1 = mid;
	int left2 = mid + 1, right2 = right;
	int k = left;
	if (left >= right)
		return;
	//�ݹ����ÿһ��ʹ�þֲ����� 
	MergeSortRec(a, reg, left1, right1,l);
	MergeSortRec(a, reg, left2, right2,l);
	//�����������ϲ���һ������� 
	while (left1 <= right1 && left2 <= right2)
		reg[k++] = a[left1] < a[left2] ? a[left1++] : a[left2++];
	while (left1 <= right1)
		reg[k++] = a[left1++];
	while (left2 <= right2)
		reg[k++] = a[left2++];
	//�����ڼĴ������е������a����	
	for (k = left; k <= right; k++) 
		a[k] = reg[k];	
	//����м���� 		
}
void MergeSort(DataType a[], int len)//�鲢���� 
{
	DataType reg[len];
	MergeSortRec(a, reg, 0, len - 1,len);
}

void QuickSortRec(DataType a[], int left, int right, int len) 
{
	if (left >= right)
		return;
	DataType mid = a[right];//�����һ��ֵ��Ϊ��׼��¼ 
	int low = left, high = right - 1;
	while (low < high)  
	{
		while (a[low] < mid && low < high)//�������Ҵ���mid�ļ�¼
			low++;
		while (a[high] >= mid && low < high)//���ҵ�����С��mid�ļ�¼ 
			high--;
		swap(&a[low], &a[high]);
	}
	if (a[low] >= a[right])//����׼��¼���浽right��λ�� 
		swap(&a[low], &a[right]);
	else
		low++;			    	
	QuickSortRec(a, left, low - 1,len);//�����ӱ�ݹ�����
	QuickSortRec(a, low + 1, right,len);//�����ӱ�ݹ�����
}
void QuickSort(DataType a[], int len) //�������� 
{
	QuickSortRec(a, 0, len - 1,len);
}

void SelectionSort(DataType a[],int len) //ѡ������ 
{
	int i,j;
	for(i=0;i<len-1;i++)
		for(j=i+1;j<len;j++)
			if(a[j]<a[i])
				swap(&a[j],&a[j+1]);
}

void StrInsSort(DataType a[],int len)//�������� 
{
	int i,j;
	DataType temp;
	for(i=1;i<len;i++)
	{
		temp=a[i];//��Ž��������¼
		j=i-1;//�Ӻ���ǰ���Ҳ���λ�ã�ͬʱ���������¼����ƶ� 
		while(j>=0&&a[j]>temp)
		{
			a[j+1]=a[j];
			j--;//��¼����
		}
		a[j+1]=temp;//���ż�¼�ŵ�����λ��
	}
}

void ShellSort(DataType a[], int len)//ϣ������ 
{
	int shall, i, j;
	DataType temp;
	for (shall = len >> 1; shall > 0; shall >>= 1)//�����������У������������в��������� 
		for (i = shall; i < len; i++) //�������оֲ�ʹ�ò������� 
		{
			temp = a[i];
			for (j = i - shall; j >= 0 && a[j] > temp; j -= shall)
				a[j + shall] = a[j];
			a[j + shall] = temp;
		}
}

void menu()
{
	cout<<"       �����㷨�Ƚ�"<<endl;
	cout<<endl;
	cout<<" ��ѡ��1��2"<<endl;
	cout<<" 1��С���ݣ�10������ʾ������̣�"<<endl; 
	cout<<" 2�������ݣ�100K������ʾ������ʱ��"<<endl;  
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
		cout<<"��������"<<endl;
		int b[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"�������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		cout<<b[i]<<" ";
		cout<<endl; 
		cout<<"���̣�"<<endl;
		StrInsSort(b,10);  
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"��������"<<endl;
		int c[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"������ԭʼ���ݣ�"<<endl;
		for(i=0;i<10;i++)
		cout<<c[i]<<" ";
		cout<<endl; 
		cout<<"���̣�"<<endl;
		StrInsSort(c,10); 
		cout<<"���������"<<count<<endl; 
		
		
		count=0;
		cout<<"ϣ������"<<endl;
		int b0[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"�������ԭʼ���ݣ�"<<endl;
		for(i=0;i<10;i++)
		cout<<b0[i]<<" ";
		cout<<endl; 
		cout<<"���̣�"<<endl;
		ShellSort(b0,10);
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"ϣ������"<<endl;
		int c0[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		cout<<c0[i]<<" ";
		cout<<endl;
		cout<<"���̣�"<<endl;
		ShellSort(c0,10);
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"ð������"<<endl;
		int b1[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"�������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		cout<<b1[i]<<" ";
		cout<<endl;
		cout<<"���̣�"<<endl;
		BubbleSort(b1,10); 
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"ð������"<<endl;
		int c1[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		cout<<c1[i]<<" ";
		cout<<endl;
		cout<<"���̣�"<<endl;
		BubbleSort(c1,10); 
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"��������"<<endl;
		int b2[10];
		cout<<"�������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		{
			b2[i]=rand();
			cout<<b2[i]<<" ";
		}
		cout<<endl;
		cout<<"���̣�"<<endl;
		QuickSort(b2,10); 
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"��������"<<endl;
		int c2[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		cout<<c2[i]<<" ";
		cout<<endl;
		cout<<"���̣�"<<endl;
		QuickSort(c2,10); 
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"ѡ������"<<endl;
		int b3[10]={0,1,2,3,4,5,6,7,8,9};
		cout<<"�������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		cout<<b3[i]<<" ";
		cout<<endl;
		cout<<"���̣�"<<endl;
		SelectionSort(b3,10); 
		cout<<"���������"<<count<<endl; 
		
		count=0;
		cout<<"ѡ������"<<endl;
		int c3[10]={9,8,7,6,5,4,3,2,1,0};
		cout<<"������ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		cout<<c3[i]<<" ";
		cout<<endl;
		cout<<"���̣�"<<endl;
		SelectionSort(c3,10); 
		cout<<"���������"<<count<<endl; 
		 
		count=0;
		cout<<"�鲢����"<<endl;
		cout<<"ԭʼ���ݣ�"<<endl; 
		for(i=0;i<10;i++)
		{
			a[i]=rand();
			cout<<a[i]<<" ";
		}
		cout<<endl;
		cout<<"���̣�"<<endl;
		MergeSort(a,10); 
		cout<<"���������"<<count<<endl; 	
	}
	else
	{
	for(i=0;i<100000;i++)
		a[i]=rand();
	start=clock();
	StrInsSort(a,100000);
	end=clock();
	printf("StrInsSort��s run time is %lf s\n",double(end-start)/CLOCKS_PER_SEC);
	
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
