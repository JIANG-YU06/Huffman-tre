#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>//用里面的isdigit函数 
#define N 100

typedef struct Node
{
	int weight;//结点权重 
	char zhi;//值 
	int parent;//父结点号 
	int lchild;//左孩子号 
	int rchild;//右孩子号 
}*stack;//同时创建了一个结构体类型的指针 

void compare(int *s1,int *s2,stack ps,int n);//寻找最小值和次小值的下标函数 (通过s1 s2排列位置)
stack create(int quan[],char str[],int n,stack ps,int *s1,int *s2);//创建哈夫曼树初始化并填好 
//void display(stack ps,int n);//显示 

int main(){
	int i,n=-1,quan[N],s1,s2;
	char str[N];
	stack ps;
	while(1){
		n++;
		scanf("%c,%d,",&str[n],&quan[n]);
		//printf("%d\n",n);
		if (str[n] > 90 || str[n]<65)
		break;
		//printf("%c,%d",str[n],quan[n]);
	}
	ps = create(quan,str,n,ps,&s1,&s2);
	//display(ps,n);
	//printf("%d\n",n);
	free(ps);
}

void compare(int *s1,int *s2,stack ps,int n){
	int min1=9999999,min2=9999999,i;//首先把这两个赋值一个比较大的数值，方面下面的比较,这里一定要够大，因为真的还有那么大 
	
	//获取最小值的下标 
	for(i=0;i<2*n-1;i++)
	{
		if((ps+i)->weight!=0 && (ps+i)->parent==-1)//如果当前权重不为NULL(权重不为空)，并且父结点为NULL，就是孤结点
		{
		 	if(min1>(ps+i)->weight)
		 	{
		 		*s1=i;//获取下标 
		 		min1=(ps+i)->weight;//每次比较后获取较小值，进行下一次比较  
			}
		} 
	}
	//获取次小值的下标 
	for(i=0;i<2*n-1;i++)
	{
		if((ps+i)->weight!=0 && (ps+i)->parent==-1)//如果当前权重不为NULL，并且父结点为NULL，就是孤结点
		{
		 	if(min2>(ps+i)->weight && i!=*s1)
		 	{
		 		*s2=i;//获取下标 
		 		min2=(ps+i)->weight;//每次比较后获取较小值，进行下一次比较  
			}
		} 
	}
}

stack create(int quan[],char str[],int n,stack ps,int *s1,int *s2){
	int i;
	
	ps = (stack)malloc((2*n-1) * sizeof(struct Node));
	
	for (i=0;i<(2*n-1);i++){
		ps[i].parent=ps[i].lchild=ps[i].rchild=-1;//初始化为-1 
		ps[i].zhi=NULL;
		if (i<n){
			ps[i].weight = quan[i];
			//printf("%d\n",quan[i]);
			ps[i].zhi = str[i];
		}
		else ps[i].weight = 0;
	}
	
	for(i=n;i<2*n-1;i++)
	{
		compare(s1,s2,ps,n);
		(ps+i)->weight=(ps+*s1)->weight+(ps+*s2)->weight;//该节点的权重=两个儿子的权重之和 
		ps[*s2].parent=ps[*s1].parent=i;//儿子的父结点是该节点（此节点连接左儿子和右儿子） 
		ps[i].lchild=*s1;//左儿子*s1 
		ps[i].rchild=*s2;//右儿子*s2 
	}
	printf("下标   权值    节点     父结点   左孩子   右孩子\n");
	//printf("0                                  \n");
	for ( i = 0; i <2*n-1 ; i++)
	{
		printf("%-4d   %-6d   %-6c   %-6d   %-6d   %-6d\n", i, ps[i].weight, ps[i].zhi, ps[i].parent, ps[i].lchild, ps[i].rchild);
	}
	printf("\n");
	return ps;
}
