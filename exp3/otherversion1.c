#include <stdio.h>
#include <malloc.h> 

#define MAXSIZE 100 
#define GraphINF 88888

typedef char VertexType; //顶点类型应由用户定义  
typedef int EdgeType; 	 //边上的权值类型应由用户定义 

//定义邻接矩阵存储结构
typedef struct MGraph{
	
	int numNodes;					//用于记录顶点个数
	int numEdges;					//用于记录边个数
	VertexType vexs[MAXSIZE];		//用于保存顶点元素
	EdgeType arcs[MAXSIZE][MAXSIZE];//用于保存边元素 

}MGraph;

//创建邻接矩阵 
//定义arcs 邻接矩阵从下标为1开始存储 方便之后用户输入 
 
void CreateMGraph(MGraph **G)
{
	int i,j,k,w;
	(*G)=(MGraph*)malloc(sizeof(MGraph));
	printf("请输入结点与边的数目（格式为 i,j ）：\n");
	scanf("%d,%d",&(*G)->numNodes,&(*G)->numEdges);

	//初始化顶点数组信息 
	printf("输入顶点信息(格式为A(空格)B(空格)C)：\n");
	for(i = 0;i <(*G)->numNodes;i++){
		scanf(" %c",&(*G)->vexs[i]);
	} 
	
	//表头初始化
	(*G)->arcs[0][0]=-1; 
	for(k=1;k<=(*G)->numNodes;k++){
		(*G)->arcs[0][k]=k;
		(*G)->arcs[k][0]=k;				
	} 
	
	//整表初始化∞
	for(i = 1;i <=(*G)->numNodes;i++){
		for(j =1;j<=(*G)->numNodes;j++){
			if(i==j){
				(*G)->arcs[i][j]= 0;		//与自己的距离 
			} 
			else (*G)->arcs[i][j]= GraphINF;		
		} 	
	} 
	//连接有权重边的结点的赋值
	for(k = 1;k <=(*G)->numEdges;k++) //读入numEdges条边，建立邻接矩阵 
	{
		printf("输入边(vi,vj)上的下标i，下标j和权w（格式为i，j，w）:\n");
		scanf("%d,%d,%d",&i,&j,&w); //输入边(vi,vj)上的权w 
		(*G)->arcs[i][j]=w; 
		(*G)->arcs[j][i]= (*G)->arcs[i][j]; //无向图 
	}
	printf("\n");
} 

//打印邻接矩阵  
PrintfMGraph(MGraph *G)
{
	int i,j,k,cnt,elem;

	for(i=0;i<=G->numNodes;i++){
		cnt=1; 
			for(j=0;j<=G->numNodes;j++){
				if(G->arcs[i][j]==GraphINF){
					printf("  ∞");
				}
				else if (G->arcs[i][j]==-1){
					printf("顶点");
				}
				else if(i==0&&j!=0){
					elem=(int)(G->vexs[j-1]);
					G->arcs[0][j]=elem;
					printf("  %c ",G->arcs[0][j]);
					
				}
				else if(i!=0&&j==0){
					elem=(int)(G->vexs[i-1]);
					G->arcs[i][0]=elem;
					printf("  %c ",G->arcs[i][0]);
					
				}
				else printf("  %d ",G->arcs[i][j]);
			
				if(cnt%(G->numNodes+1)==0){
					printf("\n");
				}	
				cnt++;					
			}
		
	} 
	
	
}

int main()
{
	MGraph *G;
	CreateMGraph(&G);
	PrintfMGraph(G);
	return 0;
}
