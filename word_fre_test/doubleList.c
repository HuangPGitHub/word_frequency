#include "doubleList.h"
#include <stdlib.h>
#include<memory.h>
//创建链表
LinkList* LinkList_Create()
{
	LinkList *linklist = NULL;
	linklist =(LinkList*) malloc(sizeof(LinkList));
	if(!linklist)
		return NULL;
	memset(linklist , 0 , sizeof(LinkList));
//	linklist->head.next = NULL;
//	linklist->head.prev = NULL;
	linklist->head.next =&(linklist->tail);
	linklist->head.prev = NULL;
	linklist->tail.prev = &(linklist->head);
	linklist->tail.next = NULL;
	linklist->len = 0;
		
	return linklist; 
}

//插入数据到链表
void LinkList_Insert(LinkList* linklist, Node* node, long pos)
{
	if(linklist == NULL || node ==NULL || pos<0)
		return;
	Node *current;
	Node *ptail;
	int i = 0;
	current =&(linklist->head);
	ptail = &(linklist->tail);
	for(i = 0;i<pos &&(current->next!= NULL); i++)
	{
		current = current->next;
	}
	if(current->next == ptail/*NULL*/)
	{
		current->prev = NULL;
		current->next = node;
		node->prev = current;
//		node->next = NULL;
		node->next = ptail;
		ptail->prev = node;
		ptail->next = NULL;
		linklist->len++;	
	}	
	else
	{
 		node->prev = current;
		node->next = current->next;
		current->next->prev = node;
		current->next = node;
		linklist->len++;
	}
	
	return;
}

//查找数据节点(数据相等)
Node* LinkList_Search(LinkList* linklist, void* val, ValCompare  valcompare)
{
	if(linklist == NULL)
		return NULL;
	Node* tmp;
	tmp =linklist->head.next;
	while( tmp!= NULL)
	{	
		if(valcompare(tmp, val))
			return tmp;
		else
			tmp = tmp->next;			
	}
	return NULL;
}
//查找数据节点（节点相等）
Node* LinkList_Search_Node(LinkList* linklist, Node* node)
{
	if(linklist == NULL || node == NULL)
		return NULL;
	Node* tmp;
	tmp =linklist->head.next;
	while( tmp!= NULL)
	{	
		if(tmp==node)
			return tmp;
		else
			tmp = tmp->next;			
	}
	return NULL;	
}

void Swap(Node* node1, Node* node2)
{
	Node* node1_p = node1->prev;
	Node* node1_n = node1->next;
	if(node1->next == node2)
	{
		node1->prev->next = node2;
		node2->prev = node1->prev;
		node1->next = node2->next;
//		if(node2->next != NULL)	
		node2->next->prev  = node1;
		node2->next = node1;
		node1->prev = node2;
	}	
	else
	{
		node1->prev = node2->prev;
		node1->next = node2->next;
		node2->prev->next = node1;
//		if(node2->next != NULL)	
		node2->next->prev = node1;

		node2->prev = node1_p;
		node2->next = node1_n;
		node1_n->prev = node2;
		if(node1_p != NULL)
			node1_p->next = node2;
	}	
	return;
}

void SwapIJ(Node** node1, Node** node2)
{
	Node* tmp;
	tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;

	return;
}


