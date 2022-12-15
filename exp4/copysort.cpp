#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define KeyType int
#define DataType int
#define FALSE 0
#define TRUE 1
#define Maxsize 100010

typedef int BOOL;

typedef struct entry {					// 数据元素
	KeyType key;						// 排序关键字
	DataType data;						// data 包含数据元素中的其他数据项
}Entry;

typedef struct list {					// 顺序表
	int n;								// 待排序数据元素数量
	Entry* D;							// 动态数组存储数据元素
}List;

int FindMin(List list, int startIndex)	// 在startIndex 至表尾范围内找到最小关键字元素下标
{
	int i, minIndex = startIndex;
	for (i = startIndex + 1; i < list.n; i++)
	{
		if (list.D[i].key < list.D[minIndex].key)
			minIndex = i;
	}
	return minIndex;
}

void Swap(Entry* D, int i, int j)		// 交换顺序表中两个元素位置
{
	Entry temp;
	if (i == j) return;
	temp = *(D + i);
	*(D + i) = *(D + j);
	*(D + j) = temp;
}
/**********************************************************************/
void SelectSort(List* list)				// 选择排序
{
	int minIndex, startIndex = 0;
	while (startIndex < list->n - 1)
	{
		minIndex = FindMin(*list, startIndex);
		Swap(list->D, startIndex, minIndex);
		startIndex++;
	}
}
/**********************************************************************/
void InsertSort(List* list)				// 插入排序
{
	int i, j;							// i 为待插入元素下标
	Entry insertItem;					// 每一趟待插入元素
	for (i = 1; i < list->n; i++)
	{
		insertItem = list->D[i];
		for (j = i - 1; j >= 0; j--)
		{
			// 不断将有序序列中元素向后移动，为待插入元素空出一个位置
			if (insertItem.key < list->D[j].key)
				list->D[j + 1] = list->D[j];
			else
				break;
		}
		list->D[j + 1] = insertItem;	// 待插入元素有序存放在有序序列中
	}
}
/**********************************************************************/
void BubbleSort(List* list)// 冒泡排序
{
	int i, j;							// i标识每趟排序范围内最后一个元素的下标，每趟排序元素下标范围为0~i;
	for (i = list->n - 1; i > 0; i--)
	{
		BOOL isSwap = FALSE;			// 标记是否发生元素交换
		for (j = 0; j < i; j++)
		{
			if (list->D[j].key > list->D[j + 1].key)
			{
				Swap(list->D, j, j + 1);
				isSwap = TRUE;
			}
		}
		if (!isSwap) break;				// 如果未发生元素交换，排序完成
	}
}

/**********************************************************************/
int Partition(List* list, int low, int high)
{
	int i = low, j = high + 1;
	Entry pivot = list->D[low];			// 分割元素
	do {
		// 定位i, j
		do i++; while (i <= high && list->D[i].key < pivot.key);
		do j--; while (list->D[j].key > pivot.key);
		if (i < j) Swap(list->D, i, j);
	} while (i < j);
	Swap(list->D, low, j);
	return j;							// j为分割下标
}
// 快速排序
void QuickSort(List* list, int low, int high)
{
	int k;
	if (low < high)						// 至少两个元素
	{
		k = Partition(list, low, high);
		QuickSort(list, low, k - 1);
		QuickSort(list, k + 1, high);
	}
}

void quick_sort(List* list)				// 快排调用函数
{
	QuickSort(list, 0, list->n - 1);
}
/**********************************************************************/
// n1和n2为两个子序列长度，low是第一个子序列第一个元素下标
void Merge(List* list, Entry* temp, int low, int n1, int n2)
{
	int i = low, j = low + n1;			// i，j初始时分别指向两个序列的第一个元素
	while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1)
	{
		if (list->D[i].key <= list->D[j].key)
			*temp++ = list->D[i++];
		else *temp++ = list->D[j++];
	}
	while (i <= low + n1 - 1)
		*temp++ = list->D[i++];			// 剩余元素复制到temp
	while (j <= low + n1 + n2 - 1)
		*temp++ = list->D[j++];			// 剩余元素复制到temp
}

