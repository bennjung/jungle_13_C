//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
    // ptr head가 어떤값이지? 
	// 포인터를 가르키는 포인터 
	ListNode* temp = *ptrHead;
	// 1. ptrHead == llhead
	if(temp->next == NULL) {
		return -1;
	} 
	// 리스트 순회해서 가장 큰 값 찾아내서 헤더와 바꾸기 
	
	int idx = 0;
	int pidx = 0;
	ListNode* cur = *ptrHead;
	int mval = temp->item;
	ListNode* mnode = temp;
	ListNode* mprev = *ptrHead;
	// 1. max 값 찾을때마다 mnode 구조체 재할당
	while (cur != NULL){
		if (cur->item > mval){
			// debug 
			pidx = idx;
			mnode = cur;
			mval = cur->item;
		}
		idx++;
		cur = cur->next;
	}
	if (mnode == *ptrHead){
		return 0;
	}
	printf("현재 최대 노드 : %d\n", mnode->item);
	// 2. mprev 찾기 
	while (pidx-1 > 0){
		mprev = mprev->next;
		if (mprev == NULL){
			break;
		}
		pidx--;
	}

	printf("이전 최대 노드 : %d\n", mprev->item);
	// 3. 헤더<->Mnode 스왑 
	// 3.1. 맥스값의 직전노드가 맥스의 다음값을 가르킴 // tc [1 2 9] 
	mprev->next = mnode->next; // 2 => 1 
	
	// 3.2. 맥스노드가 맨앞 노드를를 가르킴
	mnode->next = temp; // 1 => NULL
	
	// 3.3 Mnode 헤더 변경
	*ptrHead = mnode;
	
	return 0;


	
	
	
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
