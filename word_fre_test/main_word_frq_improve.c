#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<unistd.h>
#include"doubleList.h"


#define WORD_LEN 64 

typedef struct tagWordNode
{
	Node node;
	char word[WORD_LEN];
	int times;
}WordNode;

int StringCompare(Node* node, void *str)
{
	WordNode *tmpNode = (WordNode*) node;
	return	strcmp(tmpNode->word , str)? 0:1;
}

void Print(Node* node)
{
	WordNode* tmpNode = (WordNode*)node;
	printf("%s  %d %p %p %p\n", tmpNode->word, tmpNode->times, tmpNode->node.prev, &(tmpNode->node) , tmpNode->node.next);

}

int CompareNode(Node* node1, Node* node2)
{	
	WordNode* tmpNode1 = (WordNode*)node1;
	WordNode* tmpNode2 = (WordNode*)node2;
	return (tmpNode1->times >=tmpNode2->times) ? 1:0;
}

int CompareNodeWord(Node* node1, Node* node2)
{
	WordNode* tmpNode1 = (WordNode*)node1;
	WordNode* tmpNode2 = (WordNode*)node2;

	if(strcmp(tmpNode1->word , tmpNode2->word) >= 0)
		return 1;
	else
		return 0;
}

void FreeNodeMem(Node* node)
{	
	WordNode* tmpNode = (WordNode*)node;
	if(tmpNode!= NULL)
	{
		free(tmpNode);
	}
}
//处理字符串
void WordProcess(char *str, int discap , int *afterlen)
{
	if(str == NULL)
		return;
	int i = 0,  k = 0;
	int wordlen = strlen(str);
	int len = wordlen;
	if(discap == 0)  //不区分大小写 将大写字母转换为小写
	{
		for(i=0; i<wordlen; i++)
		{
			if(str[i]>='A'&&str[i]<='Z')
				str[i] =str[i] + 32;
		}
	}
	for(i=0; i<wordlen; i++)
	{
		if(!(str[0]>='A'&&str[0]<='Z' || (str[0]>='a'&&str[0]<='z')))			
		{
			k = 0;
			while(k<wordlen)
			{
				str[k] = str[k+1];
				k++;
			}
			len--;
		}
		if(len >0 && !((str[len-1]>='A'&&str[len-1]<='Z') ||( str[len-1]>='a'&&str[len-1]<='z')))
		{
			str[len-1] = str[len];
			len--;
		}	
	}

	*afterlen = len;
}

int main(int argc, char* argv[])
{
	LinkList* linklist_first = NULL;
	LinkList* linklist_second = NULL;
	char tmpword[WORD_LEN*2] = "";
	memset(tmpword ,0, WORD_LEN*2*sizeof(char));
	FILE *fp = NULL;
	int afterlen = 0; //处理后字符长度
	int bSort = 0;    //是否排序
	int bDis =  0;	  //是否区分大小写
	char ch = 0;	
	opterr = 0;
	while((ch = getopt(argc , argv, "s:d")) != -1)   //命令行 -s：排序 -d0:不区分大小写 -d1：区分大小写
	{
		switch(ch)
		{
			case 's':
				bSort =atoi(optarg); //输入-s 表明需要排序	
				break;
			case 'd':
				bDis = 1;
				break;
			default:
				break;
				
		}
	}
	//创建链表
	linklist_first = LinkList_Create();
	if(linklist_first == NULL)
	{
		printf("LinkList_Create error!\n");
		return 0;

	}
	
	linklist_second = LinkList_Create();
	if(linklist_second == NULL)
	{
		printf("LinkList_Create error!\n");
		return 0;
	}
	//打开文件 这里argv应该用getopt
	fp = fopen(argv[optind], "r");    //optind指向非选项的第一个参数
	if(fp == NULL)
	{
		printf("File Open Failed!\n");
		return 0;
	}
	//以空格结束 讲字符串读入tmpword
	while(fscanf(fp, "%64s", tmpword)!= EOF)
	{
		WordProcess(tmpword ,bDis ,&afterlen);// 0 不区分  1 区分大小写
		if(afterlen > WORD_LEN)
			continue;
		if(strcmp("m", tmpword)>=0)
		{
			Node* tmpNode = LinkList_Search(linklist_first, tmpword , StringCompare);
			if(tmpNode == NULL)	//说明没有这个字符串则插入
			{	
				WordNode* pWordNode =(WordNode*)malloc(sizeof(WordNode));
				memset(pWordNode ,0 , sizeof(WordNode));
				strcpy(pWordNode->word , tmpword);
				pWordNode->times++;
				LinkList_Insert(linklist_first ,(Node*)pWordNode ,0);
			}
			else
			{
				WordNode* tmpWordNode = (WordNode*)tmpNode;
				tmpWordNode->times++;
			}
		}
		else
		{
			Node* tmpNode = LinkList_Search(linklist_second, tmpword , StringCompare);
			if(tmpNode == NULL)	//说明没有这个字符串则插入
			{	
				WordNode* pWordNode =(WordNode*)malloc(sizeof(WordNode));
				memset(pWordNode ,0 , sizeof(WordNode));
				strcpy(pWordNode->word , tmpword);
				pWordNode->times++;
				LinkList_Insert(linklist_second ,(Node*)pWordNode ,0);
			}
			else
			{
				WordNode* tmpWordNode = (WordNode*)tmpNode;
				tmpWordNode->times++;
			}
		}
	}
	//关闭文件
	fclose(fp);
	//合并链表
	LinkList* linklist_merge = NULL;
	linklist_merge = LinkList_Merge(linklist_first, linklist_second);
	LinkList_Traverse_Reverse(linklist_merge, Print);
/*	printf("swap:----------\n");
	Node* node1 = linklist_merge->head.next;
	Node* node2 = linklist_merge->tail.prev;
	Swap(node1 ,node2);

	LinkList_Traverse_Reverse(linklist_merge, Print);
*/	
	printf("-----------------\n");
	if(bSort == 1)
	{
		//排序打印 按出现次数从小大
		LinkList_Sort_Node(linklist_merge ,CompareNode);			
		LinkList_Traverse_Reverse(linklist_merge, Print);
		printf("------------\n");
		LinkList_Traverse(linklist_merge, Print);
	}
	else if(bSort == 0)
	{
		//打印出现次数最多的字符串
		LinkList_Sort_Node(linklist_merge ,CompareNode);			
		WordNode* tmp = (WordNode*)LinkList_Get(linklist_merge , linklist_merge->len-1);
		printf("%s  %d\n:", tmp->word, tmp->times);	
	}
	else if(bSort ==2)
	{
		//按词排序 跟词典的一样
		LinkList_Sort_Node(linklist_merge ,CompareNodeWord);			
//		LinkList_Traverse_Reverse(linklist_merge, Print);
		fprintf(stderr, "*----------------\n");
		LinkList_Traverse(linklist_merge, Print);
	}
	LinkList_Free(linklist_merge , FreeNodeMem);
	LinkList_Destory(linklist_merge);
	return 1;
}
