#include<stdio.h>
#include<stdlib.h>

typedef struct pNode{
	int coef;
	int exp;
	struct pNode* link;
}PNode;
typedef struct polynominal{
	PNode *head;
}Polynominal; 

void Create(Polynominal* p)
{
	PNode* mx, * pre, * q;	
	p->head = (PNode*)malloc(sizeof(PNode));	
	p->head->exp = -1;
	p->head->link = p->head;
	printf("自定义两个多项式:\n");
	while(1)	// 创建链表
	{
		mx = (PNode*)malloc(sizeof(PNode));	
		printf("请输入系数:\n");
		scanf("%d", &mx->coef);				// 输入系数
		printf("指数（小于0时停止输入）:\n");
		scanf("%d", &mx->exp);				// 输入指数
		if (mx->exp < 0)						// 当指数为0时停止输入
			break;
		pre = p->head;
		q = p->head->link;
		while (q&&q->exp>mx->exp)				// 按照降幂排列
		{
			pre = q;
			q = q->link;
		}
		mx->link = q;							// 插入结点
		pre->link = mx;
	}
}

void Output(Polynominal* p)							// 输出
{
	PNode* temp = p->head->link;
	while (temp->exp>=0)
	{
		printf("%dx^%d", temp->coef, temp->exp);	
		printf("+");
		temp = temp->link;
	}
	// 控制格式
	printf("\b ");
	printf("\n");
}

void Add(Polynominal* px, Polynominal* qx)			// 多项式相加
{
	PNode* q, * q1 = qx->head, * p, * p1, * temp;	// q1指向表头结点
	p = px->head->link;								// p指向多项式px的第一个结点
	q = q1->link;									
	while (p->exp>=0)
	{
		while (p->exp < q->exp)						// 跳过q->exp大的项
		{
			q1 = q;
			q = q->link;
		}
		if (p->exp==q->exp)							// 当指数相等时，系数相加
		{
			q->coef = q->coef + p->coef;
			if (q->coef == 0)						// 若相加后系数为0
			{
				q1->link = q->link;					// 删除q
				free(p);							// 释放空间
				q = q1->link;						// 重置指针
				p = p->link;
			}
			else									// 若相加后不为0
			{
				q1 = q;								// q1后移
				q = q->link;
				p = p->link;
			}
		}
		else // p->epx > q->exp 的情况
		{
			temp = (PNode*)malloc(sizeof(PNode));	// 生成新结点
			temp->coef = p->coef;
			temp->exp = p->exp;
			temp->link = q1->link;
			q1->link = temp;
			q1 = q1->link;
			p = p->link;
		}
	}
}

int main()
{
	Polynominal mx0;
	Polynominal mx1;
	Create(&mx0);
	Output(&mx0);
	Create(&mx1);
	Output(&mx1);
	printf("相加后:");
	Add(&mx0, &mx1);
	Output(&mx1);
}


