#include<stdio.h>
#include<stdlib.h>
#define M 100
typedef char Etype; //定义二叉树结点值的类型为字符型
typedef struct BiTNode      //树结点结构
{  
    Etype data;
    struct BiTNode *lch,*rch;
}BiTNode,*BiTree;
BiTree que[M];
int front=0,rear=0;
//函数原型声明
BiTNode *creat_bt1();
BiTNode *creat_bt2();
void preorder(BiTNode *p);
void inorder(BiTNode *p);
void postorder(BiTNode *p);
void enqueue(BiTree);
BiTree delqueue( );
void levorder(BiTree);
int treedepth(BiTree);
void prtbtree(BiTree,int);
void exchange(BiTree);
int leafcount(BiTree);
void paintleaf(BiTree);
BiTNode *t;
int count=0;
//主函数
void main()
{
    char ch;
    int k;
    do{
        printf("\n\n\n");
        printf("\n===================主菜单===================");
        printf("\n\n   1.建立二叉树方法1");
        printf("\n\n   2.建立二叉树方法2");
        printf("\n\n   3.先序递归遍历二叉树");
        printf("\n\n   4.中序递归遍历二叉树");
        printf("\n\n   5.后序递归遍历二叉树");
        printf("\n\n   6.层次遍历二叉树");
        printf("\n\n   7.计算二叉树的高度");
        printf("\n\n   8.计算二叉树中叶结点个数");
        printf("\n\n   9.交换二叉树的左右子树");
        printf("\n\n   10.打印二叉树");
        printf("\n\n   0.结束程序运行");
        printf("\n============================================");
        printf("\n   请输入您的选择(0,1,2,3,4,5,6,7,8,9,10)");
        scanf("%d",&k);
        switch(k)
        {
            case 1:t=creat_bt1( );break;                  //调用性质5建立二叉树算法
            case 2:
                printf("示例123##4##5#6##   其中#代表空，##代表双孩子空");
                printf("\n    1\n  2   5\n3  4  # 6\n## ##    ##");
                printf("\n若无法退出循环则连续输入 12##4##5#6## ");
                printf("\n请输入二叉树各结点值:");
                fflush(stdin);
                t = creat_bt2();
                break; //调用递归建立二叉树算法
            case 3:if(t)
                   {printf("先序遍历二叉树:");
                   preorder(t);
                   printf("\n");
                   }
                   else printf("二叉树为空!\n");
                   break;
            case 4:if(t)
                   {printf("中序遍历二叉树:");
                   inorder(t);
                   printf("\n");
                   }
                   else printf("二叉树为空!\n");
                   break;
            case 5:if(t)
                   {printf("后序遍历二叉树:");
                   postorder(t);
                   printf("\n");
                   }
                   else printf("二叉树为空!\n");
                   break;
            case 6:if(t)
                   {printf("层次遍历二叉树：");
                    levorder(t);
                    printf("\n");
                   }
                   else printf("二叉树为空！\n");
                   break;
            case 7:if(t)
                   {printf("二叉树的高度为：%d",treedepth(t));
                    printf("\n");
                   }
                   else printf("二叉树为空！\n");
                   break;
            case 8:if(t)
                   {printf("二叉树的叶子结点数为：%d\n",leafcount(t));
                    printf("二叉树的叶结点为：");paintleaf(t);
                    printf("\n");
                   }
                   else printf("二叉树为空！\n");
                   break;
            case 9:if(t)
                   {printf("交换二叉树的左右子树：\n");
                    exchange(t);
                    prtbtree(t,0);
                    printf("\n");
                   }
                   else printf("二叉树为空！\n");
                   break;
            case 10:if(t)
                    {printf("逆时针旋转90度输出的二叉树：\n");
                     prtbtree(t,0);
                     printf("\n");
                    }
                    else printf("二叉树为空！\n");
                    break;
            case 0:exit(0);
            }   //switch
 
}while(k>=1&&k<=10);
        printf("\n再见！按回车键，返回…\n");
        ch=getchar();
}   //main
//输出叶结点
void paintleaf(BiTree t)
{
    if(t)
    {
        if(t->lch==NULL&&t->rch==NULL)
        {
            printf("%c ",t->data);
        }
        paintleaf(t->lch);
        paintleaf(t->rch);
    }
}
//输出二叉树
void prtbtree(BiTree t,int n)
{
    int i;
    if(t)
    {
        prtbtree(t->rch,n+1);
        for(i=0;i<n;i++)
        {
            printf(" ");
        }
        printf("%c\n",t->data);
        prtbtree(t->lch,n+1);
    }
}
//利用二叉树性质6，借助一维数组V建立二叉树
BiTNode *creat_bt1()
{ BiTNode *t,*p,*v[20];int i,j;Etype e;
/*输入结点的序号i、结点的数据e*/
printf("\n请输入二叉树各结点的编号和对应的值（如1，a）：");
scanf("%d,%c",&i,&e);
while(i!=0&&e!='#')                                //当i为0，e为'#'时，结束循环
{
    p=(BiTNode*)malloc(sizeof(BiTNode));
    p->data=e;
    p->lch=NULL;
    p->rch=NULL;
    v[i]=p;
   if(i==1)
    t=p;   //序号为1的结点是根 
    else
    {
        j=i/2;
        if(i%2==0)v[j]->lch=p;                        //序号为偶数，作为左孩子 
        else  v[j]->rch=p;                            //序号为奇数，作为右孩子 
    }
    printf("\n请继续输入二叉树各结点的编号和对应的值：");
    scanf("%d,%c",&i,&e);
}
return(t);
}//creat_bt1;
//模仿先序递归遍历方法，建立二叉树
BiTNode *creat_bt2()
{
    BiTNode *t;
    Etype e;
    scanf("%c",&e);
    if(e=='#')t=NULL;   //对于'#'值，不分配新结点 
    else{
            t=(BiTNode *)malloc(sizeof(BiTNode));
            t->data=e;
            t->lch=creat_bt2();                               //左孩子获得新指针值 
            t->rch=creat_bt2();                               //右孩子获得新指针值
          }
    return(t);
}   //creat_bt2
//先序递归遍历二叉树
void preorder(BiTNode *p)
{
   if(p){
        printf("%3c",p->data);
        preorder(p->lch);
        preorder(p->rch);
    }
}    //preorder
//中序递归遍历二叉树
void inorder(BiTNode *p)
{
   if(p){
        inorder(p->lch);
        printf("%3c",p->data);
        inorder(p->rch);
    }
} //inorder
//后序递归遍历二叉树
void postorder(BiTNode *p)
{ 
    if(p){ postorder(p->lch);
         postorder(p->rch);
         printf("%3c",p->data);
     }
} //postorder
//层次遍历二叉树
void enqueue(BiTree T)
{
    if(front!=(rear+1)%M)
    {rear=(rear+1)%M;
    que[rear]=T;}
}
BiTree delqueue( )
{
    if(front==rear)return NULL;
    front=(front+1)%M;
    return(que[front]);
}
void levorder(BiTree T)                //层次遍历二叉树
{
    BiTree p;
    if(T){enqueue(T);
       while(front!=rear){
        p=delqueue(  );
        printf("%3d",p->data-48);
        if(p->lch!=NULL)enqueue(p->lch);
        if(p->rch!=NULL)enqueue(p->rch);
        }
    }
}
int treedepth(BiTree bt)        //计算二叉树的高度
{
    int hl,hr,max;
    if(bt!=NULL)
    {  hl=treedepth(bt->lch);
       hr=treedepth(bt->rch);
       max=(hl>hr)?hl:hr;
       return (max+1);
    }
    else return (0);
} 
void exchange(BiTree bt){  //交换二叉树左右子树
      BiTree p;
      if(bt){
          p=bt->lch;
          bt->lch=bt->rch;
          bt->rch=p;
          exchange(bt->lch);
          exchange(bt->rch);
      }
} 
int leafcount(BiTree bt)  {//计算叶结点数
if(bt!=NULL){
    leafcount(bt->lch);
    leafcount(bt->rch);
    if((bt->lch==NULL)&&(bt->rch==NULL))
        count++;
}
return(count);
} 


            
