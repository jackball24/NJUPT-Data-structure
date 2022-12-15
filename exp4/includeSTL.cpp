#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <algorithm>
#define size 10000//数组大小
using namespace std;
 
const int cnt=50;     //重复执行次数
 
int a[size+10];
 
void Swap(int &x,int &y)
{
    int tmp=x;
    x=y;
    y=tmp;
}
 
 
 
 
 
 
void Menu()
{
    system("cls");
    printf("---------------------------------内排序测试系统------------------------------\n\n\n");
    printf("--------------------------------1.简单选择排序-------------------------------\n");
    printf("--------------------------------2.直接插入排序-------------------------------\n");
    printf("--------------------------------3.冒泡排序-----------------------------------\n");
    printf("--------------------------------4.快速排序-----------------------------------\n");
    printf("--------------------------------5.改进的快速排序-----------------------------\n");
    printf("--------------------------------6.STL库的快速排序----------------------------\n");
    printf("--------------------------------7.两路合并排序-------------------------------\n");
    printf("--------------------------------8.堆排序-------------------------------------\n");
    printf("--------------------------------9.分别运行以上所有排序，给出对比---------\n");
    printf("--------------------------------0.退出系统-----------------------------------\n");
    printf("\n\n\n                    输入你的选择:");
}
 
void SeleteSort()
{
    int i;
    printf("\n正在进行%d次简单选择排序......\n",cnt);
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
        for(i=0;i<size-1;i++)
        {
            int index=i;
            for(int j=i+1;j<size;j++)
            {
                if(a[j]<a[index])
                {
                    index=j;
                }
            }
            Swap(a[i],a[index]);
        }
    }
}
 
void InsertSort()
{
    int i;
    printf("\n正在进行%d次插入排序......\n",cnt);
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
        for(i=1;i<size;i++)
        {
            int j=i;
            int tmp=a[i];
            while(j>0&&tmp<a[j-1])
            {
                a[j]=a[j-1];
                j--;
            }
            a[j]=tmp;
        }
    }
}
 
void BubbleSort()
{
    int i,j,last;
    printf("\n正在进行%d次冒泡排序......\n",cnt);
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
        i=size-1;
        while(i>0)
        {
            last=0;
            for(j=0;j<i;j++)
            {
                if(a[j+1]<a[j])
                {
                    Swap(a[j],a[j+1]);
                    last=j;
                }
            }
            i=last;
        }
    }
}
 
void Qsort(int left,int right)
{
    int i=left,j=right+1;
    if(left<right)
    {
        do
        {
            do
            {
                i++;
            }while(a[i]<a[left]);
            do
            {
                j--;
            }while(a[j]>a[left]);
            if(i<j) Swap(a[i],a[j]);
        }while(i<j);
        Swap(a[left],a[j]);
        Qsort(left,j-1);
        Qsort(j+1,right);
    }
}
 
void QuickSort()
{
    printf("\n正在进行%d次快速排序......\n",cnt);
    a[size]=100000000;
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(int i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
        Qsort(0,size-1);
//                for(int i=0;i<10;i++)
//        {
//            printf("%d ",a[i]);
//        }
//        printf("\n");
    }
}
 
 
struct note
{
    int left;
    int right;
    note(int a,int b)
    {
        left=a;
        right=b;
    }
};
 
void ImprovedQuickSort()   //改善的快速排序,用局部栈代替系统栈,并将A[(left+right)/2]作为分割元素
{
    printf("\n正在进行%d次改善版本的快速排序......\n",cnt);
    a[size]=100000000;
    int i,j;
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(int i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
        stack<note> S;
        note tmp(0,size-1);
        S.push(tmp);
        while(!S.empty())
        {
            tmp=S.top();
            S.pop();
            int left=tmp.left;
            int right=tmp.right;
            if(left<right)
            {
                Swap(a[left],a[(left+right)/2]);
                i=left;
                j=right+1;
                do
                {
                    do
                    {
                        i++;
                    }while(a[i]<a[left]);
                    do
                    {
                        j--;
                    }while(a[j]>a[left]);
                    if(i<j) Swap(a[i],a[j]);
                }while(i<j);
                Swap(a[left],a[j]);
                if(left<j-1)
                {
                    note t1(left,j-1);
                    S.push(t1);
                }
                if(j+1<right)
                {
                    note t2(j+1,right);
                    S.push(t2);
                }
            }
        }
 
    }
}
 
 
void STLsort()
{
    printf("\n正在进行%d次STL库函数sort快速排序......\n",cnt);
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(int i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
        sort(a,a+size);
    }
}
 
