#include<stdio.h>
#include<stdlib.h>//用到rand()函数
#include<time.h>   //用到clock()函数
using namespace std;
#include<algorithm>
#include<cmath>
#define KeyType int
#define DataType int
#include<iostream>
#include <cassert>
#define N 10000
#define MAX 32768
// 99999

int MyRandom() {
    int a0, a = 0;
    a0 = rand() % 10000;
    a = rand() % 10;
    
    
    return a * 10000 + a0;
}

typedef struct entry           //数据元素
{
    KeyType key;				//排序关键字，KeyType应该为可比较类型
    DataType data;				//data包含数据元素中的其他数据项
}Entry;

typedef struct list {				//顺序表
    int n;				//待排序数据元素数量
    Entry* D;		//静态数组存储数据元素
}List;

typedef struct Peer
{
    unsigned int start;
    unsigned int end;
}Peer;

typedef struct Stack
{
    Peer* data;
    int   top;
}Stack;


//简单选择排序
void SelectSort(List* list) {
    int small, i, j;
    // 要排序 n-1 次
    for (i = 0; i < list->n - 1; i++) {
        small = i;                                    //标记每次第一位元素下标
        for (j = i + 1; j < list->n; j++) {
            if (list->D[j].key < list->D[small].key) {  //按非递减顺序比较大小
                small = j;
            }
        }
        if (small != i) {   
            swap(list->D[i], list->D[small]);
        }
    }
}

//直接插入排序
void InsertSort(List* list) {
    int i, j;  
    //i标识待插入元素下标
    for (i = 1; i < list->n; i++) {
        Entry insertItem = list->D[i];     //标记每次第一位元素
        for (j = i - 1; j >= 0; j--) {
            //不断将有序序列中元素向后移动,为待插入元素空出一个位置
            if (insertItem.key < list->D[j].key) {
                list->D[j + 1] = list->D[j];
            }
            else break;
        }
        list->D[j + 1] = insertItem;          //待插入元素有序存放至有序序列中
    }
}

//冒泡排序
void BubbleSort(List* list) {
    int i, j;                    //i标识每趟排序范围最后一个元素下标,每趟排序元素下标范围是0~i
    for (i = list->n - 1; i > 0; i--) {
        bool isSwap = false;   
        for (j = 0; j < i; j++) {
            if (list->D[j].key > list->D[j + 1].key) {
                swap(list->D[j], list->D[j + 1]);
                isSwap = true;
            }
        }
        if (!isSwap) break;     //如果本趟排序没有发生元素交换,排序完成
        
    }
}


//Merge(合并)函数
void Merge(List* list, int Temp[], int i1, int j1, int i2, int j2, int* k) {
    int i = i1, j = i2;
    while ((i <= j1) && (j <= j2)) {                       //若两个子序列都不空,则循环
        if (list->D[i].key <= list->D[j].key) {
            Temp[(*k)++] = list->D[i++].key;         //将较小元素存入Temp[*k]
        }
        else Temp[(*k)++] = list->D[j++].key;
    }
    while (i <= j1) Temp[(*k)++] = list->D[i++].key;  //将子序列1中剩余元素存入Temp
    while (j <= j2) Temp[(*k)++] = list->D[j++].key;  //将子序列2中剩余元素存入Temp
}


// 两路合并函数
void MergeSort(List* list) {
    int Temp[N];
    int i1, j1, i2, j2, i, k, size = 1;              //i1,j1和i2,j2分别是两个子序列的上,下界
    while (size < list->n) {
        i1 = 0;
        k = 0;
        while (i1 + size < list->n) {              //若i1+size < n,则说明存在两个子序列,需要再两两合并
            i2 = i1 + size;                      //确定子序列2的下界和子序列1的上界
            j1 = i2 - 1;
            if (i2 + size - 1 > list->n - 1) {         //设置子序列2的上界
                j2 = list->n - 1;
            }
            else j2 = i2 + size - 1;
            Merge(list, Temp, i1, j1, i2, j2, &k);  //合并相邻两个子序列
            i1 = j2 + 1;                        //确定下一次合并第一个子序列的下界
        }
        for (i = 0; i < k; i++) {
            list->D[i].key = Temp[i];
        }
        size *= 2;                            //子序列长度扩大一倍
    }
}