void  qSort(Node* bgnNode, Node* endNode, Compare compare)
{	
	if(bgnNode == NULL || endNode == NULL || bgnNode == endNode)
		return;
	
	Node* storgbgnN = bgnNode;
	Node* storgendN = endNode;
	Node* iNode = bgnNode;
	Node* jNode = endNode;
	Node* tmpNode = bgnNode;

	while(iNode != jNode)
	{
		while( compare(jNode, tmpNode) && iNode!= jNode)
		{
//			fprintf( stderr,"%s   %d\n",__FILE__, __LINE__ );
			jNode = jNode->prev;	
		}
		if(iNode != jNode)
		{
//			fprintf( stderr,"%s    %d\n",__FILE__, __LINE__ );
			Swap(iNode , jNode);
			if(iNode == storgbgnN)
			{
				storgbgnN = jNode;
			}
			if(jNode == storgendN)
			{
				storgendN = iNode;
			}
			SwapIJ(&iNode, &jNode);
			iNode = iNode->next;
		}	
		while( !compare(iNode, tmpNode) && iNode!=jNode)
		{
			iNode = iNode->next;
		}
		if(iNode != jNode)
		{
			Swap(iNode, jNode);
			if(jNode == storgendN)
			{
				storgendN = iNode;
			}
			if(iNode == storgbgnN)
			{
				storgbgnN= jNode;
			}
			SwapIJ(&iNode, &jNode);
			jNode = jNode->prev;
		}
	}
//	fprintf(stderr , "tmpNode->prev:%p ,  tmpNode:%p , tmpNode->next:%p , iNode:%p , jNode:%p\n", tmpNode->prev,tmpNode, tmpNode->next, iNode, jNode);
	if(tmpNode != storgbgnN )
		qSort(storgbgnN , tmpNode->prev, compare);

	if(tmpNode != storgendN)
		qSort(tmpNode->next, storgendN, compare);

	return;
}

//排序（交换指针）
void LinkList_Sort_Node(LinkList* linklist, Compare compare)
{
	if(linklist == NULL || linklist->len <0)
		return;
	
	Node* bgnNode;
	Node* endNode;
	
	bgnNode = linklist->head.next;
	endNode = linklist->tail.prev;
/*	endNode = &(linklist->head);
	while(endNode->next)
	{
		endNode = endNode->next;
	}*/	
	qSort(bgnNode ,endNode, compare);

	return;
}

//排序
LinkList* LinkList_Sort(LinkList* linklist,int low, int high, Compare compare, Assign assign)
{
	if(linklist == NULL)
		return NULL;
	int n = 0;
	int i = low;
	int j = high;	
	Node* iNode;
	Node* jNode;
	Node* tmpNode = malloc(sizeof(Node));
	if(tmpNode == NULL)
		return NULL;
	iNode = linklist->head.next;

	for (n=0; n<i&&(iNode->next!=NULL); n++)
	{
		iNode = iNode->next;
	}	
	memcpy(tmpNode, iNode, sizeof(Node));
	tmpNode = assign(tmpNode, iNode);

	jNode = linklist->head.next;
	for (n=0; n<j&&(jNode->next!=NULL); n++)
	{
		jNode = jNode->next;
	}
	if(low<high)
	{
		while(i < j)
		{
			while(compare(jNode ,tmpNode)&&(i < j))
			{	
				j--;
				jNode = jNode->prev;			
//				printf("jNode->prev:%p, jNode:%p, jNode->next:%p\n", jNode->prev, jNode, jNode->next);
			}
			if(i < j)		
			{	
				iNode = assign(iNode, jNode);
				i++;
				iNode = iNode->next;
			}
					
			while(!compare(iNode, tmpNode)&&(i < j))
			{
				i++;
				iNode = iNode->next;
			}
			if(i < j)
			{
				jNode = assign(jNode, iNode);
				j--;
				jNode = jNode->prev;
			}				
		}	


		iNode = assign(iNode, tmpNode);
		
		LinkList_Sort(linklist , low, i-1, compare, assign);
		LinkList_Sort(linklist , i+1, high, compare, assign);

	}	
	if(tmpNode!=NULL)	
	{
		free(tmpNode);
		tmpNode = NULL;
	}
	return linklist;
}

//遍历(相同)
void LinkList_Traverse(LinkList* linklist, PrintFun print)
{
	if(linklist == NULL)
		return;
	Node* tmp;
//	tmp = &(linklist->head);
	tmp = &(linklist->tail);
	while(tmp->prev && tmp->prev!=&(linklist->head))
	{
		tmp = tmp->prev;
		print(tmp);
	}
}

