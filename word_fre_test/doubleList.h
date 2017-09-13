#include<stdio.h>

typedef struct tagNode
{
	struct tagNode* prev;
	struct tagNode* next;
}Node;

typedef struct tagLinkList
{
	Node head;
	Node tail;
	long len;
}LinkList;

typedef void (*PrintFun)(Node *node);
typedef int (*Compare)(Node* node1,Node* node2);
typedef int (*ValCompare)(Node* node, void* val);
typedef Node* (*Assign)(Node* node1,Node* node2);
typedef void (*FreeMemory)(Node *node);

//创建链表
LinkList* LinkList_Create();
//插入数据到链表
void LinkList_Insert(LinkList* linklist, Node* node, long pos);
//查找数据节点（节点数据相等）
Node* LinkList_Search(LinkList* linklist, void* val, ValCompare valcompare);
//查找数据节点（节点）
Node* LinkList_Search_Node(LinkList* linklist, Node* node);
//排序
LinkList* LinkList_Sort(LinkList* linklist,int low, int high,  Compare compare, Assign assign);
//排序（节点指针交换）
void LinkList_Sort_Node(LinkList* linklist, Compare compare);
//遍历（相同方向输出）
void LinkList_Traverse(LinkList* linklist, PrintFun print);
//遍历（相反）
void LinkList_Traverse_Reverse(LinkList* linklist, PrintFun print);
//返回链表长度
long LinkList_Length(LinkList* linklist);
//销毁链表
void LinkList_Destory(LinkList* linklist);
//获取链表pos位置节点
Node* LinkList_Get(LinkList* linklist, long pos);
//删除链表pos位置节点
Node* LinkList_Delete(LinkList* linklist, long pos);
//删除节点（按节点）
LinkList* LinkList_Delete_Node(LinkList* linklist, void *val,  ValCompare valcompare);
//释放内存，删除节点 用户释放
void LinkList_Free(LinkList* linklist , FreeMemory freemem);

void Swap(Node* node1, Node* node2);
//合并链表
LinkList* LinkList_Merge(LinkList* linklist_first, LinkList* linklist_second);