void Init(List* list) {
    list->n = N;
    list->D = (Entry*)malloc(sizeof(Entry) * list->n);
    for (int i = 0; i < list->n; i++) {
        list->D[i].key = i;
    }
    for (int j = 0; j < N; j++) {
        int l, r;
        if (N > MAX) {
            l = MyRandom();
            r = MyRandom();
        }
        else {
            l = rand() % N;
            r = rand() % N;
        }
        swap(list->D[l].key, list->D[r].key);
    }
}

void Print(List* list) {
    for (int i = 0; i < list->n; i++) {
        cout << list->D[i].key << "\t";
        if (i % 20 == 19)
            cout << endl;
    }
}

void AdjustDown(List* list, int r, int j)
{
    int child = 2 * r + 1;
    Entry temp = list->D[r];
    while (child <= j)
    {
        if ((child < j) && (list->D[child].key < list->D[child+1].key))
            child++;
        if (temp.key >= list->D[child].key)
            break;
        list->D[(child - 1) / 2] = list->D[child];
        child = 2 * child + 1;
    }
    list->D[(child - 1) / 2] = temp;
}
void HeapSort(List* list)
{
    int n = list->n;
    for (int i = (n - 2) / 2; i > -1; i--)
        AdjustDown(list, i, n - 1);
    for (int i = n - 1; i > 0; i--)
    {
        swap(list->D[0], list->D[i]);
        AdjustDown(list, 0, i - 1);
    }
}



int Partition(List* list, int low, int high) {
    int i = low, j = high + 1;
    Entry pivot = list->D[low];                 //pivot是分割元素
    do {
        do i++;
        while (list->D[i].key < pivot.key);      //i前进
        do j--;
        while (list->D[j].key > pivot.key);      //j前进
        if (i < j) swap(list->D[i], list->D[j]);
    } while (i < j);
    swap(list->D[low], list->D[j]);
    return j;                                   //此时j是分割元素下标
}

void QuickSortNoR(List* list)
{
    int len = N;
    int size = (int)(log((double)len) / log((double)2)) + 1;
    Stack st;
    st.data = (Peer*)malloc(sizeof(Peer) * size);
    assert(st.data != NULL);
    st.top = 0;

    Peer peer;
    peer.start = 0;
    peer.end = len - 1;
    st.data[st.top++] = peer;

    while (st.top != 0)
    {
        peer = st.data[--st.top];
        int mod = Partition(list, peer.start, peer.end);

        if (peer.end - mod > 1)
        {
            Peer new_peer = { mod + 1, peer.end };
            st.data[st.top++] = new_peer;
        }
        if (mod - peer.start > 1)
        {
            Peer new_peer = { peer.start, mod - 1 };
            st.data[st.top++] = new_peer;
        }
    }
}

int main() {
    int begintime, endtime;
    cout << "原序列为：" << endl;
    List* list = new List;
    //Init(list);
    //Print(list);

    
    list = new List;
    Init(list);
    begintime = clock();
    cout << endl << "简单选择排序" << endl;           // 9200ms
    SelectSort(list);
    endtime = clock();
    printf("\nRunning Time：%dms\n", endtime - begintime);
    cout << endl;

    
    list = new List;
    Init(list);
    begintime = clock();
    cout << "直接插入排序" << endl;            // 5300ms
    InsertSort(list);
    endtime = clock();
    printf("\nRunning Time：%dms\n", endtime - begintime);
    cout << endl;

    list = new List;
    Init(list);
    begintime = clock();
    cout << "冒泡排序" << endl;
    BubbleSort(list);
    endtime = clock();
    printf("\nRunning Time：%dms\n", endtime - begintime);
    cout << endl;   

    
    list = new List;
    Init(list);
    begintime = clock();
    cout << "快速排序" << endl;
    QuickSortNoR(list);
    endtime = clock();
    printf("\nRunning Time：%dms\n", endtime - begintime);
    cout << endl;      

    list = new List;
    Init(list);
    begintime = clock();
    cout << "两路合并排序" << endl;
    MergeSort(list);
    endtime = clock();
    printf("\nRunning Time：%dms\n", endtime - begintime);
    cout << endl;    

    list = new List;
    Init(list);
    begintime = clock();
    cout << "堆排序" << endl;
    HeapSort(list);
    endtime = clock();
    printf("\nRunning Time：%dms\n", endtime - begintime);
    cout << endl;

    return 0;
}

/*  简单选择排序、
    直接插入排序、
    冒泡排序、
    快速排序、
    两路合并排序
    堆排序。    */ 




/*  简单选择排序、
    直接插入排序、
    冒泡排序、
    快速排序、
    两路合并排序
    堆排序。    */ 
 