//遍历（相反）
void LinkList_Traverse_Reverse(LinkList* linklist, PrintFun print)
{
	if(linklist == NULL)
		return;
	Node* tmp;
	tmp = &(linklist->head);

	while(tmp->next && tmp->next!=&(linklist->tail))
	{
		tmp = tmp->next;
		print(tmp);
	}
		
}



//返回链表长度
long LinkList_Length(LinkList* linklist)
{
	return linklist->len;
}

//销毁链表
void LinkList_Destory(LinkList* linklist)
{
	if(linklist)
	{
		free(linklist);
	//	linklist = NULL;
	}
}

//获取链表pos位置节点
Node* LinkList_Get(LinkList* linklist, long pos)
{
	if(linklist == NULL || pos<0)
		return NULL;
	Node* current;
	int i = 0;
	current = &(linklist->head);
	for(i = 0;i<pos &&(current->next!= NULL);i++)
	{
		current = current->next;
	}

	return current->next;
}

//删除链表pos位置节点
Node* LinkList_Delete(LinkList* linklist, long pos)
{
	if(linklist == NULL || pos<0)
		return;

	Node *current;
	Node *tmpNode;
	int i = 0;

	current =&(linklist->head);
	for(i = 0;i<pos && (current->next!= NULL);i++)
	{
		current = current->next;
	}
	tmpNode = current->next;
	current->next = tmpNode->next;
	tmpNode->prev = current->prev;
	linklist->len--;
	return tmpNode;
}

//删除节点（按节点数据）
LinkList* LinkList_Delete_Node(LinkList* linklist, void* val, ValCompare valcompare)
{
	if(linklist == NULL )
		return;

	Node *current;

	current =linklist->head.next;
	while(current!= NULL)
	{
		if(valcompare(current, val))
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				linklist->len--;
				return linklist;
			}
		else
			current = current->next;
	}
	printf("Delete Node Not Found!\n");
	return NULL;
}

//用户释放内存
void LinkList_Free(LinkList* linklist , FreeMemory freemem)
{
	if(linklist == NULL || linklist->len <0)
		return;
	Node *tmpNode;
	Node *storgNode;
	tmpNode = linklist->head.next;

	while(tmpNode!=NULL && tmpNode!=&(linklist->tail)) 	
	{
//		tmpNode = tmpNode->next;
		storgNode = tmpNode->next;
		tmpNode->prev->next = tmpNode->next;
		tmpNode->next->prev = tmpNode->prev;

		linklist->len--;
		freemem(tmpNode);
		tmpNode = storgNode;
	}
}


LinkList* LinkList_Merge(LinkList* linklist_first, LinkList* linklist_second)
{
	if(linklist_first==NULL||linklist_second==NULL||linklist_first->len<0||linklist_second->len<0)
		return NULL;
	
/*	linklist_first->tail.next = &(linklist_second->head);
	linklist_second->head.prev = &(linklist_first->tail);
	
	linklist_first->tail.prev->next = &(linklist_second->head);
	linklist_second->head.prev = linklist_first->tail.prev;
	linklist_first->tail.next = NULL;
	linklist_second->head.prev->next = linklist_second->head.next;
	linklist_second->head.next->prev = linklist_second->head.prev;
	linklist_first->tail = linklist_second->tail;
	linklist_first->tail.next = NULL;*/
	linklist_first->tail.prev->next = linklist_second->head.next;
	linklist_second->head.next->prev = linklist_first->tail.prev;
	linklist_first->tail.prev = linklist_second->tail.prev;
	linklist_second->tail.prev->next = &(linklist_first->tail);
	linklist_second->head.next = NULL;
//	linklist_first->tail = linklist_second->tail;

	linklist_first->len += linklist_second->len;	
	free(linklist_second);	
	return linklist_first;
}



