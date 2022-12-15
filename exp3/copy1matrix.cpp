#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define _CRT_SECURE_NO_WARNINGS 1
#define error 0;
#define ok 1;
using namespace std;
typedef int status;
typedef int elemtype;
typedef struct mgraph {
	elemtype** a;										// 邻接矩阵
	int n;												// 图的当前顶点数
	int e;												// 图的当前边数
	elemtype noedge;									// 两顶点无边时的值
}mgraph;

status init(mgraph* mg, int nsize, elemtype noedgevalue)
{
	int i, j;
	mg->n = nsize;										// 初始化顶点数
	mg->e = 0;											// 初始化时没有边
	mg->noedge = noedgevalue;							// 初始化时没有边的取值
	mg->a = (elemtype**)malloc(nsize * sizeof(elemtype*));
	if (!mg->a)
		return error;
	for (int i = 0; i < mg->n; i++)						// 动态生成二维数组
	{
		mg->a[i] = (elemtype*)malloc(nsize * sizeof(elemtype));
		for (int j = 0; j < mg->n; j++) mg->a[i][j] = mg->noedge;
		mg->a[i][i] = 0;
	}
	return ok;
}

void destory(mgraph* mg)
{
	int i;
	for (int i = 0; i < mg->n; i++)
		free(mg->a[i]);							// 释放n个一维数组的存储空间
	free(mg->a);									// 释放一维指针数组的存储空间
}

status exist(mgraph* mg, int u, int v)
{
	if (u < 0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noedge)
	{
		return error;
	}
	return ok;
}

status insert(mgraph* mg, int u, int v, elemtype w)
{
	if (u < 0 || v < 0 || u > mg->n - 1 || u == v)
	{
		return error;
	}
	if (mg->a[u][v] != mg->noedge)
	{
		return error;									// 若待插入边已存在，则返回出错信息
	}
	mg->a[u][v] = w;									// 插入新边
	mg->e++;
	return ok;
}

status remove(mgraph* mg, int u, int v)
{
	if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
	{
		return error;
	}
	if (mg->a[u][v] == mg->noedge)						// 若删除边不存在，则返回错误信息
		return error;
	mg->a[u][v] = mg->noedge;							// 删除边
	mg->e--;
	return ok;
}

void dfs(int v, int visited[], mgraph g)
{
	printf("%d ", v);
	visited[v] = 1;										// 访问顶点v，并记录
	for (int j = 0; j < g.n; j++)						// 遍历v的邻接点
	{
		if (g.a[v][j] != 0 && g.a[v][j] != g.noedge && visited[j] == 0)
			dfs(j, visited, g);						// 若未被访问则dfs访问
	}
}

void dfs_mgraph(mgraph g)
{
	int i;
	int* visited = (int*)malloc(g.n * sizeof(int));// 生成标记数组visited
	for (int i = 0; i < g.n; i++)
		visited[i] = 0;									// 初始化visited数组
	for (int i = 0; i < g.n; i++)						// 逐一访问每个顶点
	{
		if (!visited[i])
			dfs(i, visited, g);
	}
	free(visited);
	printf("\n");
}

void bfs(int v, int vistied[], mgraph g)
{
	queue<int> q;										// 初始化队列
	vistied[v] = 1;
	printf("%d ", v);								// 访问顶点v
	q.push(v);										// v入队
	while (q.size())
	{
		int t = q.front();								// 取出队首
		q.pop();

		for (int j = 0; j < g.n; j++)					// 遍历v的所有邻接点
		{
			if (!vistied[j] && g.a[v][j] != 0 && g.a[v][j] != g.noedge)
			{
				vistied[j] = 1;
				printf("%d ", j);
				q.push(j);
			}
		}
	}
}

void bfs_mgraph(mgraph g)
{
	int i;
	int* visited = (int*)malloc(g.n * sizeof(int));// 动态生成visited数组
	for (int i = 0; i < g.n; i++)
		visited[i] = 0;									// 初始化visited数组
	for (int i = 0; i < g.n; i++)
		if (!visited[i])
			bfs(i, visited, g);
	free(visited);
	printf("\n");
}

int dijkstra(mgraph g)
{
	int dist[100];
	int st[100];
	/*int* dist = (int*)malloc((g.n + 1) * sizeof(int));
	int* st = (int*)malloc((g.n + 1) * sizeof(int));*/
	for (int i = 0; i < g.n; i++)						// 初始化
	{
		st[i] = 0;
		dist[i] = g.noedge;
	}
	dist[0] = 0;
	for (int i = 0; i < g.n; i++)
	{
		int t = -1;
		for (int j = 0; j < g.n; j++)					// 选出最小的 dist[i]
		{
			if (!st[j] && (t == -1 || dist[j] < dist[t]))
				t = j;
		}
		st[t] = 1;

		for (int j = 0; j < g.n; j++)					// 更新距离
		{
			dist[j] = min(dist[j], dist[t] + g.a[t][j]);
		}
	}
	
	return dist[g.n - 1];
}
int main()
{
	mgraph g;
	int size, path;
	printf("请输入顶点数（编号0~size-1）:");
	scanf("%d", &size);
	printf("请输入边的数量:");
	scanf("%d", &path);
	init(&g, size, 0x3f3f3f3f);
	while (path--)
	{
		printf("请输入 起点/终点/边的权值:");
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		insert(&g, u, v, w);
		insert(&g, v, u, w);
	}
	printf("dfs:");
	dfs_mgraph(g);
	printf("bfs:");
	bfs_mgraph(g);
	printf("0~n-1的最短距离为: %d", dijkstra(g));
	return 0;
}