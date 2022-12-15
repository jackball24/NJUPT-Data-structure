#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define INF 0xfffff    //权值上限
#define maxn 110  //最大顶点个数
int n;       //顶点个数

struct arcnode  //边结点
{
    int vertex;     //与表头结点相邻的顶点编号
    int weight;     //连接两顶点的边的权值
    arcnode * next; //指向下一相邻接点
    arcnode() {}
    arcnode(int v,int w):vertex(v),weight(w),next(NULL) {}
};

struct vernode      //顶点结点，为每一条邻接表的表头结点
{
    int vex;    //当前定点编号
    arcnode * firarc;   //与该顶点相连的第一个顶点组成的边
}Ver[maxn];

void Init()  //建立图的邻接表需要先初始化，建立顶点结点
{
    for(int i = 1; i <= n; i++)
    {
        Ver[i].vex = i;
        Ver[i].firarc = NULL;
    }
}

void Insert(int a, int b, int w)  //尾插法，插入以a为起点，b为终点，权为w的边，效率不如头插，但是可以去重边
{
    arcnode * q = new arcnode(b, w);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        if(p->vertex == b)
        {
            if(p->weight > w)
                p->weight = w;
            return ;
        }
        while(p->next != NULL)
        {
            if(p->next->vertex == b)
            {
                if(p->next->weight > w)
                    p->next->weight = w;
                return ;
            }
            p = p->next;
        }
        p->next = q;
    }
}
void Insert2(int a, int b, int w)   //头插法，效率更高，但不能去重边
{
    arcnode * q = new arcnode(b, w);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        q->next = p;
        Ver[a].firarc = q;
    }
}
struct node     //顶点节点，保存id和到源顶点的估算距离，优先队列需要的类型
{
    int id;     //源顶点id和估算距离
    int w;
    friend bool operator<(node a, node b)   //因要实现最小堆，按升序排列，因而需要重载运算符，重定义优先级，以小为先
    {
        return a.w > b.w;
    }
};

int parent[maxn];   //每个顶点的父亲节点，可以用于还原最短路径树
bool visited[maxn]; //用于判断顶点是否已经在最短路径树中，或者说是否已找到最短路径
node d[maxn];      //源点到每个顶点估算距离，最后结果为源点到所有顶点的最短路。
priority_queue<node> q; //优先队列stl实现
void Dijkstra(int s)    //Dijkstra算法，传入源顶点
{
    for(int i = 1; i <= n; i++) //初始化
    {
        d[i].id = i;
        d[i].w = INF;           //估算距离置INF
        parent[i] = -1;         //每个顶点都无父亲节点
        visited[i] = false;     //都未找到最短路
    }
    d[s].w = 0;                 //源点到源点最短路权值为0
    q.push(d[s]);               //压入队列中
    while(!q.empty())           //算法的核心，队列空说明完成了操作
    {
        node cd = q.top();      //取最小估算距离顶点
        q.pop();
        int u = cd.id;
        if(visited[u])   
            continue;
        visited[u] = true;
        arcnode * p = Ver[u].firarc;
        //松弛操作
        while(p != NULL)    //找所有与他相邻的顶点，进行松弛操作，更新估算距离，压入队列。
        {
            int v = p->vertex;
            if(!visited[v] && d[v].w > d[u].w+p->weight)
            {
                d[v].w = d[u].w+p->weight;
                parent[v] = u;
                q.push(d[v]);
            }
            p = p->next;
        }
    }
}

int main()
{
    int m, a, b, c, st, ed;
    printf("请输入地点数和路径数：\n");
    scanf("%d%d", &n, &m);
    printf("请输入路径以及路径长度（a, b, c)\n");
    Init();     //计算前必须初始化
    while(m--)
    {
        scanf("%d%d%d", &a, &b, &c);
        Insert2(a, b, c);   //无向图注意存储两条边
        Insert2(b, a, c);
    }
    printf("请输入起点和终点：\n");
    scanf("%d%d", &st, &ed);
    Dijkstra(st);
    if(d[ed].w != INF)
        printf("%d到%d最短路径长度为：%d\n", st,ed,d[ed].w);
    else
        printf("不存在从地点%d到地点%d的最短路径。\n", st, ed);
    return 0;
}