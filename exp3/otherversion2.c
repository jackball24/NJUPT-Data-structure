#include<stdio.h>
#include<malloc.h>

#define MAXVEX 100

typedef char VertexType; 	//顶点数据类型为char 
typedef int EdgeType; 		 //边上的权值类型为int 
typedef int NodeReturnType;	//结点返回值 

//边表结点结构
typedef struct EdgeNode{
	
	int adjvex;		    	//用于存储边表的下标 
	EdgeType weight;		//用于存储边表权值
	struct EdgeNode *next;	//用于指向下一个邻接点（边表结点) 	
	
}EdgeNode; 


//顶点结构
typedef struct VertexNode{
	
	VertexType data;		//用于存储顶点结点信息 
	EdgeNode* firstedge;	//用于存储第一个邻接点 
	
}VertexNode,AdjList[MAXVEX];//定义AdjList[MAXVEX]为顶点数组 

//邻接表结构
typedef struct ALGraph{
	
	int numNodes;			//用于记录顶点个数
	int numEdges;			//用于记录边个数 
	AdjList adjList;		//用于存储顶点的数组 
	//VertexNode adjList[MAXVEX]; 顶点数组这样也ok 
	
}ALGraph;

//明确顶点数据存储的是ABCD 这些点当成边点时存的就是1,2,3,4 
//故我们在这里定义一个Locate函数来找ABCD位于顶点数组的位置下标1,2,3,4(返回值) 
//1,2,3,4 则作为边结点的data 
NodeReturnType LocateVex(ALGraph *G,char vex)
 {
 	int index;
 	for(index=0;index<G->numNodes;index++){
 		if(G->adjList[index].data==vex){
		 return index; 
		 } 
	 }
 }

void CreatALGraph(ALGraph **G)
{
	int i,j,k;
	char v1,v2;
	EdgeNode *NewarcNode1,*NewarcNode2;
	(*G)=(ALGraph*)malloc(sizeof(ALGraph)) ;	//动态申请空间
	printf("请输入顶点数与边数（格式为i,j）:\n");
	scanf("%d,%d",&(*G)->numNodes,&(*G)->numEdges);
	
	printf("输入顶点信息(格式为A(空格)B(空格)C)：\n");
	//初始化顶点表 
	for(i=0;i<(*G)->numNodes;i++){
		scanf(" %c",&((*G)->adjList[i].data));			//输入顶点表信息 %c前空格吃回车 
		(*G)->adjList[i].firstedge=NULL;				//将顶点表的邻接点指针域置空 
	}

	
	//建立邻接点与顶点逻辑关系	
	for(k=0;k<(*G)->numEdges;k++){
		printf("请输入i->j的两个顶点(格式:A(空格)C):\n");
		scanf(" %c %c",&v1,&v2);
		
	//获取邻接点的data 
		i=LocateVex((*G),v1);
		j=LocateVex((*G),v2);
		
	//头插法 无向图所以两个顶点都需要操作 
		
		//i->j 
		NewarcNode1=(EdgeNode*)malloc(sizeof(EdgeNode)) ;
		NewarcNode1->adjvex=i;		
		NewarcNode1->next=(*G)->adjList[j].firstedge;
		(*G)->adjList[j].firstedge=NewarcNode1;
		
		//j->i 
		NewarcNode2=(EdgeNode*)malloc(sizeof(EdgeNode)) ;
		NewarcNode2->adjvex=j;
		NewarcNode2->next=(*G)->adjList[i].firstedge;
		(*G)->adjList[i].firstedge=NewarcNode2;	 	
		
	}
	 
}


//打印邻接表 
//输出样式	Vex：Edge1 Edge2........ 


void PrintALGraph(ALGraph *G)
{
	int i,j; 
	EdgeNode *p;		//用于指向当前操作边结点 
	
	// 输出顶点结点
	for(i=0;i<G->numNodes;i++){ 
		printf("顶点%c",G->adjList[i].data) ;//注意是%c  
//		printf("numNodes=%d",G->numNodes);
		for(p= G->adjList[i].firstedge;p!=NULL;p=p->next){
			printf("->%d ",p->adjvex);
		}
		printf("\n"); 
	} 
	printf("\n"); 
}



int main()
{
	ALGraph *G; 
	CreatALGraph(&G);
	PrintALGraph(G);
	return 0;	
} 