int tmp[size];
void Merge(int i1,int j1,int i2,int j2)
{
    int i,j,k;
    i=i1;
    j=i2;
    k=0;
    while(i<=j1&&j<=j2)
    {
        if(a[i]<=a[j]) tmp[k++]=a[i++];
        else tmp[k++]=a[j++];
    }
    while(i<=j1) tmp[k++]=a[i++];
    while(j<=j2) tmp[k++]=a[j++];
    for(i=0;i<k;i++) a[i1++]=tmp[i];
}
 
 
 
 
void MergeSort()
{
    printf("\n正在进行%d次两路合并排序排序......\n",cnt);
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(int i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
 
        int i1,i2,j1,j2;
        int Size=1;
        while(Size<size)
        {
            i1=0;
            while(i1+Size<size)
            {
                i2=i1+Size;
                j1=i2-1;
                if(i2+Size-1>size-1)
                {
                    j2=size-1;
                }
                else
                {
                    j2=i2+Size-1;
                }
                Merge(i1,j1,i2,j2);
                i1=j2+1;
            }
            Size*=2;
        }
    }
}
 
 
 
void AdjustDown(int r,int j)
{
    int ch=2*r+1;
    int temp=a[r];
    while(ch<=j)
    {
        if(ch<j && a[ch]<a[ch+1]) ch++;
        if(temp>=a[ch]) break;
        a[(ch-1)/2]=a[ch];
        ch=2*ch+1;
    }
    a[(ch-1)/2]=temp;
}
 
 
 
 
void HeapSort()
{
    int i;
    printf("\n正在进行%d次堆排序......\n",cnt);
    for(int k=0;k<cnt;k++)
    {
        srand(time(NULL)+k*10);
        for(i=0;i<size;i++)
        {
            a[i]=rand();   //rand()范围是0-32767
        }
        for(i=(size-2)/2;i>=0;i--)
        {
            AdjustDown(i,size-1);
        }
        for(i=size-1;i>0;i--)
        {
            Swap(a[0],a[i]);
            AdjustDown(0,i-1);
        }
//        for(int i=0;i<10;i++)
//        {
//            printf("%d ",a[i]);
//        }
//        printf("\n");
    }
}
 
 
 
 
 
 
void SortOne(int choice)
{
    system("cls");
    printf("--------------------------------单个排序测试-------------------------------\n\n\n");
    clock_t StartTime,EndTime;
    printf("%d 个数据,进行 %d 次排序,数据大小范围 0~32767\n\n开始排序，并开始计时......\n\n",size,cnt);
    StartTime=clock();
    switch (choice)
    {
        case 1:
            SeleteSort();
            break;
        case 2:
            InsertSort();
            break;
        case 3:
            BubbleSort();
            break;
        case 4:
            QuickSort();
            break;
        case 5:
            ImprovedQuickSort();
            break;
        case 6:
            STLsort();
            break;
        case 7:
            MergeSort();
            break;
        case 8:
            HeapSort();
            break;
    }
    EndTime=clock();
    double len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;
    printf("排序完成,停止计时,一共花费时间为 %.3f 秒\n",len);
    system("pause");
}
 
 
 
 
void SortAll()
{
    system("cls");
    printf("--------------------------------排序对比测试-------------------------------\n\n\n");
    printf("%d 个数据,进行 %d 次排序,数据大小范围 0~32767\n\n",size,cnt);
    clock_t StartTime,EndTime;
    double record[15];
    StartTime=clock();
    SeleteSort();
    EndTime=clock();
    double len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[0]=len;
    printf("时间%.3f秒\n",len);
    StartTime=clock();
    InsertSort();
    EndTime=clock();
    len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[1]=len;
    printf("时间%.3f秒\n",len);
    StartTime=clock();
    BubbleSort();
    EndTime=clock();
    len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[2]=len;
    printf("时间%.3f秒\n",len);
    StartTime=clock();
    QuickSort();
    EndTime=clock();
    len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[3]=len;
    printf("时间%.3f秒\n",len);
    StartTime=clock();
    ImprovedQuickSort();
    EndTime=clock();
    len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[4]=len;
    printf("时间%.3f秒\n",len);
    StartTime=clock();
    STLsort();
    EndTime=clock();
    len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[5]=len;
    printf("时间%.3f秒\n",len);
    StartTime=clock();
    MergeSort();
    EndTime=clock();
    len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[6]=len;
    printf("时间%.3f秒\n",len);
    StartTime=clock();
    HeapSort();
    EndTime=clock();
    len=(double(EndTime-StartTime))/CLOCKS_PER_SEC;;
    record[7]=len;
    printf("时间%.3f秒\n\n",len);
    double maxx=-1,minn=1000;
    for(int i=0;i<8;i++)
    {
        if(record[i]>maxx) maxx=record[i];
        if(record[i]<minn) minn=record[i];
    }
    printf("最快的%.3f秒,最慢的%.3f秒\n",minn,maxx);
    system("pause");
}
 
 
int main()
{
    int choice;
    while(1)
    {
        Menu();
        cin>>choice;
        if(choice>=1&&choice<=8)
        {
            SortOne(choice);
        }
        else if(choice==9)
        {
            SortAll();
        }
        else if(choice==0)
        {
            return 0;
        }
        else
        {
            cout<<"-------------------------输入有误--------------------------------"<<endl;
            system("pause");
        }
    }
    return 0;
}