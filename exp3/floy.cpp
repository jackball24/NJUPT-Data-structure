#include <iostream>
#include <string>   
#include <stdio.h>   
using namespace std;   
#define MaxVertexNum 100   
#define INF 32767   
typedef struct  
{   
    char vertex[MaxVertexNum];   
    int edges[MaxVertexNum][MaxVertexNum];   
    int n,e;   
}MGraph;   

void CreateMGraph(MGraph &G)   
{   
    int i,j,k,p;   
    cout<<"请输入顶点数和边数:";   
    cin>>G.n>>G.e;   
    cout<<"请输入顶点元素:";   
    for (i=0;i<G.n;i++)   
    {   
        cin>>G.vertex[i];   
    }   
    for (i=0;i<G.n;i++)   
    {   
        for (j=0;j<G.n;j++)   
        {   
            G.edges[i][j]=INF;   
            if (i==j)   
            {   
                G.edges[i][j]=0;   
            }   
        }   
    }      
    for (k=0;k<G.e;k++)   
    {   
        cout<<"请输入第"<<k+1<<"条弧头弧尾序号和相应的权值:";   
        cin>>i>>j>>p;   
        G.edges[i][j]=p;   
    }   
}   
void Dispath(int A[][MaxVertexNum],int path[][MaxVertexNum],int n);

void Floyd(MGraph G)
{
	int A[MaxVertexNum][MaxVertexNum],path[MaxVertexNum][MaxVertexNum];
	int i,j,k;
	for (i=0;i<G.n;i++)
	{
		for (j=0;j<G.n;j++)
		{
			A[i][j]=G.edges[i][j];
			path[i][j]=-1;
		}
	}
	for (k=0;k<G.n;k++)
	{
		for (i=0;i<G.n;i++)
		{
			for (j=0;j<G.n;j++)
			{
				if (A[i][j]>A[i][k]+A[k][j])
				{
					A[i][j]=A[i][k]+A[k][j];
					path[i][j]=k;
				}
			}
		}
	}
	Dispath(A,path,G.n);
}

void Ppath(int path[][MaxVertexNum],int i,int j)
{
	int k;
	k=path[i][j];
	if (k==-1)
	{
		return;
	}
	Ppath(path,i,k);
	printf("%d",k);
	Ppath(path,k,j);
}

void Dispath(int A[][MaxVertexNum],int path[][MaxVertexNum],int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			if (A[i][j]==INF)
			{
				if (i!=j)
				{
					printf("从%d到%d没有路径/n",i,j);
				}
			}
			else
			{
				printf("  从%d到%d=>路径长度:%d路径:",i,j,A[i][j]);
				printf("%d,",i);
				Ppath(path,i,j);
				printf("%d/n",j);
			}
		}
	}
}

int main()
{
	MGraph G;
	CreateMGraph(G);
	Floyd(G);
	return 0;
}


// #include <stdio.h>
// #define V 4    //设定图中的顶点数
// #define INF 65535   // 设置一个最大值
// int P[V][V] = { 0 }; //记录各个顶点之间的最短路径
// void printMatrix(int matrix[][V]);  //输出各个顶点之间的最短路径
// void printPath(int i, int j); // 递归输出各个顶点之间最短路径的具体线路
// void floydWarshall(int graph[][V]); // 实现弗洛伊德算法
// int main() {
//     // 有向加权图中各个顶点之间的路径信息
//     int graph[V][V] = { {0, 3, INF, 5},
//                           {2, 0, INF, 4},
//                           {INF, 1, 0, INF},
//                           {INF, INF, 2, 0} };
//     floydWarshall(graph);
// }
// // 中序递归输出各个顶点之间最短路径的具体线路
// void printPath(int i, int j)
// {
//     int k = P[i][j];
//     if (k == 0)
//         return;
//     printPath(i, k);
//     printf("%d-", k + 1);
//     printPath(k, j);
// }
// // 输出各个顶点之间的最短路径
// void printMatrix(int graph[][V]) {
//     int i, j;
//     for (i = 0; i < V; i++) {
//         for (j = 0; j < V; j++) {
//             if (j == i) {
//                 continue;
//             }
//             printf("%d - %d: 最短路径为:", i + 1, j + 1);
//             if (graph[i][j] == INF)
//                 printf("%s\n", "INF");
//             else {
//                 printf("%d", graph[i][j]);
//                 printf("，依次经过：%d-", i + 1);
//                 //调用递归函数
//                 printPath(i, j);
//                 printf("%d\n", j + 1);
//             }
//         }
//     }
// }
// // 实现弗洛伊德算法,graph[][V] 为有向加权图
// void floydWarshall(int graph[][V]) {
//     int  i, j, k;
//     //遍历每个顶点，将其作为其它顶点之间的中间顶点，更新 graph 数组
//     for (k = 0; k < V; k++) {
//         for (i = 0; i < V; i++) {
//             for (j = 0; j < V; j++) {
//                 //如果新的路径比之前记录的更短，则更新 graph 数组
//                 if (graph[i][k] + graph[k][j] < graph[i][j]) {
//                     graph[i][j] = graph[i][k] + graph[k][j];
//                     //记录此路径
//                     P[i][j] = k;
//                 }
//             }
//         }
//     }
//     // 输出各个顶点之间的最短路径
//     printMatrix(graph);
// }