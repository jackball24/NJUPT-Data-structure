#include<stdio.h>
#include<stdlib.h>

typedef struct list{
	int n;
	int maxLength;
	int* element;
}SeqList;

//初始化
int Init(SeqList* L, int mSize)
{
	L->maxLength = mSize;
	L->n = 0;
	L->element = (int*)malloc(sizeof(int) * mSize);
	if (!L->element)
		return 0;
	return 1;
}

//查找
int Find(SeqList L, int i, int* x)
{
	if (i < 0 || i > L.n-1)
		return 0;
	*x = L.element[i];
	return 1;
}

//插入
int Insert(SeqList* L, int i, int x)
{
	int j;
	if (i < -1 || i > L->n - 1)
		return 0;
	if (L->n == L->maxLength)
		return 0;
	for (j = L->n - 1; j > i; j--)
		L->element[j + 1] = L->element[j];
	L->element[i + 1] = x;
	L->n=L->n+1;
	return 1;
}

//删除
int Delete(SeqList* L, int i)
{
	int j;
	if (i < -1 || i >= L->n - 1)
		return 0;
	if (L->n == 0)
		return 0;
	for (j = i + 1; j < L->n; j++)
		L->element[j - 1] = L->element[j];
	L->n--;
	return 1;
}

//输出
int Output(SeqList* L)
{
	int i;
	if (L->n == 0)
		return 0;
	for (i = 0; i < L->n; i++)
		printf("%d ", L->element[i]);
	printf("\n");
	return 1;
}

//撤销
void Destroy(SeqList* L)
{
	L->n = 0;
	L->maxLength = 0;
	free(L->element);
}

int main()
{
	int i,n,m;
	SeqList list;
	Init(&list, 10);
	for (i = 0; i < 10; i++)
		Insert(&list, i - 1,i);
	printf("初始化:\n");
	Output(&list);
	printf("分别输入删除和插入元素8的位置：");
	scanf("%d %d",&n,&m);
	Delete(&list, n-1);
	printf("删除第%d个元素后的线性表为:\n",n);
	Output(&list);
	Insert(&list, m-1, 8);
	printf("在第%d个元素后插入8:\n",m);
	Output(&list);
	Destroy(&list);

}

