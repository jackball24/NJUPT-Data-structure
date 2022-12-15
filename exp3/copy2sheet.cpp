#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define _CRT_SECURE_NO_WARNINGS 1
#define ERROR 0;
#define OK 1;
using namespace std;

typedef int ElemType;
typedef int Status;

typedef struct eNode {
	int adjVex;							// 与任意顶点u相邻接的顶点
	ElemType w;							// 边权
	struct eNode* nextArc;				// 指向下一个边结点
}ENode;
typedef struct lGraph {
	int n;								// 图的结点数
	int e;								// 图边数
	ENode** a;							// 指向一维指针数组
}LGraph;

Status Init(LGraph* lg, int nSize)
{
	int i;
	lg->n = nSize;
	lg->e = 0;
	lg->a = (ENode**)malloc(nSize * sizeof(ENode*));
	if(!lg->a)
		return ERROR;
	for (int i = 0; i < lg->n; i++)
	{
		lg->a[i] = NULL;				// 将指针数组置空
	}
	return OK;
}

void Destroy(LGraph* lg)
{
	int i;
	ENode* p, * q;
	for (int i = 0; i < lg->n; i++)
	{
		p = lg->a[i];					// 指针p指向顶点i的单链表的第一个边结点
		q = p;
		while (p)						// 释放顶点 i 的单链表的所有边结点
		{
			p = p->nextArc;
			free(q);
			q = p;
		}
	}
	free(lg->a);					// 释放一维指针数组a
}

Status Exist(LGraph* lg, int u, int v)
{
	ENode* p;
	if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v)
	{
		return ERROR;
	}
	p = lg->a[u];						// p指向u的第一个边结点
	while (p && p->adjVex != v) p = p->nextArc;
	if (!p) return ERROR;
	return OK;
}

Status Insert(LGraph* lg, int u, int v, ElemType w)
{
	ENode* p;
	if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
	if (Exist(lg, u, v)) return ERROR;
	p = (ENode*)malloc(sizeof(ENode));
	p->adjVex = v;
	p->w = w;
	p->nextArc = lg->a[u];				// 插入单链表的最前面
	lg->a[u] = p;
	lg->e++;
	return OK;
}

Status Remove(LGraph* lg, int u, int v)
{
	ENode* p, * q;
	if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v)
	{
		return ERROR;
	}
	p = lg->a[u], q = NULL;
	while (p && p->adjVex != v)			// 查找是否存在
	{
		q = p;
		p = p->nextArc;
	}
	if (!p) return ERROR;
	if (q) q->nextArc = p->nextArc;		// 删除边
	else lg->a[u] = p->nextArc;
	free(p);
	lg->e--;
	return OK;
}

void DFS(int v, int visited[], LGraph g)
{
	ENode* w;
	printf("%d ", v);				// 访问顶点v
	visited[v] = 1;						// 标记已访问
	for (w = g.a[v]; w; w = w->nextArc)
	{
		if (!visited[w->adjVex])		// 如果未被访问则DFS
			DFS(w->adjVex, visited, g);
	}
}

void DFSGraph(LGraph g)
{
	int i;
	int* visited = (int*)malloc(g.n * sizeof(int));
	for (int i = 0; i < g.n; i++)
	{
		visited[i] = 0;					// 初始化visited数组
	}
	for (int i = 0; i < g.n; i++)		// 遍历i的邻接结点
	{
		if (!visited[i]) DFS(i, visited, g);
	}
	printf("\n");
	free(visited);
}

void BFS(int v, int visited[], LGraph g)
{
	ENode* w;
	queue<int> q;
	visited[v] = 1;						// 标记访问
	printf("%d ", v);
	q.push(v);						// 入队
	while (q.size())
	{
		int t = q.front();				// 取出队首
		q.pop();
		for (w = g.a[t]; w; w = w->nextArc)
		{
			if (!visited[w->adjVex])	// 遍历w的邻接点
			{
				visited[w->adjVex] = 1;
				printf("%d ", w->adjVex);
				q.push(w->adjVex);
			}
		}
	}
}

void BFSGraph(LGraph g)
{
	int i;
	int* vistied = (int*)malloc(g.n * sizeof(int));
	for (int i = 0; i < g.n; i++)
	{
		vistied[i] = 0;					// 初始化visited数组
	}
	for (int i = 0; i < g.n; i++)		// 遍历每一结点
	{
		if (!vistied[i]) BFS(i, vistied, g);
	}
	printf("\n");
	free(vistied);
}

int main()
{
    LGraph g;
    int i, u, v, enode, edge;
    ElemType w;
    printf("请输入顶点数（编号0~size-1）:");
    scanf_s("%d", &enode);
    Init(&g, enode);
    printf("请输入边的数量:");
    scanf_s("%d", &edge);
    for (i = 0; i < edge; i++) {
        printf("请输入 起点/终点/边的权值:");
        scanf_s("%d%d%d", &u, &v, &w);
        Insert(&g, u, v, w);
    }
    printf("DFS:\n");
    DFSGraph(g);
    printf("\nBFS:\n");
    BFSGraph(g);
    return 0;
}