void MergeSort(List* list)//归并排序
{
	Entry *temp;
	temp = (Entry*)malloc(Maxsize * sizeof(Entry));
	if (temp)
	{
		int low, n1, n2, i, size = 1;
		while (size < list->n)
		{
			low = 0;					// low是一对待合并序列中第一个序列的第一个元素下标
			while (low + size < list->n)
			{
				n1 = size;
				if (low + size * 2 < list->n)
					n2 = size;			// 第二个序列长度
				else
					n2 = list->n - low - size;
				Merge(list, temp + low, low, n1, n2);
				low += n1 + n2;			// 确定下标
			}
			for (i = 0; i < low; i++)
			{
				list->D[i] = temp[i];	// 复制结果
			}
			size *= 2;					// 子序列长度翻倍
		}
		free(temp);				// 释放临时数组
	}
}
/**********************************************************************/
void AdjustDown(Entry heap[], int current, int border)
{
	int p = current;
	int minChild;
	int temp;
	while (2*p+1<=border)
	{
		if ((2 * p + 2 <= border) && (heap[2 * p + 1].key > heap[2 * p + 2].key))
			minChild = 2 * p + 2;		// 右孩子存在，且较小
		else
			minChild = 2 * p + 1;		// 右孩子不存在，或者较大，指向左孩子
		if (heap[p].key <= heap[minChild].key)
			break;						// 若当前结点不大于其最小的孩子，则调整结束
		else
		{
			temp = heap[p].key;
			heap[p].key = heap[minChild].key;
			heap[minChild].key = temp;
			p = minChild;
		}
	}
}

void HeapSort(List* list)//堆排序
{
	int i;
	for (i = ((list->n) - 2) / 2; i >= 0; i--)
		AdjustDown(list->D, i, list->n - 1);
	for (i = list->n - 1; i > 0; i--)	// i指向堆底
	{
		Swap(list->D, 0, i);		// 交换堆底与堆顶元素
		AdjustDown(list->D, 0, i - 1);
	}
}
/**********************************************************************/
void initial(List* list)				// 初始化随机数组
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < list->n; i++)
		list->D[i].key = rand();
}

void showlist(List* list)				// 打印数组
{
	for (int i = 0; i < list->n; i++)
		printf("%d ", list->D[i].key);
}
/**********************************************************************/
int main()
{
	int testSize[4] = {500, 10000, 50000, 100000};
	List list;

	for (int i = 0; i < 4; i++)
	{
		list.D = (Entry*)malloc(Maxsize * sizeof(Entry));
		list.n = testSize[i];
		int beg, end;

		initial(&list);
		beg = clock();
		SelectSort(&list);
		end = clock();
		printf("算法: 选择排序 数据量:%d 耗时: %lf ms\n", testSize[i], (double)(end - beg) * 1000/CLOCKS_PER_SEC);

		initial(&list);
		beg = clock();
		InsertSort(&list);
		end = clock();
		printf("算法: 插入排序 数据量:%d 耗时: %lf ms\n", testSize[i], (double)(end - beg) * 1000 / CLOCKS_PER_SEC);

		initial(&list);
		beg = clock();
		BubbleSort(&list);
		end = clock();
		printf("算法: 冒泡排序 数据量:%d 耗时: %lf ms\n", testSize[i], (double)(end - beg) * 1000 / CLOCKS_PER_SEC);

		initial(&list);
		beg = clock();
		quick_sort(&list);
		end = clock();
		printf("算法: 快速排序 数据量:%d 耗时: %lf ms\n", testSize[i], (double)(end - beg) * 1000/ CLOCKS_PER_SEC);

		initial(&list);
		beg = clock();
		MergeSort(&list);
		end = clock();
		printf("算法: 归并排序 数据量:%d 耗时: %lf ms\n", testSize[i], (double)(end - beg) * 1000/ CLOCKS_PER_SEC);

		initial(&list);
		beg = clock();
		HeapSort(&list);
		end = clock();
		printf("算法: 堆排序   数据量:%d 耗时: %lf ms\n", testSize[i], (double)(end - beg) / CLOCKS_PER_SEC);
		free(list.D);
	}

	return 0;
}